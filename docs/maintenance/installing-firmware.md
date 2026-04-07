# <i data-lucide="download"></i> Installing Firmware Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: FIRMWARE DEPLOYMENT** | **TOOL: ESPHOME DASHBOARD**


This guide explains how to install the firmware for the Wee2-D2 project. It covers the initial USB flashing for new nodes and the Over-The-Air (OTA) update procedure for the `v2.6.0-Dashboard` firmware sequence.


---


## Initial Deployment (Wired USB)

New microcontroller nodes (ESP32-S3 or ESP32) require a physical USB connection for their first update. Once the initial firmware is installed, all future updates can be handled wirelessly.


1. **Connect**: Use a high-quality USB-C cable to connect your ESP32-S3 node (firmware/production/node-1-dome-motion.yaml:34) to your computer.
2. **Launch**: Open the ESPHome dashboard or the ESPHome Web site.
3. **Flash**: Pick the correct `.yaml` configuration file and select "Install". Choose the "Plug into this computer" option.
4. **Monitor**: Watch the initialization logs (firmware/production/node-1-dome-motion.yaml:66) to ensure the node successfully connects to your Wi-Fi network.


---


## OTA Updates (Wireless Bridge)

Once a node is connected to the network, you can deploy updates wirelessly. This is the primary method for managing the "Golden State" configurations in the `v2.6.0` sequence.


- **Procedure**: Navigate to the node's local web-dashboard (port 80) and upload the compiled binary.
- **Verification**: The node will check the `ota_password` (firmware/production/node-1-dome-motion.yaml:62) before initiating the write cycle.
- **Monitoring**: You can watch the flashing progress in the web-logs to ensure no radio interference occurs.


---


## Standard Node Addresses

The project uses a predictable naming convention to ensure you are deploying the correct firmware to the correct physical node.


| Node | Local Hostname | Target Firmware |
| :--- | :--- | :--- |
| **Node 1** | `wee2d2-dome-master.local` | [node-1-dome-motion.yaml](../../firmware/production/node-1-dome-motion.yaml) |
| **Node 2** | `wee2d2-sound-hub.local` | [node-2-sound-hub.yaml](../../firmware/production/node-2-sound-hub.yaml) |
| **Node 3** | `wled-dome.local` | [node-3-segments.json](../../firmware/production/node-3-segments.json) |


---


## Hardware Diagnostics & Troubleshooting

Successful deployment is confirmed by the appearance of the "Diagnostic" cards in Home Assistant (firmware/production/node-1-dome-motion.yaml:436).


- **USB Driver**: Ensure you have the CP2102 or CH340 drivers installed if the node is not detected by your computer.
- **Encryption**: If the OTA update fails, check that the `api_encryption_key` in your `secrets.yaml` matches the node configuration.
- **Safe Mode**: If a node enters a bootloop, it will automatically launch a fallback hotspot for recovery.


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Calibration](calibration-guide.md)