# 🏛️ IMPERIAL DATABANK: MAINTENANCE GUIDE
> **DECRYPTED DATA REPOSITORY** | **SERIAL: OPS-MAINT-R2**

This guide covers the recurring maintenance tasks and software operations required to keep Wee2-D2 mission-ready.

## 🔋 Battery Management & Safety
Wee2-D2 is powered by **DeWalt 20V Max** lithium-ion batteries.

### ⚠️ Charging Safety
*   **Always** remove batteries from the droid before charging.
*   Use only official DeWalt chargers.
*   **Never** leave a charging battery unattended.

### 🛡️ Low Voltage Cutoff (LVC)
The **MgcSTEM LVP-R1.5** board is pre-programmed to protect your cells:
*   **Cutoff Voltage (`dn`)**: 16.5V - 17.0V (Relay will click and power will cut).
*   **Recovery Voltage (`UP`)**: 20.0V (Relay will only re-engage with a fresh battery).
*   **Verification**: Check the LCD display on the back of the droid regularly. If the voltage is near 17V, swap the pack immediately.

---

## 📡 Over-The-Air (OTA) Updates
You can update your droid's brain without opening the dome.

### 1. ESPHome (Node 1 & 3)
*   Ensure your PC is on the same WiFi as the droid (**Wee2D2-Internal**).
*   Run `esphome run firmware/nodeX/config.yaml`.
*   Select the **Wireless/OTA** port in the menu.

### 2. WLED (Node 2)
*   Navigate to `http://<NODE2_IP_ADDRESS>/settings/update`.
*   Upload the latest WLED `.bin` file or a saved configuration backup.

---

## 🩺 Droid Medic (Basic Troubleshooting)

| Issue | Potential Cause | Fix |
| :--- | :--- | :--- |
| **No Sound** | SD Card loose or Amp 20V fuse blown. | Check the SD card in the DY-HL50T; verify the 3A fuse. |
| **Dome Sluggish** | 20V supply sagging or Slip Ring friction. | Check battery voltage; inspect slip ring for debris. |
| **WiFi Lost** | Standard ESP32 antenna range limit. | Move closer to the droid or check the internal 5V buck converter. |
| **"Angry" Trigger Fails** | Node 1 to Node 2 link wire disconnected. | Inspect the GPIO signal wire running through the slip ring. |
