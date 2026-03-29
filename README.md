# Wee2-D2: Mr. Baddeley Big Baby Astromech

Welcome to the official repository for **Wee2-D2**. Built in 2025 as part of the **Badlands Droid Builders** and the **501st Legion's Badlands Garrison**, this active-duty astromech is frequently deployed to community events for both organizations. The physical chassis was meticulously 3D printed utilizing the acclaimed Mr. Baddeley engineering files.

This specific repository tracks the subsequent high-current electrical architecture, firmware configurations, and hardware documentation required to bring the droid's decentralized control system to life.
## 🛰️ Technical Wiki: Imperial Databank
To view the documented system with a premium, interactive "Mission Control" interface, visit the official Technical Wiki:
👉 **[Wee2-D2 Databank (Wiki)](https://ruzzler.github.io/Wee2-D2/)**

---

## 🚀 Project Overview
Wee2-D2 uses a decentralized architecture across three ESP32 microcontrollers to ensure non-blocking operation of audio, lighting, and mechanical systems. The droid is controlled via **Dual HOTRC DS-600 transmitters** (one for drive, one for dome) for maximum reliability during events.

### 🧠 System MCUs
- **MCU 1: Body Controller (Audio & Dispatch)**: ESPHome-based controller for RC signal processing, bank-switching, and audio triggering.
- **MCU 2: Lighting Controller (WLED)**: Dedicated WLED instance for WS2812 addressable LED light shows with safety current limiting.
- **MCU 3: Motion Controller (ESPHome)**: Precise motor control for dome rotation with safety voltage clamping (20V battery to 12V motor).

> [!WARNING]
> **PROJECT SCOPE**: This repository exclusively documents the custom **Electrical Architecture** and **Firmware** ecosystem. It does **not** contain the 3D-printable STL files or mechanical assembly instructions for the droid chassis itself. Please refer to the official Mr. Baddeley Patreon or Group for structural files.

## 🔋 Master Power Architecture

The Wee2-D2 is natively powered by **DeWalt 20V Batteries** running through an LVP-R1.5 low-voltage cutoff to a primary distribution bus.

👉 **[View the Interactive Electrical Schematic](#docs/architecture/electrical-schematic.md)**
👉 **[View the Power Architecture Deep-Dive](#docs/architecture/power-architecture.md)**

## 📁 Repository Structure
```text
├── docs/               # Technical Documentation
│   ├── architecture/   # System-wide logic (Wiring, Power, UDNS)
│   ├── hardware/       # Component Manuals (Manuals & PDFs)
│   ├── maintenance/    # Operational & Safety standards
│   ├── archive/        # Legacy test and research assets
│   └── bill-of-materials.md # Unified Component Ledger
├── firmware/           # Microcontroller Code
├── system/             # Databank Engine (SPA Logic & Styles)
├── assets/             # Normalized Hardware Assets
├── index.html          # Databank HUD (Entry Point)
└── README.md           # This file
```

## 🦿 Hardware Ecosystem
*   **Control**: 2x [HOTRC DS-600](./docs/hardware/hotrc-ds600-manual.md) (Silent Mode mod).
*   **Drive System**: 2x [Flipsky Mini FSESC 6.7 Pro](./docs/hardware/flipsky-fsesc-67-pro-manual.md) ➔ L-faster Hub Motors.
*   **Motion Controller**: [goBILDA 5203 Yellow Jacket](./docs/hardware/gobilda-motor-manual.md) ➔ [1x15A Motor Controller](./docs/hardware/gobilda-motor-manual.md).
*   **Audio**: [PEMENOL 60W (DY-HL50T)](./docs/hardware/pemenol-60w-voice-manual.md) (60W Mono).
*   **Power Protection**: [MgcSTEM LVP-R1.5](./docs/hardware/mgcstem-lvp-r15-manual.md) (40A Cutoff).
*   **Lighting**: [GrnWave Circular PSI](./docs/hardware/grnwave-psi-manual.md) (76-LED Inward Spiral).

---

## 🏛️ Local Deployment
To run the Databank engine locally via Python:
1.  Open a terminal in the project root.
2.  Run the local server: `python -m http.server 8001 --bind 127.0.0.1`
3.  Navigate to [http://127.0.0.1:8001](http://127.0.0.1:8001).
