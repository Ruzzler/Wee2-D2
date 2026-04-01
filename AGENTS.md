# 🤖 AI Agent Briefing: Wee2-D2 Imperial Databank

This document provides critical context for AI coding assistants working on the Wee2-D2 project. It summarizes the droid's architecture, hardware stack, and historical technical decisions.

---

## 🏛️ Persona & Project Intent
*   **Role**: You are an Imperial Astromech Engineering Assistant.
*   **Aesthetic**: All user interfaces and documentation must reflect a high-fidelity **Star Wars Imperial Databank** theme (Dark mode, glassmorphism, scanlines, modern typography).
*   **Visual Excellence**: Modern web design best practices (curated HSL palettes, smooth transitions, micro-animations) are mandatory. **Avoid Tailwind CSS**; use Vanilla CSS for maximum control.
*   **Tone**: Maintain a professional, straightforward, and matter-of-fact tone. Avoid "cheesy" flavor text (e.g., "Mission-Ready," "Elite," "Authentic") and "stuffy" formalisms (e.g., "Technical Engineering Standard"). Use plain technical language.
*   **Terminology**: 
    *   Use **"High Alert"** instead of "Angry Mode" (though behavioral descriptions like "Happy" or "Droid Thinking" are acceptable for specific alerts/animations).
    *   Use **"Cinematic Logic Display"** for LED matrix scrolling animations.

---

## 📊 Databank Dependency Map (v2.1.0-Zero-Infra)
To ensure project-wide synchronization, use this map as a lookup table during research phases. When modifying a component, audit **ALL** primary and firmware files listed.

| Version | Date | Milestone | Status | Nodes | Base |
| :--- | :--- | :--- | :--- | :--- | :--- |
| v2.1.0-Zero-Infra | 2026-03-31 | **The Zero-Infra Pivot** | Stable | [Node 1, 2, 3] | [v2.0.0-Hybrid] |
| v2.0.0-Hybrid | 2026-03-31 | **The Automated Pipeline** | Stable-Legacy | [Node 1, 3] | [v1.8.4-Legacy] |

| Dependency Cluster | Core Components | Primary Documentation & Firmware Links |
| :--- | :--- | :--- |
| **🧠 Control Hub** | MCU 1, 2, 3 | `AGENTS.md`, `electrical-schematic.md`, `firmware/**/README.md` |
| **📡 Comm Bridge** | ESP-NOW, RC | `unified-nervous-system.md`, `hotrc-ds600-manual.md`, `hotrc-f06a-manual.md` |
| **⚡ Power Grid** | Battery, LVP, Buck | `power-architecture.md`, `battery-runtime-guide.md`, `mgcstem-lvp-r15-manual.md` |
| **🛞 Drive System** | Motors, ESCs | `body-drive.md`, `hub-motor-manual.md`, `flipsky-fsesc-67-pro-manual.md`, `ESC-XML-Settings` |
| **🔊 Audio/Visual** | DFPlayer, LEDs | `audio-system.md`, `led-system.md`, `dfplayer-mini-manual.md`, `grnwave-psi-manual.md` |
| **🔧 Maintenance** | OTA, Calibration | `troubleshooting.md`, `calibration-guide.md`, `network-ota-guide.md`, `manuals-and-files.md` |
| **🏗️ Physical** | Chassis, Slip Ring | `3d-print-assembly.md`, `cnbtr-slip-ring-manual.md`, `body-wiring-guide.md` |

### 🛰️ Refined File Dependency Matrix

| Hardware Component | Primary Documentation | Firmware / Config Files |
| :--- | :--- | :--- |
| **Node 1 (Sound Hub)** | `node-pinout-guide.md`, `electrical-schematic.md` | `node-1-sound-hub.yaml`, `README.md` |
| **Node 3 (Dome Motion)** | `dome-rotation.md`, `electrical-schematic.md` | `node-3-dome-motion.yaml`, `README.md` |
| **Drive ESCs** | `body-drive.md`, `flipsky-fsesc-67-pro-manual.md` | `left-motor-settings.xml` |
| **Audio (DFPlayer)**| `audio-system.md`, `dfplayer-mini-manual.md` | `node-1-sound-hub.yaml` (UART triggers) |
| **WLED Display** | `led-system.md`, `grnwave-psi-manual.md` | `node-2-led-distribution.yaml` (RMT Timing) |

---

## 🧠 Core Architecture: Wireless Bridge (ESP-NOW)
The droid operates on a **Distributed Wireless Trigger** model called the **Wireless Bridge**.

*   **MCU 1 (Body Hub)**: **ESP32-S3 Super Mini**. Manages the **DFPlayer Mini** and drive system monitoring. Listens for ESP-NOW triggers.
*   **MCU 2 (Dome Lights)**: **ESP32D Dev Board**. Handles lighting (WLED). Listens for sync triggers.
*   **MCU 3 (Dome Master)**: **ESP32-S3 Super Mini**. Manages precision dome rotation (ESPHome) and acts as the **Behavioral Master**, broadcasting ESP-NOW triggers.
*   **Communication**: Extremely low-latency **ESP-NOW** (@ 2.4GHz). This eliminates the need for data wires through the slip ring.
*   **Firmware**: 100% **ESPHome** (MCUs 1 & 3) and **WLED** (MCU 2).
    *   *Note*: Both S3 nodes **MUST** use the `esp-idf` framework to ensure RMT and ESP-NOW stability.

---

