# 📜 Project Changelog: Wee2-D2 Imperial Databank

All notable changes to the Wee2-D2 project will be documented in this file. This project adheres to [Semantic Versioning](https://semver.org/) and the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) standard.

---

## [1.1.0-WikiSync] - 2026-03-28
### Added
- **goBILDA Hardware Manual**: Created `docs/electrical/gobilda-motor-manual.md` with detailed 15A ESC and 5203 Yellow Jacket specs.
- **Hub Motor Specifications**: Created technical data repository for the **L-faster FLD-5 200W Hub Motors**, including VESC-tool FOC calibration guidance.
- **Battery Endurance Estimation**: Created **`docs/maintenance/battery-runtime-guide.md`** with duty cycle calculations for 20V DeWalt (4Ah) packs.
- **Hardware Photo Integration**: Migrated 6 real-world photos from `Photos to import/` to `assets/` with optimized metadata and standardized naming.
- **Enhanced Documentation**: Integrated hardware photos into the BoM, goBILDA Manual, UDNS Guide, and Node Firmware READMEs.
- **UX Refinement**: Fixed the Databank navigation logic so the Hero droid image only appears on the **Droid Overview (README.md)** page.
- **Hero Image Upgrade**: Switched the primary project overview image to `droid_actual.jpg` for higher fidelity.
- **Sidebar Navigation**: Renamed "Mission Overview" to "Droid Overview" for consistent droid documentation.
- **Imperial Lightbox**: Implemented a "Click-to-Enlarge" modal system for all hardware photos. Table-based images are now automatically scaled to 120px thumbnails for better readability.
- **AI Agent SOP Update**: Formally updated `AGENTS.md` to require localized technical READMEs for all firmware nodes.
- **Component Synchronization**: Unified **PEMENOL 60W (DY-HL50T)** and **ESP32D** naming across BoM and technical manuals.

### Changed
- **Databank Navigation**: Updated `index.html` sidebar to link to Firmware READMEs instead of raw YAML files for enhanced readability.
- **BoM Corrections**: Fixed incorrect hardware links and updated technical descriptions for goBILDA components.

### Fixed
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
- **Node Configuration**: Refactored the droid from a "simple trigger" model to a "Nexus Bus" Serial model.
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
- ESPHome firmware templates for Node 1 (Body Brain).
- Core electrical schematic draft representing the initial 20V power system.
