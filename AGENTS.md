# 🤖 AI Agent Briefing: Wee2-D2 Imperial Databank

This document provides critical context for AI coding assistants working on the Wee2-D2 project. It summarizes the droid's architecture, hardware stack, and historical technical decisions.

---

## 🏛️ Persona & Project Intent
*   **Role**: You are an Imperial Astromech Engineering Assistant.
*   **Aesthetic**: All user interfaces and documentation must reflect a high-fidelity **Star Wars Imperial Databank** theme (Dark mode, glassmorphism, scanlines, modern typography).
*   **Visual Excellence**: Modern web design best practices (curated HSL palettes, smooth transitions, micro-animations) are mandatory. **Avoid Tailwind CSS**; use Vanilla CSS for maximum control.

---

## 🧠 Core Architecture: Unified Droid Nervous System (UDNS)
The droid operates on a **Master-Slave Serial Bus** model called the **UDNS**.

*   **Node 1 (Body Master)**: **ESP32D Dev Board**. Interprets RC signals (PWM) and manages the hardware soundboard triggers.
*   **Nodes 2 & 3 (Dome Slaves)**: **ESP32-S3 Super Mini**. Handle lighting (WLED-style effects within ESPHome) and precision dome rotation.
*   **Communication**: Bidirectional UART (Serial) @ 9600 baud through a 6-circuit slip ring.
*   **Firmware**: 100% **ESPHome**. Integrated with **Home Assistant** and support for **OTA (Over-The-Air)** updates.

---

## 🛠️ Hardware Ecosystem
*   **Audio**: PEMENOL 60W (DY-HL50T). **Confirmed**: No UART control needed; use 9-wire direct trigger (Active LOW).
*   **Power**: 20V DeWalt Battery ➔ LVC (MgcSTEM) ➔ Multi-channel Buck Converters (5.1V logic).
*   **Drive**: 2x Flipsky Mini FSESC 6.7 Pro ➔ **L-faster FLD-5 5" Hub Motors**.
*   **Dome**: goBILDA 5203 Yellow Jacket ➔ 1x15A Motor Controller (PWM).
*   **Lighting**: GrnWave PSI Logic (Addressable LEDs).

---

## 📂 Project Structure & UI Logic
*   **Web Core**: `index.html`, `app.js`, `style.css`.
*   **Logic**: A Single Page App (SPA) that fetches Markdown files from `docs/` and `firmware/` using `fetch`.
*   **Diagrams**: Mermaid.js for schematics, enhanced with `svg-pan-zoom` for a professional engineering HUD.
*   **Image Handling**: Process all images by stripping metadata and optimizing for web (WebP/JPEG). Asset folder: `assets/`.
*   **Path Resolution**: The JS logic must handle GitHub Pages subdirectories (e.g., `/Wee2-D2/`) automatically.

---

## 📜 Key Technical Decisions
1.  **3-Node Split**: Moved from single large ESP to 3 distributed nodes to minimize wiring through the slip ring and isolate motor noise from lighting logic.
2.  **S3 Mini for Dome**: Chosen for its ultra-compact form factor and native USB-C support.
3.  **No Standalone WLED**: Integrated lighting into ESPHome to ensure the "Unified Nervous System" commands work holistically.
4.  **Imperial HUD**: Implemented a custom 7-button navigation grid for schematics to achieve 100% parity with GitHub's professional Mermaid viewer.
5.  **17.5V Safety Floor**: Established 17.5V (3.5V/cell) as the "Imperial Gold Standard" for battery cutoffs to ensure maximum Lithium-ion cell longevity for 20V DeWalt packs.
6.  **Conditional Hero**: Confined the large droid hero render to `README.md` only to maintain technical focus on secondary Databank pages.
7.  **Voltage Clamping**: Implemented a mandatory 60% software throttle clamp for the 12V goBILDA dome motor when running on the 20V DeWalt bus to prevent over-voltage damage.

---

## 🚫 Avoid These Errors
*   **Don't** use placeholders for images; use the real hardware photos in the `assets/` or `Photos to import/` directories.
*   **Don't** use generic CSS colors; stick to the Imperial HSL palette.
*   **Don't** break the URL structure; use the custom `data-path` navigation in `index.html`.

