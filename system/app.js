document.addEventListener('DOMContentLoaded', () => {
  // Initialize navigation and interceptors
  const sidebarNav = document.getElementById('sidebar-nav');
  const contentDiv = document.getElementById('content');

  // Submenu Toggle Logic
  const submenuToggles = document.querySelectorAll('.submenu-toggle');
  submenuToggles.forEach(toggle => {
    toggle.addEventListener('click', (e) => {
      e.preventDefault();
      e.stopPropagation();
      const parent = toggle.closest('.has-submenu');
      if (parent) parent.classList.toggle('open');
    });
  });

  // Support clicking the parent header
  const submenuHeaders = document.querySelectorAll('.submenu-header');
  submenuHeaders.forEach(header => {
    header.addEventListener('click', (e) => {
      if (e.target.tagName !== 'A' && e.target.tagName !== 'BUTTON') {
        const parent = header.closest('.has-submenu');
        if (parent) parent.classList.toggle('open');
      }
    });
  });

  // Mobile Menu Toggle
  const menuToggle = document.getElementById('mobile-menu-toggle');
  if (menuToggle) {
    menuToggle.addEventListener('click', () => {
      document.body.classList.toggle('sidebar-open');
    });
  }

  // Intercept clicks in content area
  contentDiv.addEventListener('click', (e) => {
    const target = e.target.closest('a');
    if (!target) return;
    const href = target.getAttribute('href') || target.getAttribute('xlink:href');
    if (href && !href.startsWith('http') && !href.startsWith('#') && !href.startsWith('javascript:')) {
      if (href.endsWith('.md') || href.endsWith('.yaml') || href.endsWith('.yml')) {
        e.preventDefault();
        const newPath = resolvePath(window.currentPath || 'README.md', href);
        navigateToPath(newPath);
      }
    }
  });

  // Sidebar Link Delegation
  sidebarNav.addEventListener('click', (e) => {
    const link = e.target.closest('a');
    if (!link || !link.getAttribute('data-path')) return;
    e.preventDefault();
    navigateToPath(link.getAttribute('data-path'));
    document.body.classList.remove('sidebar-open');
  });

  // Lightbox Logic
  const modal = document.getElementById('image-modal');
  contentDiv.addEventListener('click', (e) => {
    if (e.target.tagName === 'IMG' && !e.target.classList.contains('droid-render')) {
      modal.style.display = 'flex';
      document.getElementById('modal-img').src = e.target.src;
      document.getElementById('modal-caption').innerText = e.target.alt || 'Technical View';
      document.body.style.overflow = 'hidden';
    }
  });

  modal.addEventListener('click', (e) => {
    if (e.target === modal || e.target.classList.contains('close-modal')) {
      modal.style.display = 'none';
      document.body.style.overflow = '';
    }
  });

  // State Management
  window.addEventListener('popstate', (e) => {
    if (e.state && e.state.path) navigateToPath(e.state.path, false);
    else navigateToPath(window.location.hash.slice(1) || 'README.md', false);
  });

  // Initial Boot
  const initialPath = window.location.hash.slice(1) || 'README.md';
  navigateToPath(initialPath, false);
});

/* --- CORE SYSTEM HANDLERS (GLOBAL SCOPE) --- */

let currentPath = 'README.md';

function resolvePath(base, relative) {
  if (relative.startsWith('docs/') || relative.startsWith('firmware/') || relative.startsWith('archive/') || relative.startsWith('assets/')) {
    return relative;
  }
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
    if (isActive) {
      const parent = l.closest('.has-submenu');
      if (parent) parent.classList.add('open');
    }
  });
  loadContent(path, pushHistory);
}

async function loadContent(path, pushHistory = true) {
  if (pushHistory) window.history.pushState({ path: path }, '', '#' + path);
  window.currentPath = path;
  const contentDiv = document.getElementById('content');
  const heroSection = document.getElementById('hero');

  if (heroSection) heroSection.style.display = (path === 'README.md') ? 'flex' : 'none';
  contentDiv.innerHTML = `<div class="loading-text" style="font-family: var(--font-mono); color: var(--accent-cyan);">Decrypting datastream... [${path}]</div>`;

  try {
    const response = await fetch('./' + path + '?v=' + Date.now());
    if (!response.ok) throw new Error('CORS or Connection Denial: ' + response.statusText);
    const markdown = await response.text();

    if (path.endsWith('.yaml') || path.endsWith('.yml')) {
      contentDiv.innerHTML = `<h1>${path.split('/').pop()}</h1><pre><code>${escapeHtml(markdown)}</code></pre>`;
    } else {
      contentDiv.innerHTML = marked.parse(markdown);
      setTimeout(() => renderMermaidDiagrams(contentDiv), 100);
    }
    
    if (typeof lucide !== 'undefined') lucide.createIcons();
    window.scrollTo({ top: 0, behavior: 'smooth' });
  } catch (error) {
    contentDiv.innerHTML = `<div class="alert alert-warning"><strong>ACCESS DENIED</strong><br>${error.message}</div>`;
  }
}

