# 🧠 The Unified Droid Nervous System (UDNS)

The **Unified Droid Nervous System (UDNS)** is the high-bandwidth industrial backbone of the Wee2-D2. It transforms three independent ESP32 microcontrollers into a single, cohesive "Droid Brain" through a master-slave serial command architecture.

---

## 🏛️ Architecture Overview
In a standard hobbyist build, parts often work in isolation. In the **UDNS** model, every action is synchronized across the droid's entire frame:

*   **The Master (Body Controller)**: Interprets RC signals and manages the soundboard. It acts as the "Central Cortex."
*   **The Slaves (Dome MCUs)**: High-performance S3 Mini nodes that listen on a shared **Command Bus**. They react instantly to instructions sent from the body (e.g., "Rotate dome 90°," "Switch lights to Angry Mode").

---

## 🛰️ How it Works: The Serial Bus
The UDNS uses **Asynchronous Serial (UART)** communication to bridge the gap between the body and the dome. 

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
Unlike Wi-Fi-only communication (which can be unreliable at busy events/conventions), the UDNS uses a **physical wire** through the slip ring. This ensures your "Angry Mode" trigger works 100% of the time, even in areas with heavy radio interference.

---

## 🛠️ Components of the System
*   **Body Controller**: ESP32-WROOM-32D (High pin-count for sound triggers).
*   **Dome Controllers**: 2x ESP32-S3 Super Mini (Ultra-compact for internal dome mounting).

---

## 🛞 Slip Ring Integration (6-Circuit)
The slip ring is the physical "Spinal Cord" of the droid. Every signal must be shared across this rotating joint perfectly to ensure the UDNS bus does not drop packets. Because the dome contains a heavy motor and sensitive 5V logic chips, power is separated into two clean lines.

| Circuit | Function | Color (Typical) | Wire Gauge | Destination |
| :--- | :--- | :--- | :--- | :--- |
| **C1** | **VCC (20V DC)** | Red | 18 AWG | **Motor Line**: To goBILDA 15A ESC |
| **C2** | **GND (Common)** | Black | 18 AWG | **Motor Line**: To goBILDA 15A ESC |
| **C3** | **VCC (20V DC)** | Yellow/White | 18 AWG | **Logic Line**: To Mini560 Pro Buck |
| **C4** | **GND (Common)** | Green/Blue | 18 AWG | **Logic Line**: To Mini560 Pro Buck |
| **C5** | **UDNS TX (Out)** | Brown | 18 AWG | Body Master -> Dome Slaves (Command) |
| **C6** | **UDNS RX (In)** | Gray | 18 AWG | Dome Slaves -> Body Master (Telemetry) |

> [!WARNING]
> **COMMON GROUND IS MANDATORY**: You must ensure the Ground from the main Negative Bus Bar travels up the slip ring to provide a flawless reference potential for both the motor and the logic wires. If the ground is broken or noisy, your 3.3V UART serial signals will become "garbage" data floating in reference to nothing, and the droid will wildly glitch. 

---

## 📊 GPIO Interconnects
If you need the specific GPIO pins used by the UDNS serial bus to wire the controllers into the slip ring, refer to the **Pinout Lookup Tables** at the bottom of the [Interactive Electrical Schematic](electrical-schematic.md).
