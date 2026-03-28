# 📜 Project Changelog: Wee2-D2 Imperial Databank

All notable changes to the Wee2-D2 project will be documented in this file. This project adheres to [Semantic Versioning](https://semver.org/) and the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) standard.

---

## [1.0.0-UDNS] - 2026-03-28
### Added
- **Unified Droid Nervous System (UDNS)**: Implemented a high-bandwidth master-slave serial architecture across all 3 nodes.
- **UDNS Technical Documentation**: Created a dedicated explainer and wiring guide for the droid's integrated nervous system.
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