async function renderMermaidDiagrams(container) {
  const nodes = container.querySelectorAll('.mermaid');
  if (nodes.length === 0) return;
  mermaid.initialize({ startOnLoad: false, theme: 'dark', securityLevel: 'loose', flowchart: { useMaxWidth: false, htmlLabels: true, curve: 'basis' } });
  await mermaid.run({ nodes: nodes });
  
  nodes.forEach(node => {
    const svg = node.querySelector('svg');
    if (!svg || node.dataset.initialized) return;
    node.dataset.initialized = 'true';
    const pz = svgPanZoom(svg, { zoomEnabled: true, controlIconsEnabled: false, fit: true, center: true, minZoom: 0.1, maxZoom: 14 });
    
    // Resize handler
    window.addEventListener('resize', () => { pz.resize(); pz.fit(); pz.center(); });
  });
}

function escapeHtml(unsafe) {
  return unsafe.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;").replace(/"/g, "&quot;").replace(/'/g, "&#039;");
}

/* --- NEURAL CONNECTOME HUB --- */
const CONNECTOME_DATA = {
  NODE_1: {
    title: "NODE 1: DOME MOTION MASTER",
    manual: "docs/architecture/node-1-dome-motion.md",
    logic: `graph TD; N1["Node 1 (Dome S3)"]:::brain; ESC["Dome ESC"]:::drive; RC["RC Receiver"]:::signal; N3["Node 3 (WLED)"]:::brain; RC -->|PWM| N1; N1 -->|PWM| ESC; N1 -->|UART| N3; classDef brain fill:#0066cc,stroke:#fff,color:#fff; classDef drive fill:#cc3300,stroke:#fff,color:#fff; classDef signal fill:#ffcc00,stroke:#333,color:#000;`
  },
  NODE_2: {
    title: "NODE 2: NEURAL SOUND HUB",
    manual: "docs/architecture/node-2-sound-hub.md",
    logic: `graph TD; N2["Node 2 (Sound Hub)"]:::brain; DF["DFPlayer Mini"]:::audio; AMP["TPA3118 Amp"]:::audio; SPK["Pyle Speaker"]:::audio; N2 -->|UART| DF; DF -->|Analog| AMP; AMP -->|Audio| SPK; classDef brain fill:#0066cc,stroke:#fff,color:#fff; classDef audio fill:#99cc00,stroke:#000,color:#000;`
  },
  NODE_3: {
    title: "NODE 3: LIGHTING DISTRIBUTION",
    manual: "docs/architecture/node-3-led-distribution.md",
    logic: `graph TD; N3["Node 3 (WLED)"]:::brain; F_LED["Front LEDs"]:::lights; R_LED["Rear LEDs"]:::lights; N3 -->|GPIO 18| F_LED; N3 -->|GPIO 19| R_LED; classDef brain fill:#0066cc,stroke:#fff,color:#fff; classDef lights fill:#6600cc,stroke:#fff,color:#fff;`
  },
  BAT: {
    title: "DEWALT 20V POWER CORE",
    manual: "docs/maintenance/battery-runtime-guide.md",
    logic: `graph TD; BAT["20V Battery"]:::power; LVC["LVP Protection"]:::power; BUS["Fuse/Bus Rail"]:::power; BAT ==>|20V| LVC; LVC ==>|20V| BUS; classDef power fill:#ff9900,stroke:#333,stroke-width:2px,color:#000;`
  },
  AUDIO: {
    title: "AUDIO STACK CONSTRUCT",
    manual: "docs/capabilities/lights-and-sounds/audio-system.md",
    logic: `graph LR; HUB["Node 2"]:::brain; DF["DFPlayer"]:::audio; AMP["TPA3118"]:::audio; HUB -->|UART| DF; DF -->|Analog| AMP; classDef brain fill:#0066cc,stroke:#fff,color:#fff; classDef audio fill:#99cc00,stroke:#000,color:#000;`
  }
};

window.showConnectome = async function(nodeId) {
  const data = CONNECTOME_DATA[nodeId];
  const modal = document.getElementById('connectome-modal');
  const container = document.getElementById('connectome-container');
  if (!data || !modal || !container) return;

  modal.style.display = 'flex';
  document.getElementById('connectome-title').innerText = data.title;
  document.getElementById('full-manual-btn').onclick = () => {
    modal.style.display = 'none';
    navigateToPath(data.manual);
  };

  container.innerHTML = `<div class="mermaid">${data.logic}</div>`;
  mermaid.initialize({ theme: 'dark', securityLevel: 'loose' });
  await mermaid.run({ nodes: [container.querySelector('.mermaid')] });
  document.body.style.overflow = 'hidden';

  modal.onclick = (e) => {
    if (e.target === modal || e.target.classList.contains('close-connectome')) {
      modal.style.display = 'none';
      document.body.style.overflow = '';
    }
  };
};