---

## 🛠️ Operational Procedures (SOPs)

### 1. Documenting New Components
*   **Markdown First**: New technical manuals must be placed in `docs/electrical/` or `docs/maintenance/`.
*   **Sidebar Registry**: Every new document **MUST** be manually added to the `<ul>` navigation in `index.html` with a unique `data-path`.
*   **Industrial Formatting**: Use GitHub-style alerts (`> [!IMPORTANT]`, `> [!TIP]`) to highlight critical safety and calibration steps.
*   **Firmware Explainers**: Every firmware node directory `firmware/node-x/` MUST contain a `README.md` that explains the PINOUT, logic (e.g., voltage clamping), and calibration steps for that specific node to ensure readability within the Databank UI.
*   **Energy Sync**: Every major hardware or logic change (e.g., new motors, added LEDs) MUST trigger a review and update of the `docs/maintenance/battery-runtime-guide.md` to maintain accurate con-day endurance estimates.

### 2. Updating the UDNS Firmware
*   **Logic Isolation**: Changes to sound triggers happen in `body-brain.yaml`. Changes to light presets or dome speed happen in the respective `dome-nervous-system` files.
*   **OTA Expectation**: Always remind the user that firmware can be pushed wirelessly via the ESPHome dashboard once the initial USB flash is complete.

### 3. Asset & Image Management
*   **Import Folder**: Always check the `Import/Photos/` and `Import/Manuals/` directories first for new raw assets provided by the user.
*   **Document Processing**: New technical manuals (PDFs) should be moved and renamed to a professional engineering standard within `docs/electrical/`.
*   **Photo Processing**: Evaluate each photo to determine if it should be optimized and moved to the permanent `assets/` folder.
*   **EXIF Stripping**: AI assistants MUST strip all metadata from user photos before moving them to the permanent `/assets` folder.
*   **Optimization**: Prefer WebP/Lossy JPEG for the web interface to keep the "Databank" fast.
*   **Naming**: Use lowercase, hyphenated names (e.g., `esp32d-wiring-v1.webp`).

### 4. Verification & Deployment
*   **Cache-Busting**: When verifying changes on the live GitHub Pages site, assistants **MUST** use a unique version query string (e.g., `index.html?v=v20_refresh`) to bypass the CDN cache.
*   **Interactive Audit**: Use the browser subagent to hover over Mermaid diagrams to ensure the pan-zoom HUD controls are functional after any CSS/JS change.
*   **Lightbox Verification**: Ensure hardware photos in tables (BoM) are clickable to trigger the Imperial Lightbox modal for high-fidelity technical view.

### 6. Project Organization (Standard)
AI assistants MUST adhere to the 3-pillar documentation hierarchy to maintain project clarity:
*   **Architecture (`docs/architecture/`)**: System-wide logic (Wiring, Power, UDNS, Schematics).
*   **Hardware (`docs/hardware/`)**: Individual component manuals and their paired technical PDFs.
*   **Maintenance (`docs/maintenance/`)**: Operational guides, safety standards, and calibration tables.
*   **Bill of Materials**: Maintained at the root `docs/bill-of-materials.md` for immediate decryption. MUST use the **4-column technical ledger** format: `Component | Qty | Specifications | Visual ID`. 
*   **Visual ID Column**: The 4th column in the BoM MUST contain a thumbnail of the localized hardware asset to support the click-to-enlarge Lightbox system.
*   **Assets**: All images MUST reside in the flat `/assets` folder using `lowercase-hyphenated-naming.webp/jpg`.

### 7. Autonomous Maintenance
*   **Dossier Review**: AI assistants MUST periodically and autonomously review and update the **README.md** and **AGENTS.md** files whenever significant structural or technical shifts (e.g., new firmware nodes, asset reorganization) occur to prevent "dossier rot" and maintain technical parity.

---

## 📜 Historical Record
*   **Changelog**: Every session resulting in technical changes **MUST** conclude with an update to `CHANGELOG.md` following the established UDNS versioning scheme.
