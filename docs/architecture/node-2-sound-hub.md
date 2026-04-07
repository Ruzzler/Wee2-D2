# <i data-lucide="cpu"></i> Node 2: Sound Hub

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: SOUND HUB MASTER** | **MODEL: ESP32-S3 SUPER MINI**


Node 2 is the primary audio controller and web gateway for the Wee2-D2 project. It manages the DFPlayer Mini sound module and hosts the droid's interactive dashboard for remote behavioral control.


---


## Hardware Specifications (Logic Focus)

The **ESP32-S3 Super Mini** is used for its dual-core performance, allowing it to handle real-time ESP-NOW radio mesh triggers while simultaneously running the glassmorphic dashboard web-server.


- **Processor**: Dual-Core ESP32-S3
- **Voltage**: 5V Logic Rail (Mini560 Pro)
- **GPIO Pins**: [Node Pinout Guide](../architecture/node-pinout-guide.md)
- **Framework**: ESPHome (esp-idf)


---


## GPIO Pinout & Logic Assignments

The Sound Hub manages a high-speed UART serial bus to trigger the MP3-TF-16P decoder and listens for mesh commands from the Dome Master.


These settings are verified in the `v2.6.0-Dashboard` firmware sequence.


| Assignment | GPIO Pin | Function | Citation |
| :--- | :--- | :--- | :--- |
| **DFPlayer TX** | **GPIO 43** | Serial Out to Audio Hub | [node-2.yaml:43](../../firmware/production/node-2-sound-hub.yaml#L43) |
| **DFPlayer RX** | **GPIO 44** | Serial In from Audio Hub | [node-2.yaml:44](../../firmware/production/node-2-sound-hub.yaml#L44) |
| **Status LED** | **GPIO 15** | Onboard Diagnostics | [node-2.yaml:70](../../firmware/production/node-2-sound-hub.yaml#L70) |
| **Dashboard** | **Internal** | Web API Port 80 | [node-2.yaml:73](../../firmware/production/node-2-sound-hub.yaml#L73) |


---


## Web Gateway & Dashboard Logic

Node 2 acts as the **Dashboard Master**. It generates the web-based UI that allows the pilot to trigger manual animations, adjust dome speed, and manage audio presets.


1. **Trigger Handling**: When a button is pushed on the dashboard, Node 2 pushes a radio broadcast back to Node 1 over the 2.4GHz mesh.
2. **Audio Sync**: If Node 2 receives a `0x01` broadcast trigger from Node 1, it instantly sends the corresponding serial command to the DFPlayer Mini.
3. **Safety Timeout**: If the mesh bridge is lost, Node 2 entries a "Stationary" state to prevent audio/lighting desync.


---


## Maintenance & Debugging

You can access the sound hub's diagnostic logs wirelessly (`wee2d2-sound-hub.local`) or via the physical USB-C port at 115200 baud.


- **OTA Password**: Required for wireless updates (firmware/production/node-2-sound-hub.yaml:62).
- **Audio Lag**: If you experience delays in sound playback, check the signal strength between the body logic stack and the Wi-Fi router. 
- **Baud Rate**: Ensure the DFPlayer is communicating at **9600 bps** as verified in the [Audio System Guide](../capabilities/audio-system.md).


---


[View Master Schematic](electrical-schematic.md) | [View Power Architecture](power-architecture.md)