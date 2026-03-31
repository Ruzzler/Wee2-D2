# 🧠 The Unified Droid Nervous System (UDNS)

The **Unified Droid Nervous System (UDNS)** is the high-bandwidth industrial backbone of the Wee2-D2. It transforms three independent ESP32 microcontrollers into a single, cohesive "Droid Brain" through a master-slave serial command architecture.

---

## 🏛️ Architecture Overview
In a standard hobbyist build, parts often work in isolation. In the **UDNS** model, every action is synchronized across the droid's entire frame:

*   **The Master (Body Controller)**: Interprets RC signals and manages the soundboard. It acts as the "Central Cortex."
*   **The Slaves (Dome MCUs)**: High-performance **ESP32-D nodes** that listen on a shared **Command Bus**. They react instantly to instructions sent from the body (e.g., "Rotate dome 90°," "Switch lights to High Alert").

---

## 🛰️ How it Works: The Serial Bus
The UDNS uses **Asynchronous Serial (UART)** communication @ **115200 Baud** to bridge the gap between the body and the dome. 

1.  **Command Flow**: When the Body Master detects an event (like a specific button push on your remote), it broadcasts a simplified command string across the **Slip Ring**.
2.  **Multidrop Listening**: Multiple dome MCUs can listen to the same command line simultaneously. This ensures that dome LEDs and dome motors move in perfect unison without latency.
3.  **Bidirectional Telemetry**: The dome can report its status (battery health, current position) back to the body, which then relays that data to your **Home Assistant** dashboard.

---

## 🚀 Why UDNS? (Future-Proofing)

### **1. Home Assistant Integration**
By running **ESPHome** as the native firmware for UDNS, your droid isn't just a toy—it's a smart device. You can track battery levels, trigger automated "Guard Mode" routines, and control every LED segment from your phone or tablet.

### **2. Over-The-Air (OTA) Updates**
Wireless maintenance is a core pillar of UDNS. You will never need to open the droid's chassis to update the code. Simply push the update from your PC via Wi-Fi, and the MCUs will reboot with their new "logic" instantly.

### **3. Zero-Latency Triggers**
Unlike Wi-Fi-only communication (which can be unreliable at busy events/conventions), the UDNS uses a **physical wire** through the slip ring. This ensures your behavioral triggers work 100% of the time, even in areas with heavy radio interference.

---

## 🛠️ Components of the System
*   **Body Controller**: ESP32-WROOM-32D (Master).
*   **Dome Controller (Motion)**: ESP32-Dev Board (Slave/Relay).
*   **Dome Controller (Lights)**: ESP32-Dev Board (Standalone WLED).

---

## 🛞 Slip Ring Integration (6-Circuit)
The slip ring is the physical "Spinal Cord" of the droid. Every signal must be shared across this rotating joint perfectly to ensure the UDNS bus does not drop packets. Because the dome contains a heavy motor and sensitive 5V logic chips, power is separated into two clean lines.

| Circuit | Function | Color (Typical) | Wire Gauge | Destination |
| :--- | :--- | :--- | :--- | :--- |
| **C1** | **VCC (20V DC)** | Red | 18 AWG | **Motor Line**: To goBILDA 15A ESC |
| **C2** | **GND (Common)** | Black | 18 AWG | **Motor Line**: To goBILDA 15A ESC |
| **C3** | **VCC (20V DC)** | Yellow/White | 18 AWG | **Logic Line**: To Mini560 Pro Buck |
| **C4** | **GND (Common)** | Green/Blue | 18 AWG | **Logic Line**: To Mini560 Pro Buck |
| **C5** | **UDNS TX (Out)** | Yellow/Black | 18 AWG | Body Master -> Dome Slaves (Command) |
| **C6** | **UDNS RX (In)** | Green/Black | 18 AWG | Dome Slaves -> Body Master (Telemetry) |

---

## 🛠️ Signal Integrity Standards
To ensure the UDNS remains stable across multiple nodes and through the slip ring, the following engineering standards are applied to all firmware configurations:

1.  **Sensor Update Intervals**: General ESPHome sensors default to 60-second intervals. For real-time RC control, an `update_interval: 50ms` is used on the `pulse_width` component to ensure reactive motion.
2.  **Input Pull-Downs**: High-speed digital signals (like RC PWM) require `mode: INPUT_PULLDOWN` on the GPIO pin to prevent floating signals and electrical jitter when the source is disconnected or idle.
3.  **Log Noise Suppression**: Analog signals often have micro-fluctuations. A `delta: 20.0` filter is applied to sensors to ignore these fluctuations, and the `logger` level is set to `INFO` to suppress unnecessary background telemetry.

---

## 💾 Serial JSON Protocol
For reliability, the UDNS utilizes the industry-standard JSON format with the following requirements:

1.  **Delimiter**: Every command string must end with the `\n` newline character.
2.  **Segment Arrays**: All effects must be wrapped in the `[]` segment array for multi-node compatibility.

**Example Command (High Alert Mode)**:
```json
{"on":true,"seg":[{"fx":0,"col":[[255,0,0]]}]}\n
```

## 📊 GPIO Interconnects
If you need the specific GPIO pins used by the UDNS serial bus, refer to the **Pinout Lookup Tables** in the [Interactive Electrical Schematic](electrical-schematic.md).
