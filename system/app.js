document.addEventListener('DOMContentLoaded', () => {
  const contentDiv = document.getElementById('content');
  const sidebarNav = document.getElementById('sidebar-nav');

  // Configure marked with custom rendering for Mermaid and GitHub Alerts
  const renderer = new marked.Renderer();
  
  renderer.code = ({ text, lang }) => {
    if (lang === 'mermaid') return `<div class="mermaid">${text}</div>`;
    return `<pre><code class="language-${lang}">${escapeHtml(text)}</code></pre>`;
  };

  renderer.image = ({ href, title, text }) => {
    const resolvedHref = resolvePath(window.currentPath || 'README.md', href);
    return `<img src="${resolvedHref}" alt="${text}" title="${title || ''}" class="content-image">`;
  };

  renderer.link = ({ href, title, text }) => {
    let resolvedHref = href;
    if (href && !href.startsWith('http') && !href.startsWith('#') && !href.startsWith('mailto:')) {
      resolvedHref = resolvePath(window.currentPath || 'README.md', href);
    }
    return `<a href="${resolvedHref}" title="${title || ''}">${text}</a>`;
  };

  renderer.blockquote = ({ text }) => {
    const alertMatch = text.match(/^\[!(TIP|IMPORTANT|WARNING|CAUTION|NOTE)\]\s*([\s\S]*)$/i);
    if (alertMatch) {
      const type = alertMatch[1].toUpperCase();
      const alertContent = alertMatch[2].trim();
      return `<div class="alert alert-${type.toLowerCase()}"><strong>${type}</strong><br>${marked.parse(alertContent)}</div>`;
    }
    return `<blockquote>${marked.parse(text)}</blockquote>`;
  };

  marked.use({ renderer });

  // Submenu Toggle Logic
  document.querySelectorAll('.submenu-toggle').forEach(toggle => {
    toggle.addEventListener('click', (e) => {
      e.preventDefault();
      e.stopPropagation();
      const parent = toggle.closest('.has-submenu');
      if (parent) parent.classList.toggle('open');
    });
  });

  // Sidebar Link Delegation
  sidebarNav.addEventListener('click', (e) => {
    const link = e.target.closest('a');
    if (!link || !link.getAttribute('data-path')) return;
    e.preventDefault();
    navigateToPath(link.getAttribute('data-path'));
    document.body.classList.remove('sidebar-open');
  });

  // Intercept clicks in content area (Standard & SVG)
  contentDiv.addEventListener('click', (e) => {
    const target = e.target.closest('a');
    if (!target) return;
    const href = target.getAttribute('href') || target.getAttribute('xlink:href');
    if (href && !href.startsWith('http') && !href.startsWith('#')) {
      if (href.endsWith('.md') || href.endsWith('.yaml') || href.endsWith('.yml')) {
        e.preventDefault();
        const newPath = resolvePath(window.currentPath || 'README.md', href);
        navigateToPath(newPath);
      }
    }
  });

  // Mobile Menu Toggle
  const menuToggle = document.getElementById('mobile-menu-toggle');
  if (menuToggle) {
    menuToggle.addEventListener('click', () => {
      document.body.classList.toggle('sidebar-open');
    });
  }

  // State Management
  window.addEventListener('popstate', (e) => {
    if (e.state && e.state.path) navigateToPath(e.state.path, false);
    else navigateToPath(window.location.hash.slice(1) || 'README.md', false);
  });

  // Initial Load
  const initialPath = window.location.hash.slice(1) || 'README.md';
  navigateToPath(initialPath, false);
});

/* --- GLOBAL SYSTEM CORE --- */

let currentPath = 'README.md';

function resolvePath(base, relative) {
  if (relative.startsWith('docs/') || relative.startsWith('firmware/') || relative.startsWith('archive/') || relative.startsWith('assets/')) return relative;
  const stack = base.split('/');
  const parts = relative.split('/');
  stack.pop();
  for (let i = 0; i < parts.length; i++) {
    if (parts[i] === '.' || parts[i] === '') continue;
    if (parts[i] === '..') { if (stack.length > 0) stack.pop(); }
    else { stack.push(parts[i]); }
  }
  return stack.join('/');
}

function navigateToPath(path, pushHistory = true) {
  const allLinks = document.querySelectorAll('#sidebar-nav a');
  allLinks.forEach(l => {
    const isActive = l.getAttribute('data-path') === path;
    l.classList.toggle('active', isActive);
  });
  loadContent(path, pushHistory);
}

async function loadContent(path, pushHistory = true) {
  if (pushHistory) window.history.pushState({ path: path }, '', '#' + path);
  window.currentPath = path;
  const contentDiv = document.getElementById('content');
  const heroSection = document.getElementById('hero');

  if (heroSection) heroSection.style.display = (path === 'README.md') ? 'flex' : 'none';
  contentDiv.innerHTML = '<div class="loading-text" style="font-family: var(--font-mono); color: var(--accent-cyan);">Decrypting datastream... [' + path + ']</div>';

  try {
    const response = await fetch('./' + path + '?v=' + Date.now());
    if (!response.ok) throw new Error('CORS or Connection Denial: ' + response.statusText);
    const markdown = await response.text();

    if (path.endsWith('.yaml') || path.endsWith('.yml')) {
      contentDiv.innerHTML = `<h1>${path.split('/').pop()}</h1><pre><code>${escapeHtml(markdown)}</code></pre>`;
    } else {
      contentDiv.innerHTML = marked.parse(markdown);
      setTimeout(() => renderMermaid(contentDiv), 100);
    }
    
    if (typeof lucide !== 'undefined') lucide.createIcons();
    window.scrollTo({ top: 0, behavior: 'smooth' });
  } catch (error) {
    contentDiv.innerHTML = `<div class="alert alert-warning"><strong>ACCESS DENIED</strong><br>${error.message}</div>`;
  }
}

async function renderMermaid(container) {
  const nodes = container.querySelectorAll('.mermaid');
  if (nodes.length === 0) return;
  mermaid.initialize({ startOnLoad: false, theme: 'dark', flowchart: { useMaxWidth: false, htmlLabels: true, curve: 'basis' } });
  await mermaid.run({ nodes: nodes });
  
  nodes.forEach(node => {
    const svg = node.querySelector('svg');
    if (!svg || node.dataset.initialized) return;
    node.dataset.initialized = 'true';
    const pz = svgPanZoom(svg, { zoomEnabled: true, controlIconsEnabled: false, fit: true, center: true, minZoom: 0.1, maxZoom: 14 });
    window.addEventListener('resize', () => { pz.resize(); pz.fit(); pz.center(); });
  });
}

function escapeHtml(unsafe) {
  return unsafe.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;").replace(/"/g, "&quot;").replace(/'/g, "&#039;");
}
