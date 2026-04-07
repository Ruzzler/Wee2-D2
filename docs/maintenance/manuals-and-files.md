# <i data-lucide="files"></i> Manuals & Files

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: DOCUMENTATION & FILES** | **MODELS: ALL COMPONENTS**


This guide provides quick-access to the technical documentation and firmware configuration files for the Wee2-D2 project. These documents are verified for the `v2.6.0-Dashboard` hardware sequence.


---


## Core Architecture & Node Manuals

These documents cover the high-level design of the droid and the specific pinouts for each microcontroller node.


- [Node Mesh Architecture](../architecture/node-mesh.md)
- [Power Architecture Core](../architecture/power-architecture.md)
- [Node 1: Dome Master Manual](../architecture/node-1-dome-motion.md)
- [Node 2: Sound Hub Manual](../architecture/node-2-sound-hub.md)
- [Node 3: LED Distro Manual](../architecture/node-3-led-distribution.md)


---


## Hardware Specifications (OEM)

Cataloging the physical specifications for the industrial hardware components used in the body and dome drive.


| Component | Manual Link | Type |
| :--- | :--- | :--- |
| **Dome Motor** | [goBILDA 5203](../hardware/gobilda-motor-manual.md) | High-Torque Brushed |
| **Body Drive** | [FLD-5 Hub Motor](../hardware/hub-motor-manual.md) | Brushless Direct-Drive |
| **Power Controller**| [MgcSTEM LVP](../hardware/mgcstem-lvp-r15-manual.md)| Safety Cutoff Relay |
| **Motor Controller**| [Flipsky 6.7 Pro](../hardware/flipsky-fsesc-67-pro-manual.md)| VESC® Compatible |


---


## Firmware Configuration (Source Anchors)

These links point to the verified configuration files used in the `v2.6.0` production deployment.


- **Node 1 (Dome Master)**: [node-1-dome-motion.yaml](../../firmware/production/node-1-dome-motion.yaml)
- **Node 2 (Sound Hub)**: [node-2-sound-hub.yaml](../../firmware/production/node-2-sound-hub.yaml)
- **Drive Settings (Left)**: [left-motor-settings.xml](../../firmware/esc-configs/left-motor-settings.xml)
- **Drive Settings (Right)**: [right-motor-settings.xml](../../firmware/esc-configs/right-motor-settings.xml)


---


## Structural & 3D Components

Managing the physical chassis and mechanical joints for the droid's internal grid.


- **Chassis Files**: Acclaimed 3D files created by Mr. Baddeley.
- **Joint System**: [CNBTR Slip Ring Guide](../hardware/cnbtr-slip-ring-manual.md).
- **Wiring Standards**: [Node Pinout Guide](../architecture/node-pinout-guide.md).


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Troubleshooting](troubleshooting.md)