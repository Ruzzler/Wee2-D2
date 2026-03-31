<img src="assets/droid-actual.jpg" alt="Wee2-D2 Hero" width="400">

# Wee2-D2: Mr. Baddeley Big Baby Astromech

Welcome to the official repository for **Wee2-D2**. I built this droid in 2025 as an active-duty astromech for the **Badlands Droid Builders** and the **501st Legion's Badlands Garrison**, frequently deploying it to community events. The physical chassis was meticulously 3D printed utilizing the acclaimed engineering files created by Mr. Baddeley.

This repository tracks the subsequent high-current electrical architecture, firmware configurations, and custom hardware documentation I engineered to bring the droid's decentralized control system to life.

## 🛰️ Technical Wiki: Imperial Databank
To view my documented system with a premium, interactive "Mission Control" interface, visit the official Technical Wiki:
👉 **[Wee2-D2 Databank (Wiki)](https://ruzzler.github.io/Wee2-D2/)**

---

## 🚀 Project Overview
I designed Wee2-D2 utilizing a decentralized architecture split across three ESP32 microcontrollers. This ensures non-blocking operation between the heavy audio processing, intricate LED lighting, and mechanical drive systems. The droid is piloted via **Dual HOTRC DS-600 transmitters** (one for drive logic, one for dome motion) for absolute reliability during crowded events.

### 🧠 Unified Droid Nervous System (UDNS)
- **MCU 1: Body Controller (Audio & Dispatch)**: **38-pin** ESP32 Dev Board capturing RC signals, managing the S1-S9 sound triggers, and broadcasting UDNS commands @ **115200 Baud**.
- **MCU 2: Lighting Controller (WLED)**: Standard **ESP32 Dev Board** running WLED for high-density addressable light matrices.
- **MCU 3: Motion Controller (ESPHome)**: Standard **ESP32 Dev Board** managing dome rotation with 60% voltage clamping and local relay triggers.

> [!WARNING]
> **PROJECT SCOPE**: This repository exclusively documents my custom **Electrical Architecture** and **Firmware** ecosystem. It does **not** contain the 3D-printable STL files or mechanical assembly instructions for the droid chassis itself. Please refer to the official Mr. Baddeley Patreon or group hubs for structural files.

## 📁 Repository Structure
```text
├── docs/               # Technical Documentation
│   ├── capabilities/   # Functional guides (Lights, Sounds, Movement)
│   ├── architecture/   # System-wide logic (Wiring, UDNS Bus)
│   ├── hardware/       # Component Manuals (Raw PDFs)
│   ├── maintenance/    # Operational & Safety standards
│   └── bill-of-materials.md # Unified Component Ledger
├── firmware/           # Microcontroller Code (ESPHome)
├── system/             # Databank Engine (SPA Logic & Styles)
├── assets/             # Normalized Hardware Visuals
├── index.html          # Databank HUD (Entry Point)
└── README.md           # This file
```

## 🦿 Hardware Ecosystem
*   **Piloting**: 2x [HOTRC DS-600](docs/hardware/hotrc-ds600-manual.md) (Silent Mode mod).
*   **Drive System**: 2x [Flipsky Mini FSESC 6.7 Pro](docs/hardware/flipsky-fsesc-67-pro-manual.md) feeding L-faster Hub Motors.
*   **Dome Motion**: [goBILDA 5203 Yellow Jacket](docs/hardware/gobilda-motor-manual.md) driven by a [1x15A Motor Controller](docs/hardware/gobilda-motor-manual.md).
*   **Audio**: [PEMENOL 60W (DY-HL50T)](docs/hardware/pemenol-60w-voice-manual.md) running to a Pyle 60W Dual Cone driver.
*   **Power Hub**: [MgcSTEM LVP-R1.5](docs/hardware/mgcstem-lvp-r15-manual.md) mapping to a Positive Blade Fuse Box and central Negative Bus Bar.
*   **Lighting**: [GrnWave Circular PSIs](docs/hardware/grnwave-psi-manual.md) and custom logic arrays.

---
📅 **[View Project Changelog](CHANGELOG.md)**
