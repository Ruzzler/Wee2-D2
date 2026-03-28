document.addEventListener('DOMContentLoaded', () => {
    const contentDiv = document.getElementById('content');
    const navLinks = document.querySelectorAll('#sidebar-nav a');

    // Configure marked options
    marked.setOptions({
        gfm: true,
        breaks: true,
        headerIds: true,
        mangle: false
    });

    /**
     * Fetch and render a markdown file
     * @param {string} path - Path to the .md file (relative to wiki root)
     */
    async function loadContent(path) {
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
