# <i data-lucide="volume-2"></i> Node 2: Sound Hub Spec

> **TECHNICAL SPECIFICATIONS** | **ESPHome v3** | **ESP32-S3 Super Mini** | **Audio & Drive Sync**

| Component | Detail |
| :--- | :--- |
| **Node ID** | **2** |
| **Role** | Audio Execution & ESC Telemetry Monitoring |
| **Source Code** | [`node-2-sound-hub.yaml`](../../firmware/production/node-2-sound-hub.yaml) |
| **Visual ID (Logic)** | ![S3 Mini](../../assets/esp32-s3-super-mini.jpg) |
| **Visual ID (Audio)** | ![TPA3118](../../assets/tpa3118-amplifier-module.jpg) |

## Core Purpose

- **ESP-NOW Wireless Link**: Low-latency behavioral synchronization with the Dome Master.
- **DFPlayer UART Control**: High-fidelity track triggering and volume management via serial.
- **RC Signal Monitoring**: Decodes PWM from RC1 for localized drive fail-safes.
- **Telemetry Projection**: Reports audio status and battery health back to Home Assistant.
- **OTA Updates**: Fully support Over-The-Air updates via the [Documentation Dashboard](docs/maintenance/network-ota-guide.md).

## Pinout Configuration

| Connection | ESP32 Pin | Logic |
| :--- | :---: | :--- |
| **RC CH3-5 (In)** | 4, 5, 6 | Trigger Pulse Data (Input) |
| **DFPlayer TX** | GPIO 17 | Serial Command Out |
| **DFPlayer RX** | GPIO 16 | Serial Status In (Optional) |
| **Wireless Link** | N/A | ESP-NOW Behavioral Sync |
| **Status LED** | GPIO 47 | Internal Neopixel (Logic) |

### Auto-Mode Logic

When the `current_bank` is set to `3` (Bank 4), an internal 1-second interval timer decrements. When it reaches zero, a random trigger is fired and the timer is reset to a value between 5s and 15s.