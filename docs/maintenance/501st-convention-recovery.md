# 🛰️ 501st Convention Recovery (On-the-Road Updates)
> **MAINTENANCE & OPERATIONS** | **v2.0-Hybrid Procedure**

This guide outlines how to update or recover your Wee2-D2 droid when you are away from your home network (e.g., at a 501st convention, parade, or hospital visit).

---

## ⚡ Method 1: The Captive Portal (Preferred)
Use this method if the droid is already powered on but cannot find its known network.

1.  **Wait for Fallback**: If the droid cannot find its home Wi-Fi for **60 seconds**, it will automatically broadcast its own network.
2.  **Connect**: On your phone, look for the Wi-Fi network named **`WEE2-D2_SETUP`**.
3.  **Password**: Use the convention-standard password: `wee2d2setup`.
4.  **Open Portal**: A "Sign in to network" page should automatically appear. If not, open your browser and go to `http://192.168.4.1`.
5.  **Configure**: Select the convention's Wi-Fi from the list and enter its password. 
6.  **Saved**: The droid will save these credentials to its persistent memory (NVS) and attempt to connect.

---

## 💻 Method 2: The Web-Flasher (USB Recovery)
Use this method if the firmware is corrupted, the Wi-Fi is completely down, or you need to perform a "Zero-Touch" reset.

1.  **Connect**: Plug the droid's MCU (Body or Dome) into your laptop via a high-quality USB-C or Micro-USB cable.
2.  **Visit**: Go to your repository's public site: `https://ruzzler.github.io/Wee2-D2/`.
3.  **Flash**:
    - Click **[PROCEED] START FIRMWARE INJECTION**.
    - Select the **COM Port** that appears in the browser popup.
    - The browser will now securely flash the "Convention-Ready" firmware onto the chip using **Dummy Credentials**.
4.  **Setup**: Once finished, follow **Method 1** above to connect the droid to the local Wi-Fi.

---

## 🛡️ Security Note: Dummy Credentials
The Web-Flasher uses a **Safe-Context** build. It strictly compiles using `dummy-secrets.yaml`, ensuring that your home Wi-Fi SSID and Password are **never** released to the public internet. 

> [!TIP]
> **OTA Persistence**: Even if you flash via Method 2, once the droid is back on your home network, the **Auto-OTA Pipeline** on your Unraid server will recognize it and automatically re-inject your secure home credentials on the next push.
