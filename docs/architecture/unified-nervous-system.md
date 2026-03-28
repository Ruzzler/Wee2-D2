# 🧠 The Unified Droid Nervous System (UDNS)

The **Unified Droid Nervous System (UDNS)** is the high-bandwidth industrial backbone of the Wee2-D2. It transforms three independent ESP32 microcontrollers into a single, cohesive "Droid Brain" through a master-slave serial command architecture.

---

## 🏛️ Architecture Overview
In a standard hobbyist build, parts often work in isolation. In the **UDNS** model, every action is synchronized across the droid's entire frame:

*   **The Master (Body Brain)**: Interprets RC signals and manages the soundboard. It acts as the "Central Cortex."
*   **The Slaves (Dome Nodes)**: High-performance S3 Mini nodes that listen on a shared **Command Bus**. They react instantly to instructions sent from the body (e.g., "Rotate dome 90°," "Switch lights to Angry Mode").

![Wiring Diagram](../../assets/chassis-electronics-layout.png)

---

## 🛰️ How it Works: The Serial Bus
The UDNS uses **Asynchronous Serial (UART)** communication to bridge the gap between the body and the dome. 

1.  **Command Flow**: When the Body Master detects an event (like a specific button push on your remote), it broadcasts a simplified command string across the **Slip Ring**.
2.  **Multidrop Listening**: Multiple dome nodes can listen to the same command line simultaneously. This ensures that dome LEDs and dome motors move in perfect unison without latency.
3.  **Bidirectional Telemetry**: The dome can report its status (battery health, current position) back to the body, which then relays that data to your **Home Assistant** dashboard.

---

## 🚀 Why UDNS? (Future-Proofing)

### **1. Home Assistant Integration**
By running **ESPHome** as the native firmware for UDNS, your droid isn't just a toy—it's a smart device. You can track battery levels, trigger automated "Guard Mode" routines, and control every LED segment from your phone or tablet.

### **2. Over-The-Air (OTA) Updates**
Wireless maintenance is a core pillar of UDNS. You will never need to open the droid's chassis to update the code. Simply push the update from your PC via Wi-Fi, and the nodes will reboot with their new "logic" instantly.

### **3. Zero-Latency Triggers**
Unlike Wi-Fi-only communication (which can be unreliable at busy events/conventions), the UDNS uses a **physical wire** through the slip ring. This ensures your "Angry Mode" trigger works 100% of the time, even in areas with heavy radio interference.

---

## 🛠️ Components of the System
*   **Body Controller**: ESP32D Dev Board (High pin-count for sound triggers).
*   **Dome Controllers**: 2x ESP32-S3 Super Mini (Ultra-compact for internal dome mounting).
*   **Interconnect**: 6-Circuit High-Current Slip Ring (The "Spinal Cord").
