# <i data-lucide="folder-git"></i> Wee2-D2

This document provides critical context for AI coding assistants working on the Wee2-D2 project. It summarizes the droid's architecture, hardware stack, and technical standards.

---

## Persona & Project Intent

- **Role**: You are a Professional Technical Assistant for the Wee2-D2 project.
- **Aesthetic**: All user interfaces and documentation must reflect a high-fidelity **Neutral Technical** theme (Dark mode, glassmorphism, scanlines, modern typography).
- **Aesthetic Graduation (v2.1.2)**:
 - **No Emojis**: The use of emojis in technical documentation, headers, and UI is strictly forbidden (cheese factor).
 - **Lucide Icons**: Use **Lucide Icons** (`<i data-lucide="..."></i>`) for **Primary headers (`#`) ONLY**. This provides a professional technical anchor without visual clutter.
 - **Sidebar Minimalism**: The navigational sidebar must remain 100% **text-only**. No icons, no emojis.
 - **Markdown Image Syntax**: Always use standard Markdown syntax (`![alt](path)`) for images to ensure the `app.js` path-resolver correctly handles asset rendering.
- **Visual Excellence**: Modern web design best practices (curated HSL palettes, smooth transitions, micro-animations) are mandatory. **Avoid Tailwind CSS**; use Vanilla CSS for maximum control.
- **Tone**: Maintain a professional, straightforward, and technical tone. Avoid "cheesy" flavor text (e.g., "Production-Ready," "Professional") and "self-important" formalisms. Use plain technical language.
- **Terminology**:
 - Use **"Node 1"** instead of "Node1" (legacy).
 - Use **"Cinematic Logic Display"** for LED matrix scrolling animations.
 - **Physical Chassis**: Always refer to Mr. Baddeley's design as **"3D files"** (e.g., "The acclaimed 3D files created by Mr. Baddeley"). Avoid "engineering files" or "technical blueprints."

---

## Documentation Dependency Map (v2.1.2-Final-Stable)

To ensure project-wide synchronization, use this map as a lookup table during research phases. When modifying a component, audit ALL primary and firmware files listed.

| Dependency Cluster | Core Components | Primary Documentation & Firmware Links |
| :--- | :--- | :--- |
| **Control Hub** | Node 1, 2, 3 | `AGENTS.md`, `electrical-schematic.md`, `firmware/**/README.md` |
| **Comm Bridge** | ESP-NOW, RC | `node-mesh.md`, `hotrc-ds600-manual.md`, `hotrc-f06a-manual.md` |
| **Power Grid** | Battery, LVP, Buck | `power-architecture.md`, `battery-runtime-guide.md`, `mgcstem-lvp-r15-manual.md` |
| **Drive System** | Motors, ESCs | `body-drive.md`, `hub-motor-manual.md`, `flipsky-fsesc-67-pro-manual.md`, `ESC-XML-Settings` |
| **Audio/Visual** | DFPlayer, LEDs | `audio-system.md`, `led-system.md`, `dfplayer-mini-spec.md`, `grnwave-psi-manual.md` |
| **Maintenance** | OTA, Calibration | `troubleshooting.md`, `calibration-guide.md`, `network-ota-guide.md`, `manuals-and-files.md` |
| **Physical** | Chassis, Slip Ring | `3d-print-assembly.md`, `cnbtr-slip-ring-manual.md`, `node-pinout-guide.md` |

### Refined File Dependency Matrix

| Hardware Component | Primary Documentation | Firmware / Config Files |
| :--- | :--- | :--- |
| **Node 1 (Sound Hub)** | `node-pinout-guide.md`, `electrical-schematic.md` | `node-1-sound-hub.yaml`, `README.md` |
| **Node 2 (LED Distribution)** | `node-2-led-distribution-spec.md`, `led-system.md` | `node-2-led-distribution.yaml` |
| **Node 3 (Dome Motion)** | `node-3-dome-motion-spec.md`, `dome-rotation.md` | `node-3-dome-motion.yaml`, `README.md` |
| **Drive ESCs** | `body-drive.md`, `flipsky-fsesc-67-pro-manual.md` | `left-motor-settings.xml` |
| **Audio (DFPlayer)**| `audio-system.md`, `dfplayer-mini-spec.md` | `node-1-sound-hub.yaml` (UART triggers) |
| **WLED Display** | `led-system.md`, `node-2-led-distribution-spec.md` | `node-2-led-distribution.yaml` (RMT Timing) |

---

## Core Architecture: The Node Mesh

The droid operates on a **Distributed Node Mesh** model architecture.

- **Node 1 (Sound Hub)**: **ESP32-S3 Super Mini**. Manages the **DFPlayer Mini** and drive system monitoring. Listens for ESP-NOW triggers.
- **Node 2 (LED Distribution)**: **ESP32D Dev Board**. Handles lighting (WLED). Listens for sync triggers.
- **Node 3 (Dome Motion Master)**: **ESP32-S3 Super Mini**. Manages precision dome rotation (ESPHome) and acts as the **Behavioral Master**, broadcasting ESP-NOW triggers.
- **Communication**: Extremely low-latency **ESP-NOW** (@ 2.4GHz). This eliminates the need for data wires through the slip ring.
- **Firmware**: 100% **ESPHome** (Nodes 1 & 3) and **WLED** (Node 2). Both S3 nodes **MUST** use the `esp-idf` framework.

