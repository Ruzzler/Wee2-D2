# 💻 First-Time Firmware Setup (Initial USB Flash)
> **OPERATION & MAINTENANCE**

Before your ESP32 microcontrollers can be updated wirelessly over your local network, they must be "injected" with their initial code and Wi-Fi credentials via a physical USB connection.

---

## 🛠️ Prerequisites
1.  **A Computer**: PC, Mac, or Linux machine.
2.  **Google Chrome or Microsoft Edge**: The physical USB flash utilizes the [Web Serial API](https://developer.mozilla.org/en-US/docs/Web/API/Web_Serial_API), which is only supported in Chromium-based browsers. Safari/Firefox will not work.
3.  **Data-Capable USB Cable**: A high-quality USB-Micro (for ESP32D) or USB-C (for S3 Mini) cable. *Warning: Many cheap cables only provide power and cannot transmit data.*

## 🔑 Step 1: Prepare the Secrets File
Your ESP32s need to know your Wi-Fi password so they can connect to your local network and the ESPHome dashboard.

1.  In the `Wee2-D2` repository, navigate to the `firmware/` folder.
2.  Locate the file named `secrets.yaml.example`.
3.  Rename it to `secrets.yaml`.
4.  Open the file and enter your actual Wi-Fi SSID and Password.

## ⚡ Step 2: The Physical Flash
1.  Plug your ESP32 into your computer via USB.
2.  Open your [ESPHome Dashboard](https://esphome.io/).
3.  Click **"New Device"**.
4.  Click **"Continue"**, give it the name corresponding to the MCU (e.g., `mcu1-body-controller`).
5.  Click **"Connect"** and select the **USB/COM Port** that appears in your browser popup.
6.  Click **"Install"**.

*Note: The first compilation process can take up to 5 minutes as it generates the C++ bin file. Do not unplug the cable!*

## 🔄 Step 3: Copy the Configuration
Once the blank firmware is running on the device, it will connect to your Wi-Fi and appear online in your Dashboard.

1.  Click **"Edit"** on your new node in the Dashboard.
2.  Erase the default code that ESPHome generated.
3.  Copy and paste the entire YAML configuration from the repository (e.g., `firmware/production/mcu1-body-controller/body-brain.yaml`).
4.  Hit **"Install"** in the top right corner. Because the device is now online, it will install wirelessly!

> [!TIP]
> **COMPLETED!** You never have to plug this MCU into your computer via USB ever again. All future updates can be deployed directly through the air. You can now refer to the [Network & OTA Guide](network-ota-guide.md) for long-term management.
