# <i data-lucide="folder-git"></i> Wee2-D2: Imperial Databank
> **v2.1.2-FINAL-STABLE**

This document provides critical context for AI coding assistants working on the Wee2-D2 project. It summarizes the droid's architecture, hardware stack, and technical standards.

---

## Persona & Project Intent
*   **Role**: You are a Professional Technical Assistant for the Wee2-D2 project.
*   **Aesthetic**: All user interfaces and documentation must reflect a high-fidelity **Star Wars Imperial Databank** theme (Dark mode, glassmorphism, scanlines, modern typography).
*   **Visual Excellence**: Modern web design best practices (curated HSL palettes, smooth transitions, micro-animations) are mandatory. **Avoid Tailwind CSS**; use Vanilla CSS for maximum control.
*   **Tone**: Maintain a professional, straightforward, and technical tone. Avoid "cheesy" flavor text (e.g., "Mission-Ready," "Elite," "Imperial Command") and "self-important" formalisms. Use plain technical language.
*   **Terminology**: 
    - Use **"High Alert"** instead of "Angry Mode".
    - Use **"Cinematic Logic Display"** for LED matrix scrolling animations.
    - **Physical Chassis**: Always refer to Mr. Baddeley's design as **"3D files"** (e.g., "The acclaimed 3D files created by Mr. Baddeley"). Avoid "engineering files" or "technical blueprints."

---

## Databank Dependency Map (v2.1.2-Final-Stable)
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

*   **Node 1 (Sound Hub)**: **ESP32-S3 Super Mini**. Manages the **DFPlayer Mini** and drive system monitoring. Listens for ESP-NOW triggers.
*   **Node 2 (LED Distribution)**: **ESP32D Dev Board**. Handles lighting (WLED). Listens for sync triggers.
*   **Node 3 (Dome Motion Master)**: **ESP32-S3 Super Mini**. Manages precision dome rotation (ESPHome) and acts as the **Behavioral Master**, broadcasting ESP-NOW triggers.
*   **Communication**: Extremely low-latency **ESP-NOW** (@ 2.4GHz). This eliminates the need for data wires through the slip ring.
*   **Firmware**: 100% **ESPHome** (Nodes 1 & 3) and **WLED** (Node 2). Both S3 nodes **MUST** use the `esp-idf` framework.

---

## Hardware Ecosystem
*   **Audio**: **DFPlayer Mini** (MP3-TF-16P). Managed via UART from Node 1. Feeds a **TPA3118 60W Amplifier**.
*   **Power**: 20V DeWalt Battery ➔ LVC (MgcSTEM) ➔ Multi-channel Buck Converters (5.1V logic).
*   **Drive**: 2x Flipsky Mini FSESC 6.7 Pro ➔ **L-faster FLD-5 5" Hub Motors**.
*   **Dome**: goBILDA 5203 Yellow Jacket ➔ 1x15A Motor Controller (PWM). **Standard Pinout: GPIO 7**.
*   **Lighting**: GrnWave PSI Logic (Addressable LEDs).

---

## Key Technical Decisions & Constraints
1.  **Safety Heartbeat**: Receiving nodes entering "Hold/Rest" after **100ms** of signal loss.
2.  **RMT Memory Limit**: S3 nodes driving LEDs MUST use `rmt_symbols: 96` per strip (Dual strip limit).
3.  **GPIO 9 Avoidance**: Never use for PWM or data on S3 nodes.
4.  **Signal Integrity**: Use `mode: INPUT_PULLDOWN` on all PWM/High-speed inputs.
5.  **Grounding**: The **Star Ground** rule is absolute. All signals must share the Negative Bus Bar ground.

---

## Operational Procedures (SOPs)
### 1. Documentation Standard
*   **Header Purge**: Avoid "Serial/Model" headers in documentation. Use clean titles and high-density technical tables.
*   **Direct-to-Droid OTA**: Deployment is handled via the built-in **ESPHome Web Server (v3)**. No separate back-end infrastructure is used.
*   **Sidebar Refinement**: Mantain the "Project Documentation / System Architecture / Hardware / Capabilities & Movement / Microcontroller Nodes / Operation & Maintenance" hierarchy (e.g., replace 'Behavioral Logic' with '**Automations**').
*   **Image Rendering**: Always use standard Markdown image syntax (`![alt](path)`) rather than HTML `<img>` tags. This ensures the `app.js` path-resolver correctly handles relative assets across all navigation nodes.

### 2. Versioning & Deployment
*   **Production Graduation**: All active code is localized in `firmware/production/`.
*   **Release Tiers**: Use `v2.1.x-Final-Stable` for harmonized, bench-tested releases.

---

## 🚫 Avoid These Errors
*   **Design Standards**: Use **Lucide Icons** (`<i data-lucide="..."></i>`) for primary page headers only. Avoid emojis repo-wide (cheese factor).
*   **Sidebar Minimalism**: The sidebar must remain **text-only**. No icons, no emojis. Minimalist, professional hierarchy.
*   **Don't** refer to Mr. Baddeley's work as "engineering files"; use **"3D files."**
*   **Don't** use legacy "MCU 1/2/3" nomenclature; use **"Node 1/2/3."**
*   **Don't** hardcode credentials in documentation or firmware.
