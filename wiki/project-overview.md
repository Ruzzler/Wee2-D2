![wee2d2-hero](../assets/droid-actual.jpg)


# <i data-lucide="book-open"></i> Project Overview

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: PROJECT OVERVIEW** | **VERSION: v2.6.0-STABLE**


Welcome to the official repository for **Wee2-D2**, a custom-built, active-duty astromech built in 2025 for use in the **Badlands Droid Builders** and the **501st Legion's Badlands Garrison**. This repository documents the custom **Electrical Architecture**, **firmware** configurations, and custom hardware documentation I engineered to bring the droid's decentralized logic to life. This project supports the acclaimed 3D files created by Mr. Baddeley.


---


## System Architecture (Distributed Logic)

Unlike traditional single-processor droids, Wee2-D2 uses three separate microcontroller nodes to handle parallel functions. This decentralization prevents motor noise from affecting the audio and lighting systems.


- **Node 1 (Dome Master)**: Manages dome rotation, RC inputs, and logic communication (firmware/production/node-1-dome-motion.yaml:11).
- **Node 2 (Sound Hub)**: Manages the DFPlayer Mini and hosts the Web Dashboard (firmware/production/node-2-sound-hub.yaml:43).
- **Node 3 (LED Distro)**: Dedicated WLED controller for all addressable dome lighting. 


---


## Core Hardware Stack

The droid is built using high-performance industrial components to ensure reliable operation during long convention days. These components are verified for the `v2.6.0` firmware.


| Category | Component | Specification | Citation |
| :--- | :--- | :--- | :--- |
| **Logic** | ESP32-S3 Super Mini | Dual-Core / 2.4GHz Wi-Fi | [Node 1 Manual](../docs/architecture/node-1-dome-motion.md) |
| **Drive** | FLD-5 Hub Motors | Direct-Drive / 15A Soft Clamp | [Drive Guide](../docs/capabilities/body-drive.md) |
| **Power** | DeWalt 20V System | Ganged Trunk / 17.5V Cutoff | [Power Guide](../docs/architecture/power-architecture.md) |
| **Visuals** | GrnWave PSI | Addressable WS2812B Array | [LED Guide](../docs/capabilities/led-system.md) |


---


## Communication & Mesh Protocol

Wireless communication between the body and dome is handled by the **ESP-NOW** bridge. This eliminates the need for data wires through the slip ring, reducing rotational friction.


1. **Broadcast Triggers**: Node 1 pushes 1-byte command (firmware/production/node-1-dome-motion.yaml:81) over the 2.4GHz radio mesh.
2. **Dashboard Relay**: Node 2 relays dashboard triggers back to Node 1 for autonomous animations. 
3. **Lighting Sync**: Node 1 pushes a separate UART string to Node 3 for visual preset alignment.


---


---


[View Master Schematic](../docs/architecture/electrical-schematic.md) | [View Bill of Materials](../docs/bill-of-materials.md)