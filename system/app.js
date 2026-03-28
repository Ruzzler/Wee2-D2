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

    // Custom image renderer to resolve paths relative to the MD file
    renderer.image = ({ href, title, text }) => {
        const resolvedHref = resolvePath(currentPath, href);
        // On GitHub Pages, we need to ensure local assets are served correctly
        return `<img src="${resolvedHref}" alt="${text}" title="${title || ''}" class="content-image">`;
    };

    // Custom blockquote renderer for GitHub Alerts [!TIP], etc.
    renderer.blockquote = ({ text }) => {
        // Multi-line match for alerts
        const alertMatch = text.match(/^\[!(TIP|IMPORTANT|WARNING|CAUTION|NOTE)\]\s*([\s\S]*)$/i);
        if (alertMatch) {
            const type = alertMatch[1].toUpperCase();
            const alertContent = alertMatch[2].trim();
            return `<div class="alert alert-${type.toLowerCase()}"><strong>${type}</strong><br>${marked.parse(alertContent)}</div>`;
        }
        return `<blockquote>${marked.parse(text)}</blockquote>`;
    };

    marked.use({ renderer });

    let currentPath = '';

    /**
     * Fetch and render a markdown file
     * @param {string} path - Path to the .md file (relative to root)
     * @param {boolean} pushHistory - Whether to push the path to browser history
     */
    async function loadContent(path, pushHistory = true) {
        if (pushHistory) {
            window.history.pushState({ path: path }, '', '#' + path);
        }
        currentPath = path;
        
        // Show hero only on Project Overview (README.md)
        const heroSection = document.getElementById('hero');
        if (heroSection) {
            heroSection.style.display = (path === 'README.md') ? 'flex' : 'none';
        }

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
                        const nodes = contentDiv.querySelectorAll('.mermaid');
                        if (nodes.length === 0) return;

                        // Configuration for Mermaid
                        mermaid.initialize({ 
                            startOnLoad: false, 
                            theme: 'dark',
                            securityLevel: 'loose',
                            flowchart: { useMaxWidth: false, htmlLabels: true, curve: 'basis' }
                        });
                        
                        // Run Mermaid rendering
                        await mermaid.run({ nodes: nodes });

                        // Define Icons Object
                        const icons = {
                            up: '<svg viewBox="0 0 16 16"><path d="M3.47 10.53a.75.75 0 001.06 0L8 7.06l3.47 3.47a.75.75 0 101.06-1.06l-4-4a.75.75 0 00-1.06 0l-4 4a.75.75 0 000 1.06z"/></svg>',
                            down: '<svg viewBox="0 0 16 16"><path d="M12.53 5.47a.75.75 0 00-1.06 0L8 8.94 4.53 5.47a.75.75 0 00-1.06 1.06l4 4a.75.75 0 001.06 0l4-4a.75.75 0 000-1.06z"/></svg>',
                            left: '<svg viewBox="0 0 16 16"><path d="M9.53 12.53a.75.75 0 01-1.06 0l-4-4a.75.75 0 010-1.06l4-4a.75.75 0 011.06 1.06L6.06 8l3.47 3.47a.75.75 0 010 1.06z"/></svg>',
                            right: '<svg viewBox="0 0 16 16"><path d="M6.47 3.47a.75.75 0 011.06 0l4 4a.75.75 0 010 1.06l-4 4a.75.75 0 01-1.06-1.06L9.94 8 6.47 4.53a.75.75 0 010-1.06z"/></svg>',
                            plus: '<svg viewBox="0 0 16 16"><path d="M7.75 2a.75.75 0 01.75.75V7h4.25a.75.75 0 010 1.5H8.5v4.25a.75.75 0 01-1.5 0V8.5H2.75a.75.75 0 010-1.5H7V2.75A.75.75 0 017.75 2z"/></svg>',
                            minus: '<svg viewBox="0 0 16 16"><path d="M2 7.75A.75.75 0 012.75 7h10.5a.75.75 0 010 1.5H2.75A.75.75 0 012 7.75z"/></svg>',
                            sync: '<svg viewBox="0 0 16 16"><path d="M1.705 8.005a.75.75 0 01.834.656 5.5 5.5 0 009.592 2.97l-1.204-1.204a.25.25 0 01.177-.427h3.646a.25.25 0 01.25.25v3.646a.25.25 0 01-.427.177l-1.38-1.38A7.001 7.001 0 011.05 8.84a.75.75 0 01.656-.834zM1.05 1.705v3.646a.25.25 0 00.25.25h3.646a.25.25 0 00.177-.427L3.744 3.793a5.5 5.5 0 019.592 2.97.75.75 0 101.498-.12 7.001 7.001 0 00-11.874-4.836l-1.38-1.38a.25.25 0 00-.427.177z"/></svg>',
                            expand: '<svg viewBox="0 0 16 16"><path d="M3.75 2a.75.75 0 01.75.75V4.5h1.75a.75.75 0 010 1.5H3.5a.75.75 0 01-.75-.75v-2.75A.75.75 0 013.75 2zM12.25 2a.75.75 0 01.75.75v2.75a.75.75 0 01-.75.75H9.75a.75.75 0 010-1.5h1.75V2.75a.75.75 0 01.75-.75zM3.75 14a.75.75 0 01-.75-.75v-2.75a.75.75 0 01.75-.75h2.75a.75.75 0 010 1.5H4.5v1.75a.75.75 0 01-.75-.75zM12.25 14a.75.75 0 01-.75-.75V11.5h-1.75a.75.75 0 010-1.5h2.75a.75.75 0 01.75.75v2.75a.75.75 0 01-.75.75z"/></svg>'
                        };

                        // Initialize each diagram with a custom toolbar and pan-zoom
                        nodes.forEach((container, index) => {
                            const svg = container.querySelector('svg');
                            if (!svg || container.dataset.initialized) return;

                            // Mark as initialized to avoid duplicates
                            container.dataset.initialized = 'true';

                            // 1. Initialize PAN-ZOOM
                            const pz = svgPanZoom(svg, {
                                zoomEnabled: true,
                                controlIconsEnabled: false,
                                fit: true,
                                center: true,
                                minZoom: 0.1,
                                maxZoom: 10,
                                zoomScaleSensitivity: 0.2
                            });

                            // 2. Create Navigation Cluster (Bottom-Right)
                            const navCluster = document.createElement('div');
                            navCluster.className = 'diagram-nav-cluster';
                            
                            const gridItems = [
                                { type: 'spacer' },
                                { type: 'btn', icon: icons.up, title: 'Pan Up', action: () => pz.panBy({x: 0, y: -80}) },
                                { type: 'btn', icon: icons.plus, title: 'Zoom In', action: () => pz.zoomIn() },
                                { type: 'btn', icon: icons.left, title: 'Pan Left', action: () => pz.panBy({x: -80, y: 0}) },
                                { type: 'btn', icon: icons.sync, title: 'Fit to Screen', action: () => pz.reset() },
                                { type: 'btn', icon: icons.right, title: 'Pan Right', action: () => pz.panBy({x: 80, y: 0}) },
                                { type: 'spacer' },
                                { type: 'btn', icon: icons.down, title: 'Pan Down', action: () => pz.panBy({x: 0, y: 80}) },
                                { type: 'btn', icon: icons.minus, title: 'Zoom Out', action: () => pz.zoomOut() }
                            ];

                            gridItems.forEach(item => {
                                if (item.type === 'spacer') {
                                    const spacer = document.createElement('div');
                                    spacer.className = 'toolbar-spacer';
                                    navCluster.appendChild(spacer);
                                } else {
                                    const btn = document.createElement('button');
                                    btn.className = 'toolbar-btn';
                                    btn.innerHTML = item.icon;
                                    btn.title = item.title;
                                    btn.onclick = (e) => {
                                        e.preventDefault();
                                        e.stopPropagation();
                                        item.action();
                                    };
                                    navCluster.appendChild(btn);
                                }
                            });

                            // 3. Create Fullscreen Button (Top-Right)
                            const fsBtn = document.createElement('button');
                            fsBtn.className = 'diagram-fs-btn';
                            fsBtn.innerHTML = icons.expand;
                            fsBtn.title = 'View Fullscreen';
                            fsBtn.onclick = (e) => {
                                e.preventDefault();
                                e.stopPropagation();
                                toggleFullscreen(container);
                            };

                            container.appendChild(navCluster);
                            container.appendChild(fsBtn);

                            // Handle resize events
                            window.addEventListener('resize', () => {
                                pz.resize();
                                pz.fit();
                                pz.center();
                            });
                        });
                    } catch (e) {
                        console.error("Mermaid Decryption Error:", e);
                    }
                }, 300);
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

    // Helper for Fullscreen Toggle
    function toggleFullscreen(element) {
        if (!document.fullscreenElement) {
            element.requestFullscreen().catch(err => {
                console.error(`Error attempting to enable fullscreen mode: ${err.message}`);
            });
        } else {
            document.exitFullscreen();
        }
    }

    /**
     * Resolve a relative path against a base path, handling GitHub Pages subdirectories
     */
    function resolvePath(base, relative) {
        // If it's a root-relative path within the databank project
        if (relative.startsWith('docs/') || relative.startsWith('firmware/') || relative.startsWith('archive/') || relative.startsWith('assets/')) {
            return relative;
        }

        // Logic for handling relative path traversal (../)
        const stack = base.split('/');
        const parts = relative.split('/');
        stack.pop(); // remove current filename from stack
        
        for (let i = 0; i < parts.length; i++) {
            if (parts[i] === '.' || parts[i] === '') continue;
            if (parts[i] === '..') {
                if (stack.length > 0) stack.pop();
            } else {
                stack.push(parts[i]);
            }
        }
        
        return stack.join('/');
    }

    // Helper for updating active state and navigating
    function navigateToPath(path, pushHistory = true) {
        navLinks.forEach(l => {
            l.classList.toggle('active', l.getAttribute('data-path') === path);
        });
        loadContent(path, pushHistory);
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
                navigateToPath(newPath);
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
            const path = link.getAttribute('data-path');
            navigateToPath(path);

            // Close mobile menu after click
            document.body.classList.remove('sidebar-open');
        });
    });

    // Mobile Menu Toggle Logic
    const menuToggle = document.getElementById('mobile-menu-toggle');
    if (menuToggle) {
        menuToggle.addEventListener('click', () => {
            document.body.classList.toggle('sidebar-open');
        });
    }

    /* --- LIGHTBOX MODAL LOGIC --- */
    const modal = document.getElementById('image-modal');
    const modalImg = document.getElementById('modal-img');
    const modalCaption = document.getElementById('modal-caption');
    const closeModal = document.querySelector('.close-modal');

    // Content area delegated click event
    contentDiv.addEventListener('click', (e) => {
        if (e.target.tagName === 'IMG' && !e.target.classList.contains('droid-render')) {
            openModal(e.target);
        }
    });

    function openModal(imgElement) {
        modal.style.display = 'flex';
        modalImg.src = imgElement.src;
        modalCaption.innerText = imgElement.alt || 'Technical Specification View';
        document.body.style.overflow = 'hidden'; // Prevent background scroll
    }

    function closeTheModal() {
        modal.style.display = 'none';
        document.body.style.overflow = '';
    }

    // Close on click outside or close button
    modal.addEventListener('click', (e) => {
        if (e.target === modal || e.target === closeModal) {
            closeTheModal();
        }
    });

    // Close on ESC
    document.addEventListener('keydown', (e) => {
        if (e.key === 'Escape') closeTheModal();
    });

    // Handle Pop State (Browser Back/Forward Buttons)
    window.addEventListener('popstate', (e) => {
        if (e.state && e.state.path) {
            navigateToPath(e.state.path, false);
        } else {
            const hash = window.location.hash.slice(1);
            if (hash) {
                navigateToPath(hash, false);
            } else {
                navigateToPath('README.md', false);
            }
        }
    });

    // Initial Load
    const initialHash = window.location.hash.slice(1);
    if (initialHash) {
        navigateToPath(initialHash, false);
    } else {
        const activeLink = document.querySelector('nav a.active');
        if (activeLink) {
            const defaultPath = activeLink.getAttribute('data-path');
            // Using replaceState to correctly anchor the first page into history
            window.history.replaceState({ path: defaultPath }, '', '#' + defaultPath);
            navigateToPath(defaultPath, false);
        }
    }
});
