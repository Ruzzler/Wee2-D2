# <i data-lucide="volume-2"></i> Node 2: Sound Hub

> **TECHNICAL SPECIFICATIONS** | **ESPHome v3** | **ESP32-S3 Super Mini** | **Audio & Drive Sync**

| Component | Detail |
| :--- | :--- |
| **Node ID** | **2** |
| **Role** | Audio Execution & ESC Telemetry Monitoring |
| **Source Code** | [`node-2-sound-hub.yaml`](../../firmware/production/node-2-sound-hub.yaml) |
| **Visual ID (Logic)** | ![S3 Mini](../../assets/esp32-s3-super-mini.jpg) |
| **Visual ID (Audio)** | ![TPA3118](../../assets/tpa3118-amplifier-module.jpg) |

## Core Purpose

![Neural Command Dashboard](../../assets/neural-command-dashboard.jpg)

- **Neural Command Center**: Hosts the responsive web dashboard (`system_dashboard.h`) serving as the interactive entry point to the droid.
- **ESP-NOW Wireless Relay**: Securely relays dashboard commands (`0xA0-0xA2`) to Node 1 via a bidirectional 2.4GHz bridge.
- **DFPlayer UART Control**: High-fidelity track triggering and system volume management.
- **OTA Updates**: Fully support Over-The-Air updates directly from the Web UI.

## Pinout Configuration

| Connection | ESP32 Pin | Logic |
| :--- | :---: | :--- |
| **Dashboard** | Wi-Fi | TCP/IP Interface `port 80` |
| **DFPlayer TX** | GPIO 12 | Serial Command Out |
| **DFPlayer RX** | GPIO 13 | Serial Status In (Optional) |
| **Wireless Relay** | Ch. 11 | ESP-NOW Behavioral Sync |
| **Status LED** | GPIO 47 | Internal Neopixel (Logic) |

### Watchdog Link

Node 2 actively listens for a 5-second `0xB0` heartbeat sent from Node 1. If this connection drops, the Web Dashboard UI elements physically lock out and report "MESH DEGRADED" to prevent blind data transmission.