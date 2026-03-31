# Wee2-D2 System Architecture
> **MAINTENANCE & OPERATIONS** | **v2.1.0-Zero-Infra Technical Overview**

The Wee2-D2 project utilizes a distributed MCU architecture to handle high-amperage motor control, precision dome rotation, and cinematic AV triggering while minimizing physical wiring through the central slip ring.

## 🧠 Distributed Control Hub
The system is divided into three primary nodes, communicating via low-latency **ESP-NOW** wireless bridging.

### Node 1: Sound Hub (ESP32-S3)
- **Role**: Behavioral execution and audio management.
- **Hardware**: DFPlayer Mini, TPA3118 Amplifier, Drive ESC integration.
- **Primary Logic**: Listens for ESP-NOW triggers from the Dome Motion master to initiate synchronized audio/visual events.

### Node 2: LED Distribution (ESP32)
- **Role**: Visual output management.
- **Hardware**: Addressable LED arrays (WS2812B/PSI Logic).
- **Primary Logic**: Operates as a WLED-enabled node, translating motion-state triggers into specific lighting patterns.

### Node 3: Dome Motion (ESP32-S3)
- **Role**: Droid sensory input and movement control.
- **Hardware**: goBILDA 5203 Dome Motor, PWM Motor Controller.
- **Primary Logic**: Processes RC/Manual inputs and broadcasts state triggers (e.g., "Droid Thinking", "High Alert") to Nodes 1 and 2.

---

## 📡 Wireless Communication (The Bridge)
To eliminate EMI interference from the high-amperage drive motors, the droid uses **ESP-NOW** for all inter-node communication. This replaces the physical serial bus (UDNS) and significantly simplifies the slip ring wiring requirements.

- **Protocol**: ESP-NOW @ 2.4GHz
- **Update Frequency**: 50ms (for real-time response)
- **Security**: Device MAC-address binding (defined in `base-config.yaml`)
