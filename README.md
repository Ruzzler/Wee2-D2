# <i data-lucide="folder-git"></i> Wee2-D2

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: WEE2-D2 PROJECT** | **VERSION: v2.6.0-STABLE**


Welcome to the **Wee2-D2** project. This repository is a distributed microcontroller mesh designed to power the acclaimed 3D files created by Mr. Baddeley. The droid uses decentralized logic (ESPHome) and a high-current power grid to provide cinematic movement, sound, and lighting visuals.


---


## <i data-lucide="book-open"></i> Project Wiki

The primary documentation for this project is hosted in the [Project Wiki](wiki/project-overview.md). Consult the wiki for technical specifications, node mesh architecture, and hardware manuals.


---


## Project Structure

The project is organized into three primary technical clusters: Architecture, Capabilities, and Hardware. This structure ensures that every droid node and hardware component is documented for the `v2.6.0-Dashboard` sequence.


```text
Wiki-Repository/
├── docs/               # Technical Specifications
│   ├── architecture/   # System Design & Mesh
│   ├── capabilities/   # Movement & Audio Logic
│   ├── hardware/       # Component Manuals & Specs
│   └── maintenance/    # Calibration & Upkeep
├── system/             # Wiki CSS & Visual Engine
├── wiki/               # Project Overviews
└── README.md           # This file
```


---


## <i data-lucide="hard-drive"></i> Hardware Ecosystem

These components are verified for architectural parity with the project's logic stack. Each link directs to a high-density manual including pinouts and wiring.


*   **Piloting**: [HotRC DS-600](docs/hardware/hotrc-ds600-manual.md) (PWM Input to Node 1).
*   **Drive System**: [Flipsky Mini FSESC 6.7 Pro](docs/hardware/hub-motor-manual.md) feeding L-faster Hub Motors.
*   **Dome Motion**: [goBILDA 5203 Yellow Jacket](docs/hardware/gobilda-motor-manual.md) driven by an ESP-S3 Master.
*   **Audio Logic**: [DFPlayer Mini](docs/hardware/dfplayer-mini-spec.md) triggered via ESP-NOW to a [TPA3118 60W Amp](docs/hardware/tpa3118-amp-manual.md).
*   **Power Grid**: [MgcSTEM LVP-R1.5](docs/hardware/mgcstem-lvp-r15-manual.md) with a central Negative Bus Bar.
*   **Lighting**: [GrnWave PSI Logics](docs/hardware/grnwave-psi-manual.md) and WLED array controllers.


---


## <i data-lucide="book-open"></i> Getting Started

Follow the project documentation hierarchically to ensure a stable deployment of the droid logic.


### 1. System Foundations
Review the interactive schematic and the node mesh communication protocol to understand how the body and dome interact.
- [Interactive Electrical Schematic](docs/architecture/electrical-schematic.md)
- [Node Mesh Architecture](docs/architecture/node-mesh.md)
- [Power Architecture](docs/architecture/power-architecture.md)


### 2. Node Configuration
Catalog the physical pinouts and specific logic for the ESP32-S3 and ESP32 hardware.
- [Node Pinout & Wiring Guide](docs/architecture/node-pinout-guide.md)
- [Installing Firmware](docs/maintenance/installing-firmware.md)


### 3. Operation & Safety
Consult the maintenance documentation before convention deployment to ensure battery safety and drive calibration.
- [Battery Runtime Guide](docs/maintenance/battery-runtime-guide.md)
- [System Calibration Guide](docs/maintenance/calibration-guide.md)
- [Safety & Maintenance](docs/maintenance/safety-maintenance.md)


---


[View Full Bill of Materials](docs/bill-of-materials.md) | [View Project Changelog](CHANGELOG.md)