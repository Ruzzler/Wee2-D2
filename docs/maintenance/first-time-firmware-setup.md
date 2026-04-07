# <i data-lucide="download"></i> First-Time Firmware Setup (Initial USB Flash)

> **OPERATION & MAINTENANCE**

Before your ESP32 microcontrollers can be updated wirelessly over your local network, they must be "injected" with their initial code and Wi-Fi credentials via a physical USB connection.

---

## Prerequisites

1. **A Computer**: PC, Mac, or Linux machine.
1. **Google Chrome or Microsoft Edge**: The physical USB flash uses the [Web Serial API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API), which is only supported in Chromium-based browsers. Safari/Firefox will not work.
1. **Data-Capable USB Cable**: A high-quality USB-Micro (for ESP32D) or USB-C (for S3 Mini) cable. *Warning: Many cheap cables only provide power and cannot transmit data.*

## Step 1: Prepare the Secrets File

Your ESP32s need to know your Wi-Fi password so they can connect to your local network and the ESPHome dashboard.

1. In the `Wee2-D2` repository, navigate to the `firmware/` folder.
1. Locate the file named `secrets.yaml.example`.
1. Rename it to `secrets.yaml`.
1. Open the file and enter your actual Wi-Fi SSID and Password.

## Step 2: The Physical Flash

1. Plug your ESP32 into your computer via USB.
1. Open your [ESPHome Dashboard](https://esphome.io/).
1. Click **"New Device"**.
1. Click **"Continue"**, give it the name corresponding to the Node (e.g., `node-2-sound-hub`).
1. Click **"Connect"** and select the **USB/COM Port** that appears in your browser popup.
1. Click **"Install"**.

*Note: The first compilation process can take up to 5 minutes as it generates the C++ bin file. Do not unplug the cable!*

## Step 3: Retrieve your MAC Addresses (ESP-NOW)

Before you can upload the final Wee2-D2 firmware, you must record the physical MAC addresses of Node 1 and Node 2 so they can form the secure ESP-NOW wireless bridge.

1. While the device is plugged in via USB and running the blank firmware, click **"Logs"** in the ESPHome Dashboard.
2. In the resulting output, look for the line stating `MAC Address: XX:XX:XX:XX:XX:XX`.
3. Copy this address into your `secrets.yaml` file (as `node_1_mac` or `node_2_mac` depending on which chip you are currently flashing).

## Step 4: Copy the Configuration

Once the MAC addresses are stored in your secrets file and the blank firmware is running on the device, it will appear online in your Dashboard.

1. Click **"Edit"** on your new node in the Dashboard.
1. Erase the default code that ESPHome generated.
1. Copy and paste the entire YAML configuration from the repository (e.g., `firmware/production/node-2-sound-hub.yaml`).
1. Hit **"Install"** in the top right corner. Because the device is now online, it will install wirelessly!

> [!TIP]
> **COMPLETED!** You never have to plug this Node into your computer via USB ever again. All future updates can be deployed directly through the air. You can now refer to the [Network & OTA Guide](network-ota-guide.md) for long-term management.