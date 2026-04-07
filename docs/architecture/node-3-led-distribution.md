# <i data-lucide="lightbulb"></i> Node 3: LED Distribution

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: LIGHTING HUB** | **MODEL: ESP32 DEVKIT V1 / WLED**


Node 3 is the dedicated lighting controller for the Wee2-D2 project. It runs the WLED framework and manages all addressable visuals, including the GrnWave PSI logics and status displays.


---


## Hardware Specifications (Logic Focus)

The **ESP32 DevKit V1** is used for its robust RMT timing performance, ensuring that the WS2812B signals remain clear and flicker-free even during high-brightness animations.


- **Processor**: Single-Core ESP32D (WROOM)
- **Voltage**: 5V Logic Rail (Mini560 Pro)
- **GPIO Pins**: [Node Pinout Guide](../architecture/node-pinout-guide.md)
- **Framework**: WLED (v0.14+ / RMT Protocol)


---


## GPIO Pinout & Logic Assignments

The LED Distro manages the high-speed data signals for the droid's cinematic arrays. It follows the RMT protocol on a dedicated serial bus.


These settings are verified in the `v2.6.0-Dashboard` hardware sequence.


| Assignment | GPIO Pin | Function | Citation |
| :--- | :--- | :--- | :--- |
| **Logic Matrix** | **GPIO 13** | Main LED Logic Array | [LED Guide](../capabilities/led-system.md) |
| **PSI Lights** | **GPIO 12** | PSI Status Indicators | [PSI Manual](../hardware/grnwave-psi-manual.md) |
| **Sync Input** | **GPIO 3** | Serial In from Node 1 | [UART Sync Guide](../capabilities/led-system.md) |


---


## WLED Configuration & Sync Triggers

Node 3 acts as the **Lighting Slave**. It receives JSON strings from Node 1 to instantly apply visual presets that match the current audio and motion behavior.


1. **Segment Mapping**: Managed in the local `wled-cfg.json` file. Map Front PSI to Segment 0 and Rear PSI to Segment 1.
2. **Serial Receiver**: Listens at 115200 baud for instructions (e.g., `{"on":true,"ps":1}`).
3. **Preset Sync**: Ensures that a "Cantina Band" sound event instantly triggers a corresponding lighting preset.


---


## Maintenance & Debugging

You can access the lighting node's diagnostic dashboard wirelessly (`wled-dome.local`) or via the physical micro-USB port.


- **Dashboard Access**: Required for adjusting segment brightness and RGB order (GRB).
- **Signal Integrity**: If the lighting is flickering, verify that the 5V logic rail is stable. Voltage drops below 4.5V will cause the addressable LEDs to reset. 
- **Baud Rate**: Ensure the Node 1 serial bus is set to **115200** to prevent lighting lag.


---


[View Status Schematic](electrical-schematic.md) | [View LED System Guide](../capabilities/led-system.md)