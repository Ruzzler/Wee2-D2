![manual-hero](../../assets/esp32-s3-super-mini.jpg)


# <i data-lucide="cpu"></i> Node 1: Dome Master

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: DOME MOTION MASTER** | **MODEL: ESP32-S3 SUPER MINI**


Node 1 is the primary controller for the Wee2-D2 project. It manages dome rotation, receives radio stick inputs from the HotRC receiver, and acts as the master for the ESP-NOW communication mesh.


---


## Hardware Specifications (Logic Focus)

The **ESP32-S3 Super Mini** is selected for its compact footprint and high-speed radio performance required for real-time RC control.


- **Processor**: Dual-Core ESP32-S3
- **Voltage**: 5V Logic Rail (Mini560 Pro)
- **GPIO Pins**: [Node Pinout Guide](../architecture/node-pinout-guide.md)
- **Framework**: ESPHome (esp-idf)


---


## GPIO Pinout & Logic Assignments

The Dome Master manages high-precision PWM signals for dome rotation and serial triggers for the lighting and sound subsystems.


These settings are verified in the `v2.6.0-Dashboard` firmware sequence.


| Assignment | GPIO Pin | Function | Citation |
| :--- | :--- | :--- | :--- |
| **Dome PWM** | **GPIO 7** | Motor Speed/Dir | [node-1.yaml:11](../../firmware/production/node-1-dome-motion.yaml#L11) |
| **RC Input** | **GPIO 4** | HotRC Stick Data (X) | [node-1.yaml:12](../../firmware/production/node-1-dome-motion.yaml#L12) |
| **WLED Data** | **GPIO 5** | Serial Out to Node 3 | [node-1.yaml:13](../../firmware/production/node-1-dome-motion.yaml#L13) |
| **Dashboard** | **Internal** | Web API Port 80 | [node-1.yaml:73](../../firmware/production/node-1-dome-motion.yaml#L73) |


---


## Mesh Communication (ESP-NOW)

The Wee2-D2 droid uses a **Modular Animation System** based on **ESPHome States** and **Wireless Triggers**. All autonomy is processed by **Node 1 (Dome Master)**, which monitors its idle state and triggers synchronized movement/AV events to maintain character realism.


1. **Sound Broadcast**: Sends triggers (e.g., `0x01` for Beep) wirelessly (firmware/production/node-1-dome-motion.yaml:81).
2. **Dashboard Mesh**: Receives instruction packets from Node 2's web-dashboard and converts them into rotation or lighting events.
3. **Safety Timeout**: If the mesh bridge is lost for >100ms, all movement is immediately paused to prevent runaway operation.


---


## Maintenance & Debugging

You can access the real-time diagnostic logs for Node 1 over Wi-Fi (`wee2d2-dome-master.local`) or via the physical USB-C port at 115200 baud.


- **OTA Password**: Required for wireless updates (firmware/production/node-1-dome-motion.yaml:62).
- **Logger Level**: Set to `DEBUG` for all production configurations (firmware/production/node-1-dome-motion.yaml:66).
- **Heartbeat**: Node 1 sends a diagnostic "keep-alive" ping every 5 seconds to maintain the mesh connection.


---


[View Master Schematic](electrical-schematic.md) | [View Power Architecture](power-architecture.md)