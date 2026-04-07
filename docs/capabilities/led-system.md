# <i data-lucide="lightbulb"></i> Cinematic LED System

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: CINEMATIC LIGHTING** | **MODEL: GRNWAVE PSI / WLED**


This guide explains the lighting architecture for the Wee2-D2 project. It covers the addressable LED arrays, WLED synchronization, and the behavioral lighting presets managed by Node 1.


---


## Hardware Components (LED Hub)

The lighting system is decentralized across the dome using addressable WS2812B LEDs. These lights are powered by a dedicated high-current 5.01V buck converter to prevent voltage drops during bright patterns.


- **Controller**: Node 3: LED Distro (ESP32)
- **Framework**: WLED (v0.14+ / RMT Protocol)
- **Primary Arrays**: GrnWave PSI logics (Addressable)
- **Data Protocol**: UART-to-WLED Bridge (115200 Baud)


---


## Behavioral Lighting Presets (UART Sync)

Lighting presets are triggered by **Node 1 (Dome Master)** on the dedicated serial bus (firmware/production/node-1-dome-motion.yaml:137). These presets are synchronized with the droid's audio and movement behaviors.


These presets are verified in the `v2.6.0-Dashboard` firmware sequence.


| Preset ID | Animation Name | Visual Profile | Citation |
| :--- | :--- | :--- | :--- |
| **P0** | **All Off** | All LEDs are powered down | [node-1.yaml:385](../../firmware/production/node-1-dome-motion.yaml#L385) |
| **P1** | **1977 Idle** | Standard movie-accurate logic | [node-1.yaml:382](../../firmware/production/node-1-dome-motion.yaml#L382) |
| **P3** | **Full Alert** | Rapid Red/Blue logic flash | [node-1.yaml:384](../../firmware/production/node-1-dome-motion.yaml#L384) |
| **P10** | **Disco Mode** | Rainbow-cycling party vibe | [node-1.yaml:391](../../firmware/production/node-1-dome-motion.yaml#L391) |
| **P14** | **Celebration** | Gold/White high-speed flash | [node-1.yaml:395](../../firmware/production/node-1-dome-motion.yaml#L395) |


---


## Logic Flow & Connectivity

The Lighting Hub (Node 3) receives serial JSON strings from Node 1. This method ensures that the lighting stays perfectly in sync with the audio track being played by Node 2.


1. **Trigger Origin**: Node 1 detects an animation event (e.g., "The Cantina Band").
2. **Serial Broadcast**: Node 1 pushes a JSON string (e.g., `{"on":true,"ps":10}`) down the physical UART wire (GPIO 5).
3. **Execution**: Node 3 (WLED) receives the command at 115200 baud and instantly applies the preset.


---


## Troubleshooting & Management

Ensure the Node 1 and Node 3 **grounds** are tied together at the central Wago hub. Without a shared ground reference, the serial serial communication (UART) will become unreliable.


- **Flickering**: If you see random flickering, check the Node 3 buck converter output. Under-voltage can cause the addressable LEDs to reset. 
- **Lag**: The 115200 baud bus is very fast. If lighting lag occurs, it is likely due to the WLED board entering a "Deep Sleep" or the `FS` library failing on Node 1.
- **Heartbeat**: Node 1 sends a diagnostic "keep-alive" ping every 60 seconds (firmware/production/node-1-dome-motion.yaml:462) to keep the line active.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View Power Architecture](../architecture/power-architecture.md)
