# 🕸️ Unified Nervous System: distributed Node Mesh
> **ARCHITECTURE OVERVIEW** | **MODEL: v2.1.0-Zero-Infra**

The Wee2-D2 project uses a **distributed MCU model** called the **Node Mesh**. This architecture eliminates the need for complex, heavy wiring through the slip ring by distributing intelligence into three specialized hubs.

---

## 🏛️ Architecture Overview
In a standard hobbyist build, parts often work in isolation. In the **Node Mesh** model, every action is synchronized across the droid's entire frame:

*   **The Master (Node 3: Dome Motion)**: Handles all behavioral triggers and dome rotation. It acts as the "Behavioral Master."
*   **The Slaves (Node 1: Sound Hub & Node 2: LED Distribution)**: High-performance **ESP32-S3 and ESP32-D nodes** that listen for broadcast packets. They react instantly to wireless instructions (e.g., "Play Sound: Happy," "Switch lights to High Alert").

---

## 🛰️ How it Works: The Wireless Bridge (ESP-NOW)
The Node Mesh uses **ESP-NOW**, a low-power, high-speed 2.4GHz wireless protocol, to bridge the gap between the body and the dome without physical data wires.

1.  **Direct P2P Link**: Unlike standard Wi-Fi, ESP-NOW does not require a router. MCUs communicate directly with one another, ensuring sub-10ms latency for triggers.
2.  **Broadcast Behavior**: When the Dome Motion master (Node 3) detects an event (like a specific rotation threshold or RC command), it broadcasts a behavioral packet to the Sound Hub (Node 1) and LED Distribution hub (Node 2) simultaneously.
3.  **Radio Isolation**: By moving data to the 2.4GHz spectrum, we eliminate analog ground loops and EMI interference that typically plague UART signals running through a rotating slip ring.

### **Protocol Specifications**
- **Type**: Connectionless (Unicast/Broadcast)
- **Range**: ~50m (Internal Chassis Range optimized for stability)
- **Latency**: <10ms (Real-time motor/audio sync)
- **Framework**: `esp-idf` (Required on ESP32-S3 for stable RMT/Wireless threading)

---

## 🚀 Why Wireless? (Architectural Evolution)

### **1. Audio Signal Integrity**
By communicating wirelessly, we can keep the **DFPlayer Mini** and its analog audio paths entirely within the body. This prevents analog audio from ever crossing the noisy slip ring environment, ensuring a hiss-free sound floor.

### **2. Reduced Slip Ring Friction**
By removing the two serial data lines (TX/RX) from the slip ring, we reduce the complexity of the rotating joint and free up two high-current circuits for future logic sensors or backup power.

### **3. Zero-Latency Reactivity**
ESP-NOW provides the same "physical wire" feel as UART but handles packet collisions and retries at the hardware layer, making behavioral triggers more robust in high-interference environments.

---

## 🛠️ Components of the System
*   **Node 1: Sound Hub (Audio)**: ESP32-S3 Super Mini (Behavioral Slave).
*   **Node 3: Dome Motion (Motion)**: ESP32-S3 Super Mini (Behavioral Master).
*   **Node 2: LED Distribution (Lights)**: ESP32-Dev Board (Slave WLED).

---

## 🛞 Slip Ring Integration (6-Circuit)
The slip ring is the physical "Spinal Cord" of the droid. Every signal must be shared across this rotating joint perfectly to ensure the Node Mesh bus does not drop packets. Because the dome contains a heavy motor and sensitive 5V logic chips, power is separated into two clean lines.

| Circuit | Function | Color (Typical) | Wire Gauge | Destination |
| :--- | :--- | :--- | :--- | :--- |
| **C1** | **VCC (20V DC)** | Red | 18 AWG | **Motor Line**: To goBILDA 15A ESC |
| **C2** | **GND (Common)** | Black | 18 AWG | **Motor Line**: To goBILDA 15A ESC |
| **C3** | **VCC (20V DC)** | Yellow/White | 18 AWG | **Logic Line**: To Mini560 Pro Buck |
| **C4** | **GND (Common)** | Green/Blue | 18 AWG | **Logic Line**: To Mini560 Pro Buck |
| **C5** | **RESERVED** | Yellow/Black | 18 AWG | Future High-Speed Logic / Sensor Bus |
| **C6** | **RESERVED** | Green/Black | 18 AWG | Future High-Speed Logic / Sensor Bus |

---

## 🛠️ Signal Integrity Standards
To ensure the Node Mesh remains stable across multiple nodes and through the slip ring, the following engineering standards are applied to all firmware configurations:

1.  **Sensor Update Intervals**: General ESPHome sensors default to 60-second intervals. For real-time RC control, an `update_interval: 50ms` is used on the `pulse_width` component to ensure reactive motion.
2.  **Input Pull-Downs**: High-speed digital signals (like RC PWM) require `mode: INPUT_PULLDOWN` on the GPIO pin to prevent floating signals and electrical jitter when the source is disconnected or idle.
3.  **Log Noise Suppression**: Analog signals often have micro-fluctuations. A `delta: 20.0` filter is applied to sensors to ignore these fluctuations, and the `logger` level is set to `INFO` to suppress unnecessary background telemetry.

---

## 💾 ESP-NOW Behavioral Events
For reliability, the Wireless Bridge utilizes the broadcast protocol with the following logic:

### **2. ESP-NOW Mesh (Wireless)**
The core behavioral link is the **ESP-NOW Wireless Bridge**. Node 3 broadcasts status packets (e.g., "Droid Happy") which are instantly acted upon by Nodes 1 and 2.

1.  **Channel Locking**: All nodes MUST remain on the same Wi-Fi channel (typically Channel 1) to ensure packet delivery.
2.  **Encryption**: Communication can be hardened using the `api: encryption` key if deployed in public environments.
3.  **Safety Heartbeat**: If the bridge signal is lost for >100ms, the receiving nodes (Sound Hub and LED Distribution) automatically enter a "Hold" or "Rest" state to prevent runaway motors or stuck light patterns.

**Example Behavior (Play Sound)**:
- **Node 3 (Dome Motion)** broadcasts: `SOUND_ID_01`
- **Node 1 (Sound Hub)** receives: `PLAY TRACK 01` on DFPlayer Mini.

## 📊 GPIO Interconnects
If you need the specific GPIO pins used by the DFPlayer or ESCs, refer to the **Pinout Lookup Tables** in the [Interactive Electrical Schematic](electrical-schematic.md).
