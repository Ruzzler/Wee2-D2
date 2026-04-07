# <i data-lucide="wifi"></i> Network OTA Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: FIRMWARE UPDATE** | **PROTOCOL: ESPHOME WEB SERVER**


The Wee2-D2 project uses Over-The-Air (OTA) updates to deploy firmware without the need for physical USB connections. This guide explains how to use the built-in ESPHome web server to upload compiled binary files.


---


## System Connectivity

Updates are performed over a local 2.4GHz Wi-Fi network. Each node hosts its own web-based dashboard on port 80 (firmware/production/node-1-dome-motion.yaml:73) which includes a dedicated "Update" portal.


- **Node 1 (Dome Master)**: `wee2d2-dome-master.local`
- **Node 2 (Sound Hub)**: `wee2d2-sound-hub.local`
- **Node 3 (LED Distro)**: Accessed via the WLED dashboard (`wled-dome.local`).


---


## Deployment Procedure (Web Browser)

Follow these steps to deploy a new firmware binary (`.bin`) to your droid nodes. This synchronization is verified for the `v2.6.0` firmware stack.


1. **Compile**: Use the ESPHome dashboard or CLI to compile your configuration into a binary file.
2. **Navigate**: Open a web browser and navigate to the node's local URL or IP address.
3. **Upload**: Select the "Choose File" option under the OTA section and pick your compiled `.bin`.
4. **Monitor**: The node will receive the file, verify the integrity (firmware/production/node-1-dome-motion.yaml:62), and reboot automatically.


---


## Safety Standards & Recovery

Never power down the droid during an active OTA update. The node will automatically reboot into its "Previous Stable" state if the upload is interrupted. 


> [!WARNING]
> **BOOTLOOPS**: If a node fails to reconnect to Wi-Fi after an update, it will launch a **Fallback Hotspot** named `WEE2-D2_SETUP`. Connect to this network to re-configure the Wi-Fi or rollback the firmware.


---


## Hardware Diagnostics

You can verify the successfully deployed version in the "Diagnostic" cards on the Home Assistant dashboard or at the bottom of the node's local web page.


- **OTA Password**: Ensure you have the `ota_password` from your `secrets.yaml` file ready.
- **Signal Strength**: Updates are safest when the droid is within 10 feet of the Wi-Fi router. 
- **Encryption**: All OTA transfers are secured using the ESPHome encryption protocol (firmware/production/node-1-dome-motion.yaml:59).


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Troubleshooting](troubleshooting.md)