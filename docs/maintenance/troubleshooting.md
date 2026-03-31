# 🧩 Troubleshooting Matrix: Wee2-D2

If your droid begins exhibiting non-compliant behavior, use this matrix to diagnose the specific point of failure in the Imperial architecture.

| Symptom | Probable Cause | Corrective Action |
| :--- | :--- | :--- |
| **No Power / No Lights** | Main Fuse Blown | Check main bus bar; replace with 30A-40A fuse. |
| **No Power / No Lights** | LVC Active | Battery voltage < 16V. Replace DeWalt battery. |
| **Dome Won't Rotate** | Motor Signal Fault | Check GPIO 7 PWM connection; ensure goBILDA ESC is armed. |
| **Dome Won't Rotate** | ESC Calibration | Re-calibrate goBILDA ESC throttle range. |
| **Sound is Distorted** | Low Logic Power | Check Buck Converter output; ensure 5.1V stable. |
| **Sound is Distorted** | Poor Grounding | Ensure common ground is tied to the soundboard amp GND. |
| **LEDs Flickering** | Data Noise | Increase wire thickness; add 470-ohm resistor to data line. |
| **Cannot Connect to IP** | DHCP Lease Expired | Check router; use static IP in `secrets.yaml`. |
| **Sync Failure** | Wireless Bridge Fault | Check ESP-NOW MAC pairing; ensure all nodes on WiFi Channel 1. |

---

## 🛠️ Diagnostics Bench

### **1. ESPHome Logs**
The most powerful tool at your disposal is the **ESPHome Logger**.
1.  Connect the ESP32 to your PC via USB.
2.  Open the ESPHome Dashboard.
3.  Click **Logs** on the problematic MCU.
4.  **Watch for Errors**: UART timeouts, Wi-Fi disconnects, or I2C bus failures will appear in RED text.

### **2. Wireless Bridge (ESP-NOW) Synchronization Test**
To verify the wireless behavioral triggers:
1.  Open the **Dome Master (MCU 3)** Logs.
2.  Trigger a movement or behavioral script.
3.  Look for a broadcast entry: `[D][esp_now:xxx]: Broadcast behavioral EVENT_ID_XX`.
4.  Open the **Body Audio Hub (MCU 1)** Logs and confirm it receives the event and triggers the DFPlayer: `[D][dfplayer:xxx]: Playing track XX`.

### **3. Multimeter Probe Points**
*   **VCC Rail**: Should be **18V - 21V** (Main Battery).
*   **Logic Rail**: Should be **5.0V - 5.2V** (Buck Output).
*   **Signal GND**: Continuity should exist between ALL GND pins across ALL ESP32s.
