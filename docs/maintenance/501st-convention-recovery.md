# 🛰️ 501st Convention Recovery (On-the-Road Updates)
> **MAINTENANCE & OPERATIONS** | **v2.1.0-Zero-Infra Procedure**

This guide outlines how to update or recover your Wee2-D2 droid when you are away from your home network (e.g., at a 501st convention, parade, or hospital visit).

---

## ⚡ Method 1: The Captive Portal (Provisioning)
Use this method if the droid is powered on but cannot find its known network.

1.  **Wait for Fallback**: If the droid cannot find its home Wi-Fi for **60 seconds**, it will automatically broadcast its own network.
2.  **Connect**: On your phone, look for the Wi-Fi network named **`WEE2-D2_SETUP`**.
3.  **Password**: Use the convention-standard password: `wee2d2setup`.
4.  **Open Portal**: A "Sign in to network" page should automatically appear. If not, open your browser and go to `http://192.168.4.1`.
5.  **Configure**: Select the convention's Wi-Fi from the list and enter its password. 

---

## 💻 Method 2: Direct Web OTA (Drag-and-Drop)
Use this method for standard production updates without needing any build servers or local infrastructure.

1.  **Download**: Obtain the latest `.bin` firmware files from the **GitHub Releases** page of your repository.
2.  **Navigate**: On your laptop or phone, go to the droid's local IP address or hostname (e.g., `http://wee2d2-sound.local/`).
3.  **Update**:
    - Scroll to the bottom of the Imperial Dashboard to the **OTA Update** section.
    - Select the appropriate `.bin` file (e.g., `node-1-sound-hub.bin`) and click **Update**.
4.  **Confirm**: The droid will reboot and apply the new firmware in seconds.

---

## 🛠️ Method 3: The Web-Flasher (USB Recovery)
Use this method if the firmware is corrupted or the Wi-Fi is completely down.

1.  **Connect**: Plug the droid's MCU into your laptop via a high-quality USB-C cable.
2.  **Visit**: Go to your repository's public site: `https://ruzzler.github.io/Wee2-D2/`.
3.  **Flash**:
    - Click **[PROCEED] START FIRMWARE INJECTION**.
    - Select the **COM Port** that appears in the browser popup.
    - The browser will securely flash the version of the firmware hosted in the cloud.
4.  **Setup**: Once finished, follow **Method 1** above to connect the droid to the local Wi-Fi.

---

> [!TIP]
> **Zero-Infrastructure**: This workflow requires **zero** back-end servers. All code is compiled in the GitHub cloud, and all updates are handled directly between your device and the droid's built-in web server.