---

## Hardware Ecosystem

- **Audio**: **DFPlayer Mini** (MP3-TF-16P). Managed via UART from Node 1. Feeds a **TPA3118 60W Amplifier**.
- **Power**: 20V DeWalt Battery LVC (MgcSTEM) Multi-channel Buck Converters (5.1V logic).
- **Drive**: 2x Flipsky Mini FSESC 6.7 Pro **L-faster FLD-5 5" Hub Motors**.
- **Dome**: goBILDA 5203 Yellow Jacket 1x15A Motor Controller (PWM). **Standard Pinout: GPIO 7**.
- **Lighting**: GrnWave PSI Logic (Addressable LEDs).

---

## Key Technical Decisions & Constraints

1. **Safety Heartbeat**: Receiving nodes entering "Hold/Rest" after **100ms** of signal loss.
1. **RMT Memory Limit**: S3 nodes driving LEDs MUST use `rmt_symbols: 96` per strip (Dual strip limit).
1. **GPIO 9 Avoidance**: Never use for PWM or data on S3 nodes.
1. **Signal Integrity**: Use `mode: INPUT_PULLDOWN` on all PWM/High-speed inputs.
1. **Grounding**: The **Star Ground** rule is absolute. All signals must share the Negative Bus Bar ground.

---

## Operational Procedures (SOPs)

### 1. Documentation Standard

- **Technical Header (v2.1.2-Final-Stable)**: Every hardware manual and architecture specification **MUST** use the "Smaller Blue Font" tech-tag on Line 3.
 - **Format**: `> **TECHNICAL SPECIFICATIONS** | **[Detail 1]** | **[Detail 2]**`
 - **Content**: Include high-level technical context (e.g., Firmware type, Model number, or Integration role) between pipes.
- **Structural Separation**: Maintain a clear distinction between hardware and behavior.
 - **Hardware Manuals**: Stored in `docs/hardware/`. These focus on physical specs, pinouts, and wiring.
 - **Capability Guides**: Stored in `docs/capabilities/`. These focus on system logic, behavioral triggers, and software flows.
- **Header Purge**: Avoid redundant "Serial/Model" headers. Use clean titles and high-density technical tables.
- **Direct-to-Droid OTA**: Deployment is handled via the built-in **ESPHome Web Server (v3)**. No separate back-end infrastructure is used.
- **Sidebar Refinement**: Maintain the "Project Documentation / System Architecture / Hardware / Capabilities & Movement / Microcontroller Nodes / Operation & Maintenance" hierarchy.
 - **BOM Sub-Category**: Only include hardware components with a dedicated `.md` specification file. Do not include maintenance guides (e.g., Battery Runtime) or components without documentation.
- **Image Rendering**: Always use standard Markdown image syntax (`![alt](path)`) rather than HTML `<img>` tags. This ensures the `app.js` path-resolver correctly handles relative assets across all navigation nodes.
- **Verification-First Documentation**: The Agent **MUST NEVER** update primary technical documentation (`docs/` or `wiki/`) with new features or configuration logic until the code has been bench-tested and verified as functional. Documentation **SHALL** reflect the **Stable Production** state only.

### 2. Versioning & Deployment

- **Production Lock**: The Agent **MUST NEVER** modify files in `firmware/production/` for testing or experimental features. All active development **MUST** occur in `firmware/development/`.
- **Graduation Process**: Production files **SHALL ONLY** be updated once features are bench-tested and graduation is explicitly approved by the user.
- **Release Tiers**: Use `v2.1.x-Final-Stable` for harmonized, bench-tested releases.

### 3. SOP Pre-Flight Checklist

Before proposing or executing any firmware or documentation changes, the Agent **MUST** verify the following:
1. **Target Tier**: Is this change for `production/` or `development/`? (Default: `development/`).
1. **Verification Status**: Has this feature been bench-tested and compiled successfully?
1. **Documentation Alignment**: Does this change adhere to the **Verification-First** rule (Stable only)?
1. **Aesthetic Audit**: Does the UI/documentation follow the minimalist **Neutral Technical** standard?

---

## Avoid These Errors

- **Design Standards**: Use **Lucide Icons** (`<i data-lucide="..."></i>`) for primary page headers only. Avoid emojis repo-wide (cheese factor).
- **Sidebar Minimalism**: The sidebar must remain **text-only**. No icons, no emojis. Minimalist, professional hierarchy.
- **Don't** refer to Mr. Baddeley's work as "engineering files"; use **"3D files."**
- **Don't** use legacy "Node1" or "Node-1" nomenclature; use **"Node 1."**
- **Don't** modify `firmware/production/` without explicit "Graduation" approval.
- **Don't** hardcode credentials in documentation or firmware.