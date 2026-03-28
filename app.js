document.addEventListener('DOMContentLoaded', () => {
    const contentDiv = document.getElementById('content');
    const navLinks = document.querySelectorAll('#sidebar-nav a');

    // Configure marked with custom rendering for Mermaid and GitHub Alerts
    const renderer = new marked.Renderer();
    
    // Custom code block renderer for Mermaid
    renderer.code = ({ text, lang }) => {
        if (lang === 'mermaid') {
            return `<div class="mermaid">${text}</div>`;
        }
        return `<pre><code class="language-${lang}">${escapeHtml(text)}</code></pre>`;
    };

    // Custom blockquote renderer for GitHub Alerts [!TIP], etc.
    renderer.blockquote = ({ text }) => {
        const alertMatch = text.match(/^\[!(TIP|IMPORTANT|WARNING|CAUTION|NOTE)\]\s*([\s\S]*)$/i);
        if (alertMatch) {
            const type = alertMatch[1].toUpperCase();
            const content = marked.parse(alertMatch[2]);
            return `<div class="alert alert-${type.toLowerCase()}"><strong>${type}</strong><br>${content}</div>`;
        }
        return `<blockquote>${marked.parse(text)}</blockquote>`;
    };

    marked.use({ renderer });

    let currentPath = '';

    /**
     * Fetch and render a markdown file
     * @param {string} path - Path to the .md file (relative to root)
     */
    async function loadContent(path) {
        currentPath = path;
        contentDiv.innerHTML = '<div class="loading-text" style="font-family: var(--font-mono); color: var(--accent-cyan);">Decrypting datastream... [' + path + ']</div>';
        
        try {
            // Adjust path to root since app.js is now in root
            const fullPath = './' + path;
            const response = await fetch(fullPath);
            
            if (!response.ok) {
                throw new Error('Could not access datastream: ' + response.statusText);
            }
            
            const markdown = await response.text();
            
            // Render markdown or code block if it's a YAML file
            if (path.endsWith('.yaml') || path.endsWith('.yml')) {
                contentDiv.innerHTML = '<h1>' + path.split('/').pop() + '</h1><pre><code>' + escapeHtml(markdown) + '</code></pre>';
            } else {
                contentDiv.innerHTML = marked.parse(markdown);
                
                // Trigger Mermaid rendering for any new diagrams
                setTimeout(async () => {
                    try {
                        // Reset mermaid for clean state logic
                        mermaid.initialize({ 
                            startOnLoad: false, 
                            theme: 'dark',
                            securityLevel: 'loose',
                            flowchart: { useMaxWidth: true, htmlLabels: true, curve: 'basis' }
                        });
                        
                        // Force render on all .mermaid divs in the new content
                        const nodes = contentDiv.querySelectorAll('.mermaid');
                        if (nodes.length > 0) {
                            await mermaid.run({
                                nodes: nodes,
                            });
                        }
                    } catch (e) {
                        console.error("Mermaid Decryption Error:", e);
                    }
                }, 100);
            }

            // Scroll to top
            window.scrollTo({ top: 0, behavior: 'smooth' });

        } catch (error) {
            contentDiv.innerHTML = `
                <div style="color: var(--accent-red); padding: 20px; border: 1px solid var(--accent-red);">
                    <h2 style="margin-top:0">CRITICAL ERROR: ACCESS DENIED</h2>
                    <p>${error.message}</p>
                    <p style="font-family: var(--font-mono); font-size: 0.8rem; margin-top: 10px;">
                        NOTE: Browsers block local file access (CORS) when opening file:// directly. 
                        Please run a local web server (e.g., 'npx http-server') to view the wiki properly.
                    </p>
                </div>
            `;
        }
    }

    /**
     * Resolve a relative path against a base path
     */
    function resolvePath(base, relative) {
        // If it already looks like a root-relative path (docs/... firmware/...), just use it
        if (relative.startsWith('docs/') || relative.startsWith('firmware/') || relative.startsWith('archive/')) {
            return relative;
        }

        const stack = base.split('/');
        const parts = relative.split('/');
        stack.pop(); // remove current file
        for (let i = 0; i < parts.length; i++) {
            if (parts[i] === '.') continue;
            if (parts[i] === '..') stack.pop();
            else stack.push(parts[i]);
        }
        return stack.join('/');
    }

    // Intercept clicks in the content area for relative links (Standard and SVG)
    contentDiv.addEventListener('click', (e) => {
        // Support standard <a> and SVG <a> tags (Mermaid links)
        const target = e.target.closest('a');
        if (!target) return;

        // Check both href and xlink:href (for older SVG links)
        const href = target.getAttribute('href') || target.getAttribute('xlink:href');
        
        // Only intercept relative markdown/yaml links
        if (href && !href.startsWith('http') && !href.startsWith('#')) {
            if (href.endsWith('.md') || href.endsWith('.yaml') || href.endsWith('.yml')) {
                e.preventDefault();
                const newPath = resolvePath(currentPath, href);
                
                // Update Sidebar Active State
                navLinks.forEach(l => {
                    l.classList.toggle('active', l.getAttribute('data-path') === newPath);
                });

                loadContent(newPath);
            }
        }
    });

    function escapeHtml(unsafe) {
        return unsafe
             .replace(/&/g, "&amp;")
             .replace(/</g, "&lt;")
             .replace(/>/g, "&gt;")
             .replace(/"/g, "&quot;")
             .replace(/'/g, "&#039;");
    }

    // Nav Click Handling
    navLinks.forEach(link => {
        link.addEventListener('click', (e) => {
            e.preventDefault();
            
            // Update Active State
            navLinks.forEach(l => l.classList.remove('active'));
            link.classList.add('active');
            
            const path = link.getAttribute('data-path');
            loadContent(path);
        });
    });

    // Initial Load
    const defaultPath = document.querySelector('nav a.active').getAttribute('data-path');
    loadContent(defaultPath);
});
