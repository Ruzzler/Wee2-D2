# <i data-lucide="wifi"></i> Network & OTA Guide

This guide explains how to connect your droid to your local Wi-Fi, manage the "Droid Hub" (Home Assistant), and perform wireless firmware updates (OTA).


---


## Initial Connectivity

### 1. ESPHome Secrets

Before flashing your ESP32s for the first time:
1. Open `firmware/secrets.yaml.example`.
2. Rename to `secrets.yaml`.
3. Fill in your Wi-Fi SSID and Password.
4. Optionally set a Static IP for each Node to ensure your bookmarks always work.


### 2. First Flash

- **USB Connection**: The first flash **MUST** be done via USB using the **ESPHome Dashboard** or command line.
- **Node IDs**:
  - `node-1-dome-master`
  - `node-2-sound-hub`
  - `node-3-led-distribution`


---


## Home Assistant Integration

ESPHome is natively designed for Home Assistant (HA).
1. Open Home Assistant > **Settings > Devices & Services**.
2. Your 3 droid Nodes should appear automatically under "Discovered."
3. Click **Configure** and enter the API password (if you set one).
4. **Control**: You can now add behavioral switches, battery sensors, and volume sliders to your HA dashboard.


---


## Over-The-Air (OTA) Updates

Once the ESP32s are on your Wi-Fi, you never need to plug them in again.
1. Open the ESPHome dashboard on your computer.
2. Click **Edit** on the node you want to update.
3. Make your changes (e.g., add a new WLED pattern or change a pin).
4. Click **Install > Wirelessly**.
5. Wait for the progress bar to complete. **The droid will reboot automatically.**


---


## Mobile Command Center

Each ESP32 hosts its own basic web server for quick control.
- **Droid Hub**: `http://rc-sound-controller.local`
- **Lights**: `http://dome-lights.local` (WLED Dashboard)

> [!TIP]
> **Bookmark these on your phone's home screen** for instant access to sound triggers and dome speed controls while at a convention or event.