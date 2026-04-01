# <i data-lucide="history"></i> Project Changelog: Wee2-D2 Documentation

All notable changes to the Wee2-D2 project will be documented in this file. This project adheres to [Semantic Versioning](https://semver.org/) and the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) standard.

---

## [1.8.3] - 2026-03-31
### UI Refactor & Documentation Mapping
- **Manuals and Files Hub**: Replaced the legacy `Component Manuals` registry with a consolidated **Manuals and Files** hub. This provides direct download links for latest Firmware (YAML), VESC configs (XML), and Cloud Uplinks for engineering tools.
- **Documentation Dependency Map**: Integrated a project-wide mapping strategy into `AGENTS.md` (v1.8.2 briefing). This establishes a **MANDATORY FIRST STEP** for all AI agents to audit related documentation/firmware clusters before proposing changes.
- **Confusing Metadata Scrub**: Removed decorative but confusing "SERIAL: CAP-..." identifiers across 17+ capability and hardware guides.
- **BOM Cleanup**: Removed redundant "Integrity Check" tips from the Bill of Materials, replacing them with direct links to the Interactive Schematic.

## [1.8.0] - 2026-03-31
### Wireless Bridge Pivot (ESP-NOW)
- **Architectural Shift**: Decommissioned the physical UDNS UART bus (GPIO 16/17) through the slip ring in favor of a distributed **ESP-NOW** wireless bridge.
- **Node Consolidation**: Standardized **MCU 1 (Body)** and **MCU 3 (Dome)** as **ESP32-S3 Super Mini** nodes, utilizing the `esp-idf` framework for stabilized wireless and RMT performance.
- **Audio Overhaul**: Replaced the PEMENOL 60W soundboard with a modular **DFPlayer Mini** (MP3 serial hub) and **TPA3118 60W Amplifier**.
- **EMI Isolation**: Repurposed slip ring circuits **C5 and C6** to "RESERVED" status, effectively isolating all high-speed signal logic from motor-induced EMI by moving to the 2.4GHz spectrum.
- **Passive Body Drive**: Simplified the body electronics by directing RC1 signals straight to the Flipsky ESCs, with the Body S3 now focusing on audio triggering and system telemetry.

## [1.7.5] - 2026-03-31 (Final Harmonization & Tone Scrub)
### Added
- **Technical Standard (v1.7.5)**: Established a project-wide professional tone, scrubbed all "cheesy" or non-functional descriptors (Authentic, Elite, Mission-Ready, Final Boss).
- **Cinematic Logic Standard**: Rebranded LED scrolling as "Cinematic Logic Display".

### Changed
- **Feature Decommissioning**: Fully removed "Angry Mode" from all Documentation documentation, tutorials, and schematics. Reclassified as "High Alert" in internal logic only.
- **Pinout Parity**: Synchronized all READMEs and schematics to the production-verified **GPIO 7** (Dome ESC) and **115200 Baud** (UDNS) standards.
- **Nervous System Template**: Updated the core inter-MCU template to reflect the 115200 baud standard and removed legacy test-bench scripts.

### Fixed
- **Documentation Corruption**: Resolved multiple alignment and injection errors in the `architecture/` and `maintenance/` guides caused by legacy multi-file edit attempts.
- **Firmware Pathing**: Corrected broken link references in the Documentation SPA to point to the new hierarchical firmware READMEs.

---

## [1.7.2] - 2026-03-31 (Dome Control Refinement & Bench Testing)
### Changed
- **UDNS Removal**: Eliminated the UART serial bus and local relay triggers from MCU 3 to simplify the standalone S3 Mini behavioral test suite.
- **Experimental Safety**: Commented out the mandatory 60% voltage clamp across all motor logic (RC and Scripts) to allow for baseline bench testing. **Warning**: Motor is now exposed to full battery bus voltage.

---

## [1.7.0] - 2026-03-31 (S3 Behavioral Update)
### Added
- **ESP32-S3 Performance Pivot**: Upgraded MCU 3 to the S3 Super Mini platform, utilizing the `esp-idf` framework and RMT (Remote Control) peripheral for glitch-free LED driving.
- **Behavioral script Integration**: Integrated advanced autonomous scripts: "Scan Patrol," "Party Dance," and "Mood Logic" (Mechanical Jam simulator).
- **RC High-performance Passthrough**: Implemented instantaneous manual override on GPIO 4 with logic-level stick detection.

### Changed
- **Voltage Safety Enforcement**: Injected a mandatory **0.6 scale factor (60% clamp)** across all motor throttle logic (RC and Scripts) to protect the 12V goBILDA motor from the 20V battery bus.
- **UDNS Restoration**: Re-integrated the 115200 Baud UDNS serial bus (GPIO 16/17) and local relay synchronization.
- **Credential Stripping**: Migrated local Wi-Fi and API credentials to the project's `!secret` logic to prevent accidental public disclosure.

### Fixed
- **PSI Logic Mapping**: Resolved a physical label swap; confirmed GPIO 5 as **Rear PSI** and GPIO 6 as **Front PSI**.

---

## [1.6.2] - 2026-03-31 (Technical Standard & Dome Pivot)
### Added
- **Local Relay Trigger**: Implemented the physical GPIO 27 `switch` in `dome-motion.yaml` to provide a zero-latency sync trigger to the lighting controller.
- **UDNS UART (MCU 3)**: Added the UDNS serial bus component to the Motion Controller for future telemetry and synchronized movement.

### Changed
- **Dome Hardware Pivot**: Standardized all documentation and firmware READMEs to reflect the **ESP32 Dev Board (Standard)** as the official node for the entire droid, replacing the S3 Super Mini.
- **UDNS Baud Parity**: Synchronized all READMEs and architectural docs to the **115200 Baud** Technical Standard (fixing 9600 baud discrepancies).
- **Communication Hardware**: Updated MCU 2 (WLED) documentation to use standard ESP32-D pins (GPIO 16/17) for the UDNS bus instead of S3-specific pins.
- **WLED Framework Sync**: Corrected the Lighting Controller's functional capability documentation to reflect the **WLED** framework instead of ESPHome.

### Fixed
- **Logic Matrix Dimensions**: Corrected swapped Front (10x2) and Rear (12x2) matrix dimensions in the WLED configuration guide.
- **Firmware Redundancy**: Cleaned up and consolidated duplicate `esphome:` blocks in the MCU 3 YAML configuration.

---

## [1.6.0] - 2026-03-29 (UDNS Verification & Behavioral Integration)
### Added
- **Serial Integration Suite**: Implemented 14 diagnostic buttons on the Body Dashboard for "One-Touch" droid emotion testing (Red Alert, Happy, Processing, etc.).
- **Body Wiring Guide**: Created a permanent "Technical Standard" wiring ledger for MCU 1 in `docs/architecture/`.

### Changed
- **UDNS Baud Standard**: Synchronized the serial bridge to **115200 Baud** to match WLED and S3 Mini high-speed logic.
- **Serial JSON Protocol**: Hardened the command strings to utilize WLED's mandatory `\n` delimiter and Segment Array `[]` syntax for 100% reliability.
- **Temporary Node Calibration**: Documented the **GPIO 3 (RX0)** requirement for standard ESP32-D temporary dome test nodes.
- **Mixing Matrix Calibration**: Documented the DS-600 "Mixing Matrix" (Mode 1 for Body, Standard for Dome) to ensure correct Joystick interpretation.

---

## [1.5.0] - 2026-03-29 (Physical Architecture & Pin Remediation)
### Added
- **Finalized Body Wiring Guide**: Created a master reference artifact integrating all user-provided wire colors and logic mappings for MCU 1.
- **UDNS Color Standard**: Established **Yellow/Black (TX)** and **Green/Black (RX)** as the official wiring standard for the 6-circuit slip ring serial bridge.

### Changed
- **Pin Remediation (MCU 1)**: Migrated Sound Triggers S3 and S4 from GPIO 16/17 to **GPIO 26/27** to resolve Hardware UART2 conflicts.
- **RC Channel Realignment**: Updated the Body Controller to utilize **CH5 (GPIO 32)** for bank switching to match the builder's physical receiver data pin mapping.
- **Physical Build Synchronization**: Updated all technical manuals (Schematic, Audio Guide, Firmware READMEs) to reflect the specific wire colors and pin selections.

---

## [1.4.0] - 2026-03-28 (Power Topology & AI Dossier Overhaul)
### Added
> [!IMPORTANT]
> **MANDATORY STAR GROUND RULE**: Every component in the droid (MCUs, ESCs, Receivers, and LED Strips) MUST share a common ground reference. Every ground wire traces back to this central Negative Bus Bar to create a "Star Ground" topology. This is critical for signal integrity; without a shared reference, UART and PWM data signals will become unreadable static.
- **Dual-Line Slip Ring Protocol**: Documented the mechanical isolation of Dome Motor Power (C1/C2) from Dome Logic Power (C3/C4) carrying identical 18 AWG wiring through the 6-circuit hub.
- **BEC Logic Tapping**: Diagramed the explicit routing of 5V power from the Flipsky and goBILDA ESC internal BECs directly to the HOTRC Receivers and MCUs.

### Changed
- **Architectural Hierarchy**: Shifted documentation structure from component-focus to capability-focus (Lights & Sounds vs Movement).
- **Mermaid Standardization**: Hardened the unified electrical schematic by migrating from `graph TD` to modern `flowchart TD`, moving all `classDef` styling parameters to EOF, and scrubbing symbols to ensure zero parser crashes on strict offline viewers.
- **Personal Linguistics**: Rewrote the entire project repository (from collective pronouns to 'I') to accurately attribute the custom engineering to a single builder.
- **AI Directives**: Expanded `AGENTS.md` with explicit hardware mandates (Star Ground rules, capability structural logic, and Mermaid formatting bans).
- **Hero Image Integration**: Replaced the native Markdown README entrance block with an HTML-scaled `droid-actual.jpg` and scrubbed duplicate fixed-layout instances from the `index.html` Documentation HUD wrapper.

## [1.3.0] - 2026-03-28 (Diatáxis UX Overhaul)
### Changed
- **Navigation Flow**: Reorganized the Documentation sidebar to follow the Builder's Journey (Overview > Architecture > Wiring > Firmware > Maintenance).
- **Component Manuals De-clutter**: Removed the standalone 8-link component manual section from the sidebar. Users now click through via the BoM or Interactive Schematic, adhering to optimal Information Architecture.
- **Clarified Project Scope**: Updated `README.md` to explicitly state the Documentation handles electronics only, not 3D printing.
- **Architecture Consolidation**: Removed the bulky Mermaid graph from `README.md` in favor of pointing back to the dedicated `electrical-schematic.md` interface.
- **Local Server Standardization**: Enforced port `8001` with loopback IP across all documentation to prevent Windows IPv6 binding conflicts.
- **History API**: Rewrote navigation in `app.js` to utilize browser PopState for functional forward/back buttons and hash routing.

## [1.2.0] - 2026-03-28 (Tiered Technical Standard)
### Added
- **BoM Layout Upgrade**: Transitioned to a 4-column layout with a dedicated **"Visual ID"** column. All component images are now isolated and clickable via the Lightbox.
- **Hardware Asset Enrichment**: Integrated missing hardware photos for the PEMENOL 60W Soundboard and goBILDA ESC into the primary component ledger.
- **Architectural Subcategories**: Implemented a 3-pillar tiered hierarchy: `docs/architecture`, `docs/hardware`, and `docs/maintenance`.

### Changed
- **Folder Normalization**: Migrated all system-wide guides to `architecture/` and component manuals to `hardware/`.
- **BoM Consolidation**: Unified the Bill of Materials to `docs/bill-of-materials.md` and updated all internal links.
- **Asset Normalization**: Synchronized all file naming to lowercase-hyphenated (e.g., `droid-actual.jpg`).
- **Sidebar Revamp**: Redesigned the Navigation Menu to reflect the new tiered categorization.
- **UX Refinement**: Fixed the Documentation navigation logic so the Hero droid image only appears on the **Droid Overview (README.md)** page.
- **Hero Image Upgrade**: Switched the primary project overview image to `droid-actual.jpg` for higher fidelity.
- **Sidebar Navigation**: Renamed "Mission Overview" to "Droid Overview" for consistent documentation.

## [1.1.0] - 2026-03-28 (WikiSync & PDFAssist)
### Added
- **Battery Endurance Estimation**: Created **`docs/maintenance/battery-runtime-guide.md`** with duty cycle calculations.
- **Firmware**: 100% **ESPHome**. Integrated with **Home Assistant** and support for **OTA (Over-The-Air)** updates. 
 * *Note*: MCU 3 (ESP32-S3) **MUST** use the `esp-idf` framework to ensure RMT peripheral stability for high-density LED arrays.
- **Hardware Photo Integration**: Migrated and optimized raw assets to permanent project directory.
- **Enhanced Documentation**: Integrated technical photos into manuals and the BoM.

### Changed
- **Documentation Navigation**: Updated `index.html` sidebar to link to Firmware READMEs instead of raw YAML files for enhanced readability.
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
- **Documentation UI**: Launched the custom SPA (Single Page Application) for technical documentation.

### Changed
- **MCU Configuration**: Refactored the droid from a "simple trigger" model to a "Nexus Bus" Serial model.
- **Mobile Responsiveness**: Optimized the entire Documentation UI for desktop and high-density mobile displays.
- **Path Resolution**: Improved the SPA routing to handle GitHub Pages subdirectories (`/Wee2-D2/`) automatically.

### Fixed
- **CSS Linting**: Resolved nested media query bracket issues in `style.css`.
- **Image Performance**: Implemented metadata stripping for all imported technical photos to optimize site load speed.

---

## [0.5.0-Initial] - 2026-03-21
### Added
- Initial project structure including Markdown documentation and Mermaid diagrams.
- Basic Bill of Materials (BOM) following the Star Wars aesthetic.
- ESPHome firmware templates for MCU 1 (Body Controller).
- Core electrical schematic draft representing the initial 20V power system.