## 🛠️ Hardware Ecosystem
*   **Audio**: **DFPlayer Mini** (MP3-TF-16P). Managed via UART from MCU 1 (Body). Feeds a **TPA3118 60W Amplifier**.
*   **Power**: 20V DeWalt Battery ➔ LVC (MgcSTEM) ➔ Multi-channel Buck Converters (5.1V logic).
*   **Drive**: 2x Flipsky Mini FSESC 6.7 Pro ➔ **L-faster FLD-5 5" Hub Motors**.
*   **Dome**: goBILDA 5203 Yellow Jacket ➔ 1x15A Motor Controller (PWM). **Standard Pinout: GPIO 7**.
*   **Lighting**: GrnWave PSI Logic (Addressable LEDs).

---

## 📜 Key Technical Decisions & Constraints

### 1. ESP32-S3 Super Mini Constraints (MCU 3 Specific)
*   **RMT Memory Limit**: The S3 has 192 RMT symbols. Driving dual WS2812 strips requires an explicit `rmt_symbols: 96` split per strip to prevent CPU crashes.
*   **GPIO 9 Avoidance**: Internally connected to the SPI flash bus. Do not use for data/PWM.
*   **Wi-Fi Power**: Limit to `8.5dB` to prevent antenna saturation on compact boards.

### 2. General Engineering Standards (System-Wide)
*   **Update Interval**: Mandatory `50ms` on RC/Motion sensors for real-time response.
*   **Signal Integrity**: Use `mode: INPUT_PULLDOWN` on all PWM/high-speed logic inputs.
*   **Grounding**: The **Star Ground** rule is absolute. All signal-carrying components must share a common ground reference via the Negative Bus Bar.
*   **Log Filtering**: Use `delta` filtering on analog sensors to suppress micro-jitter.
*   **Security**: **NEVER** hardcode credentials (SSID, Password, API Key). Use the `!secret` logic and `secrets.yaml` architecture.

### 3. Historical Record
1.  **3-MCU Split**: Moved from single large ESP to 3 distributed nodes to minimize wiring through the slip ring and isolate motor noise.
2.  **S3 Pivot**: Standardized on the ESP32-S3 for the dome to utilize natively supported RMT peripherals for LED driving.
3.  **17.5V Safety Floor**: Established 17.5V (3.5V/cell) as the standard for battery cutoffs to ensure cell longevity.
4.  **Voltage Clamping**: Mandatory 60% software throttle clamp for the 12V dome motor when running on 20V (Currently disabled for testing).
5.  **Wireless Bridge Shift**: Decommissioned the physical serial bus (UDNS) in favor of the **ESP-NOW** wireless bridge to isolate analog audio noise from motor EMI.

---

## 🚫 Avoid These Errors
*   **Don't** use placeholders for images; use the real hardware photos.
*   **Don't** use "nonsense" text or cheesy labels. Keep it technical.
*   **Don't** suggest using GPIO 9 on S3 boards.
*   **Don't** forget the RMT memory split when adding LED strips to an S3.
*   **Don't** hardcode Wi-Fi credentials or API keys.

---

## 🛠️ Operational Procedures (SOPs)

### 1. Development & Documentation
*   **MANDATORY FIRST STEP: Check the Databank Dependency Map**. Before performing ANY research, analysis, or modification, the agent **MUST** audit the relevant files listed in the `Databank Dependency Map`.
*   **Documenting New Components**: Markdown first, add to `index.html` sidebar, use industrial formatting.
*   **Energy Sync**: Major hardware changes MUST trigger a review of the battery runtime guide.
*   **Optimization**: Prefer WebP/Lossy JPEG. Strip EXIF metadata from all user photos.
*   **Deployment**: Use port `8001` for local testing. Use version query strings (e.g., `?v=v20`) for cache-busting on GitHub.

### 3. Firmware Versioning & Backup (v2.1.2-Final)
To ensure droid stability and zero-infrastructure deployment:
*   **Modular Architecture**: All firmware inherits from `firmware/common/`.
    *   `base-config.yaml`: Unified Web Server (v3), Captive Portal, and API.
    *   `s3-defaults.yaml`: S3-specific framework/RMT protections.
*   **Direct-to-Droid OTA**:
    - **GitHub Cloud**: Compiles code and attaches `.bin` files to a **GitHub Release**.
    - **Web Dashboard**: Use the droid's local IP (e.g., `http://wee2d2-sound.local/`) to drag-and-drop its latest firmware binary.
*   **The Workflow**:
    1.  **Develop** in `development/`.
    2.  **Verify** via bench test on a spare ESP32.
    3.  **Graduate** to `production/` for active deployment.
    4.  **Tag Push**: Pushing to `production/` triggers a GitHub Release with `.bin` artifacts.

### 4. Release & Versioning Strategy (Global)
*   **Pre-Harmonization Snapshot**: A `vX.X.X-Legacy` tag **MUST** be created and pushed to GitHub before any major structural refactor, tone-scrub, or decommissioning of established features.
*   **Verified Releases**: Create a primary version tag (e.g., `v1.7.0`) ONLY after the associated firmware has been successfully bench-tested on physical hardware.
*   **Commit Batching**: Accumulate changes locally. Push to `main` as a cohesive version update that matches a new entry in `CHANGELOG.md`.
*   **Rollback Baseline**: If multiple agents or complex changes are active, create a temporary baseline tag on `origin/main` as a safety-catch before pushing a major batch.
