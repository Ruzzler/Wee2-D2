# <i data-lucide="folder-git"></i> Wee2-D2

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: WEE2-D2** | **VERSION: v2.6.0-FINAL**


Welcome to the **Wee2-D2** repository. This project is a distributed microcontroller mesh designed to power the acclaimed 3D files created by Mr. Baddeley. The droid uses a decentralized logic system (ESPHome) and a high-current power grid to provide cinematic movement and sound.


---


## Project Philosophy

This project is built for high-fidelity technical performance without the need for complex back-end servers. It is a **Wiki-Only** managed repository where the documentation acts as the source-of-truth for the "Golden State" firmware verified for the `v2.6.0-Dashboard` sequence.


1. **Normal Casual Tone**: Use clear, normal, and straightforward language.
2. **Minimalist Aesthetic**: Professional, functional design with high-fidelity typography and Lucide Icons.
3. **Distributed Logic**: Movement (Node 1), Sound (Node 2), and Lighting (Node 3) are handled by separate nodes linked by an ESP-NOW mesh (firmware/production/node-1-dome-motion.yaml:92).


---


## Getting Started: System Overview

To begin working with the Wee2-D2 stack, you should first familiarize yourself with the three primary documentation clusters.


### 1. System Architecture
This cluster covers the core "brain" of the droid, including the interactive schematic and the node mesh communication protocol.
- [Node Mesh Architecture](docs/architecture/node-mesh.md)
- [Power Architecture](docs/architecture/power-architecture.md)
- [Interactive Schematic](docs/architecture/electrical-schematic.md)


### 2. Microcontroller Nodes
This cluster catalogs the physical pinouts and specific logic for the ESP32-S3 and ESP32 hardware.
- [Node 1: Dome Master](docs/architecture/node-1-dome-motion.md)
- [Node 2: Sound Hub](docs/architecture/node-2-sound-hub.md)
- [Node 3: LED Distribution](docs/architecture/node-3-led-distribution.md)


### 3. Maintenance & Operation
This cluster provides step-by-step guides for calibrating the drive system and managing battery runtime during conventions.
- [Battery Runtime Guide](docs/maintenance/battery-runtime-guide.md)
- [System Calibration](docs/maintenance/calibration-guide.md)
- [Troubleshooting](docs/maintenance/troubleshooting.md)


---


## Engineering Standards

1. **Heading Standard**: Use exactly **2 blank lines** before all secondary headers to ensure proper vertical rhythm.
2. **Citation Standard**: All technical documentation must include evidence-based citations in the `(file:line)` format.
3. **Lead-in Rule**: All tables and code blocks must have a descriptive lead-in sentence to prevent visual clumping.
4. **Style Standard**: All visual styling is managed in the central [style.css](system/style.css) file.


---


[View Full Bill of Materials](docs/bill-of-materials.md) | [View Version History](VERSION_HISTORY.md)