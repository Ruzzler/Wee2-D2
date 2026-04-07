# <i data-lucide="share-2"></i> Node Mesh Architecture

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: DISTRIBUTED ESP-NOW MESH** | **PROTOCOL: 2.4GHz P2P**


This guide explains how the droid communicates internally using a distributed messaging system.


The droid's movement is handled by a **Decentralized Node Mesh** consisting of three primary ESP32-S3 controllers. This design handles high-amperage motor control, precision dome rotation, and cinematic AV triggers while minimizing physical wiring through the central slip ring.


---


## System Roles

Synchronization is achieved using low-latency **ESP-NOW** wireless bridging across three specialized nodes. This protocol (firmware/production/node-1-dome-motion.yaml:92) ensures <10ms latency for motion-critical commands.


### Node 1: Dome Motion Master (ESP32-S3)

- **Role**: Master Automations and movement control.
- **Hardware**: goBILDA 5203 Dome Motor, PWM Motor Controller.
- **Logic**: Reads raw RC steering. Captures ESP-NOW dashboard triggers (`0xA0`, `0xA1`, `0xA2`) from Node 2. Broadcasts a 60-second WLED heartbeat (via UART) and 5-second radio heartbeat (firmware/production/node-1-dome-motion.yaml:115).


### Node 2: Neural Command Center (ESP32-S3)

- **Role**: Dashboard Gateway and behavioral audio execution.
- **Hardware**: DFPlayer Mini, TPA3118 Amplifier.
- **Logic**: Hosts the interactive Web UI. Captures user commands and securely relays them across the ESP-NOW bridge to Node 1 for final execution.


### Node 3: LED Distribution (ESP32)

- **Role**: Cinematic visual output.
- **Hardware**: Addressable LED matrices (WS2812B/PSI Logic).
- **Sync**: A **UART-synced** node that receives serial JSON triggers from **Node 1 (Dome Master)** on the dedicated logic bus (firmware/production/node-1-dome-motion.yaml:137). 
- **Framework**: Native WLED (v0.14+).


---


## The Wireless Bridge (ESP-NOW)

To prevent analog audio interference and reduce the risk of slip ring data corruption, the Behavioral Mesh (Nodes 1 and 2) uses **ESP-NOW**, a high-speed 2.4GHz peer-to-peer protocol. Node 3 does not participate in the wireless mesh to maintain maximum radio bandwidth for timing-critical dome and audio triggers.


- **Update Frequency**: **50ms** (Internal Heartbeat) for real-time behavioral response.
- **Security**: **MAC-Address Binding** (Hardware-locked in `base-config.yaml`) to prevent mesh hijacking.
- **Zero Router Latency**: Nodes communicate directly with <10ms response times.
- **EMI Immunity**: Moving movement data to the 2.4G spectrum eliminates the ground loops and motor interference inherent in slip rings.
- **Scalability**: New nodes (e.g., foot sensors or Cinematic Logic Displays) can be added to the mesh without pulling additional wires through the central joint.


---


## Distributed Network Topology

The **CNBTR Slip Ring** (6-Circuit) acts as the physical bridge for the dome's high-current requirements. We use the **Dual-Circuit Isolation Strategy** defined in the [Power Architecture](power-architecture.md):


| Circuit | Role | Current (Peak) | Destination |
| :--- | :--- | :---: | :--- |
| **C1 / C2** | **Ganged 20V Trunk** | 10.0A | **High-Power**: To 20V Wago Hub |
| **C3 / C4** | **Ganged 20V Trunk** | 10.0A | **High-Power**: To 20V Wago Hub |
| **C5 / C6** | **RESERVED** | — | Future Logic / Telemetry Expansion |


---


## Engineering Standards

1. **Star-Grounding**: All node grounds must converge at the central Negative Bus Bar in the body to ensure a clean signal reference.
2. **Safety Heartbeat**: If the ESP-NOW signal is lost for >100ms, receiving nodes (1 and 2) automatically enter a "Hold" state to prevent stuck audio or drive patterns (firmware/production/node-1-dome-motion.yaml:474).
3. **Firmware Strategy**: Nodes 1 and 3 use the `esp-idf` framework within ESPHome for high-stability wireless threading.


---


[View Master Node Pinout & Wiring Guide](node-pinout-guide.md)