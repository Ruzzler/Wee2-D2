# <i data-lucide="network"></i> Node Mesh Architecture

> **TECHNICAL ARCHITECTURE** | **v2.1.2-FINAL-STABLE**

The Wee2-D2 utilizes a distributed MCU architecture called the **Node Mesh**.
This design handles high-amperage motor control, precision dome rotation, and cinematic AV triggers while minimizing physical wiring through the central slip ring.

---

## <i data-lucide="layout-dashboard"></i> System Roles

Synchronization is achieved using low-latency **ESP-NOW** wireless bridging across three specialized nodes:

### Node 1: Sound Hub (ESP32-S3)

- **Role**: Behavioral audio execution and locomotion monitoring.
- **Hardware**: DFPlayer Mini, TPA3118 Amplifier, Drive ESC integration.
- **Logic**: Receives behavioral triggers from Node 3 via ESP-NOW to initiate synchronized sound events.

### Node 2: LED Distribution (ESP32)

- **Role**: Cinematic visual output.
- **Hardware**: Addressable LED matrices (WS2812B/PSI Logic).
- **Logic**: A WLED-embedded node that translates motion-state triggers into specific lighting patterns.

### Node 3: Dome Motion Master (ESP32-S3)

- **Role**: Master behavioral logic and movement control.
- **Hardware**: goBILDA 5203 Dome Motor, PWM Motor Controller.
- **Logic**: Processes RC inputs and broadcasts state triggers (e.g., "Droid Happy", "High Alert") to the rest of the mesh.

---

## <i data-lucide="radio"></i> The Wireless Bridge (ESP-NOW)

To prevent analog audio interference and reduce the risk of slip ring data corruption, the Node Mesh utilizes **ESP-NOW**, a high-speed 2.4GHz peer-to-peer protocol.

- **Zero Router Latency**: MCUs communicate directly with <10ms response times.
- **EMI Immunity**: Moving data to the 2.4G spectrum eliminates the ground loops and motor interference inherent in slip rings.
- **Scalability**: New nodes (e.g., foot sensors or logic displays) can be added to the mesh without pulling additional wires through the central joint.

---

## <i data-lucide="shuffle"></i> Slip Ring Distribution (Body Dome)

The **CNBTR Slip Ring** (6-Circuit) acts as the physical bridge for the dome's high-current requirements. We utilize the **Dual-Circuit Isolation Strategy** defined in the [Power Architecture](power-architecture.md):

| Circuit | Role | Current (Peak) | Destination |
| :--- | :--- | :---: | :--- |
| **C1 / C2** | **High-Power (20V)** | 10.0A | **Motor Line**: Direct to goBILDA ESC |
| **C3 / C4** | **Logic Power (20V)** | 10.0A | **Logic Line**: To Mini560 Buck Hub |
| **C5 / C6** | **RESERVED** | — | Future Logic / Telemetry Expansion |

---

## Engineering Standards

1. **Star-Grounding**: All node grounds must converge at the central Negative Bus Bar in the body to ensure a clean signal reference.
1. **Safety Heartbeat**: If the ESP-NOW signal is lost for >100ms, receiving nodes (1 and 2) automatically enter a "Hold" state to prevent stuck audio or drive patterns.
1. **Firmware Strategy**: Nodes 1 and 3 utilize the `esp-idf` framework within ESPHome for high-stability wireless threading.

---

[View Master Node Pinout & Wiring Guide](node-pinout-guide.md)