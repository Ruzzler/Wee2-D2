# 📜 Project Changelog: Wee2-D2 Imperial Databank

All notable changes to the Wee2-D2 project will be documented in this file. This project adheres to [Semantic Versioning](https://semver.org/) and the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) standard.

---

## [1.3.0] - 2026-03-28 (Diatáxis UX Overhaul)
### Changed
- **Navigation Flow**: Reorganized the Databank sidebar to follow the Builder's Journey (Overview > Architecture > Wiring > Firmware > Maintenance).
- **Component Manuals De-clutter**: Removed the standalone 8-link component manual section from the sidebar. Users now click through via the BoM or Interactive Schematic, adhering to optimal Information Architecture.
- **Clarified Project Scope**: Updated `README.md` to explicitly state the databank handles electronics only, not 3D printing.
- **Architecture Consolidation**: Removed the bulky Mermaid graph from `README.md` in favor of pointing back to the dedicated `electrical-schematic.md` interface.
- **Local Server Standardization**: Enforced port `8001` with loopback IP across all documentation to prevent Windows IPv6 binding conflicts.
- **History API**: Rewrote navigation in `app.js` to utilize browser PopState for functional forward/back buttons and hash routing.

## [1.2.0] - 2026-03-28 (Tiered Technical Standard)
### Added
- **BoM Layout Upgrade**: Transitioned to a 4-column layout with a dedicated **"Visual ID"** column. All component images are now isolated and clickable via the Imperial Lightbox.
- **Hardware Asset Enrichment**: Integrated missing hardware photos for the PEMENOL 60W Soundboard and goBILDA ESC into the primary component ledger.
- **Architectural Subcategories**: Implemented a 3-pillar tiered hierarchy: `docs/architecture`, `docs/hardware`, and `docs/maintenance`.

### Changed
- **Folder Normalization**: Migrated all system-wide guides to `architecture/` and component manuals to `hardware/`.
- **BoM Consolidation**: Unified the Bill of Materials to `docs/bill-of-materials.md` and updated all internal links.
- **Asset Normalization**: Synchronized all file naming to lowercase-hyphenated (e.g., `droid-actual.jpg`).
- **Sidebar Revamp**: Redesigned the Imperial HUD to reflect the new tiered categorization.
- **UX Refinement**: Fixed the Databank navigation logic so the Hero droid image only appears on the **Droid Overview (README.md)** page.
- **Hero Image Upgrade**: Switched the primary project overview image to `droid-actual.jpg` for higher fidelity.
- **Sidebar Navigation**: Renamed "Mission Overview" to "Droid Overview" for consistent documentation.

## [1.1.0] - 2026-03-28 (WikiSync & PDFAssist)
### Added
- **Battery Endurance Estimation**: Created **`docs/maintenance/battery-runtime-guide.md`** with duty cycle calculations.
- **Hardware Photo Integration**: Migrated and optimized raw assets to permanent project directory.
- **Enhanced Documentation**: Integrated technical photos into manuals and the BoM.

### Changed
- **Databank Navigation**: Updated `index.html` sidebar to link to Firmware READMEs instead of raw YAML files for enhanced readability.
- **BoM Corrections**: Fixed incorrect hardware links and updated technical descriptions for goBILDA components.

- **Broken Links**: Resolved dead links in `README.md` and BoM cross-references.
- **Structure Cleanup**: Removed redundant/empty `wiki/` directory to standardize on the `docs/` architecture.

---

## [1.0.0-UDNS] - 2026-03-28
### Added
- **Unified Droid Nervous System (UDNS)**: Implemented a high-bandwidth master-slave serial architecture across all 3 nodes.
- **UDNS Technical Documentation**: Created a dedicated explainer and wiring guide for the droid's integrated nervous system.
- **AI Agent Briefing**: Created `AGENTS.md` to provide comprehensive context, hardware specs, and design guidelines for future AI engineering assistants.
- **Hardware Profile**: Integrated the **PEMENOL 60W (DY-HL50T)** soundboard and **ESP32D Dev Board** (Body) into the technical manuals.
- **Interactive HUD**: Added professional `svg-pan-zoom` capabilities to all technical schematics with a GitHub-style control cluster.
- **S3 Mini Support**: Formalized the use of ESP32-S3 Super Mini (HW-747) for Dome logic.
- **Wiring Manual**: Created a dedicated high-fidelity wiring guide for the 6-circuit slip ring and serial interconnects.
- **Imperial Databank UI**: Launched the custom SPA (Single Page Application) for technical documentation.

### Changed
- **MCU Configuration**: Refactored the droid from a "simple trigger" model to a "Nexus Bus" Serial model.
- **Mobile Responsiveness**: Optimized the entire Databank UI for desktop and high-density mobile displays.
- **Path Resolution**: Improved the SPA routing to handle GitHub Pages subdirectories (`/Wee2-D2/`) automatically.

### Fixed
- **CSS Linting**: Resolved nested media query bracket issues in `style.css`.
- **Image Performance**: Implemented metadata stripping for all imported technical photos to optimize site load speed.

---

## [0.5.0-Initial] - 2026-03-21
### Added
- Initial project structure including Markdown documentation and Mermaid diagrams.
- Basic Bill of Materials (BOM) following the Star Wars Imperial aesthetic.
- ESPHome firmware templates for MCU 1 (Body Controller).
- Core electrical schematic draft representing the initial 20V power system.
