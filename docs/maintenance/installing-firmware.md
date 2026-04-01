# <i data-lucide="download"></i> Installing Firmware & Field Recovery
> **TECHNICAL OPERATIONS** | **v2.1.2-FINAL-STABLE**

The Wee2-D2 project utilizes a **Zero-Infrastructure** deployment standard. Once your microcontrollers are "injected" with their initial code, all future updates and configuration changes are handled directly through the air—even when you are away from your home network (e.g., at a 501st convention, parade, or hospital visit).

---

## Step 0: Initial USB Flash
Before a node can be updated wirelessly, it must be flashed via USB once to establish its identity and Wi-Fi credentials.

> [!IMPORTANT]
> **[First-Time Firmware Setup](first-time-firmware-setup.md)** 
> Follow this guide if you are starting with a factory-new ESP32 or need to perform a complete manual reset.

---

## Method 1: Direct Web OTA (Standard Update)
This is the primary method for deploying production updates (`.bin` files) without needing a local build server.

1. **Download**: Obtain the latest firmware binaries for your specific nodes.
2. **Navigate**: On your laptop or phone, go to the node's individual Dashboard (e.g., `http://wee2d2-sound.local/`).
3. **Upload**:
 - Scroll to the bottom of the dashboard to the **OTA Update** section.
 - Select the appropriate `.bin` file and click **Update**.
4. **Confirm**: The node will reboot and apply the new firmware in seconds.

---

## Method 2: The Captive Portal (Network Provisioning)
Use this method if the droid is powered on but cannot find its known network, or if you need to move it to a new location.

1. **Wait for Fallback**: If a node cannot find its home Wi-Fi for **60 seconds**, it will automatically broadcast its own network.
2. **Connect**: On your mobile device, look for the Wi-Fi network named **`WEE2-D2_SETUP`**.
3. **Authentication**: Use the convention-standard password: `wee2d2setup`.
4. **Configure**: A "Sign in to network" page should automatically appear. Select the local Wi-Fi from the list and enter its password to migrate the node.

---

## Method 3: Browser-Based Web Phasing (Cloud Recovery)
Use this method if the firmware is corrupted or the Wi-Fi stack is unresponsive.

1. **Connect**: Plug the node into your computer via a data-capable USB cable.
2. **Visit**: Open the public Documentation portal in a Chromium-based browser (Chrome/Edge).
3. **Flash**:
 - Select **[PROCEED] START FIRMWARE INJECTION**.
 - Select the **COM Port** from the browser popup.
 - The browser will securely flash the latest stable production firmware directly from the cloud.

---

> [!TIP]
> **Operational Density**: These methods ensure that the Documentation is 100% serverless. All code compilation happens in the cloud, and all deployment is handled directly between your device and the droid's built-in web server.
