# 🧩 Troubleshooting Matrix: Wee2-D2

If your droid begins exhibiting non-compliant behavior, use this matrix to diagnose the specific point of failure in the Imperial architecture.

| Symptom | Probable Cause | Corrective Action |
| :--- | :--- | :--- |
| **No Power / No Lights** | Main Fuse Blown | Check main bus bar; replace with 30A-40A fuse. |
| **No Power / No Lights** | LVC Active | Battery voltage < 16V. Replace DeWalt battery. |
| **Dome Won't Rotate** | Slip Ring Fault | Clean slip ring with DeoxIT; check TX signal pin. |
| **Dome Won't Rotate** | ESC Calibration | Re-calibrate goBILDA ESC throttle range. |
| **Sound is Distorted** | Low Logic Power | Check Buck Converter output; ensure 5.1V stable. |
| **Sound is Distorted** | Poor Grounding | Ensure common ground is tied to the soundboard amp GND. |
| **LEDs Flickering** | Data Noise | Increase wire thickness; add 470-ohm resistor to data line. |
| **Cannot Connect to IP** | DHCP Lease Expired | Check router; use static IP in `secrets.yaml`. |
| **"Angry Mode" Fails** | UDNS Link Fault | Check GPIO 13-to-5 serial connection (UDNS). |

---

## 🛠️ Diagnostics Bench

### **1. ESPHome Logs**
The most powerful tool at your disposal is the **ESPHome Logger**.
1.  Connect the ESP32 to your PC via USB.
2.  Open the ESPHome Dashboard.
3.  Click **Logs** on the problematic node.
4.  **Watch for Errors**: UART timeouts, Wi-Fi disconnects, or I2C bus failures will appear in RED text.

### **2. Unified Droid Nervous System (UDNS) Serial Bus Test**
To verify communication across the slip ring:
1.  Open the **Body Brain (Node 1)** Logs.
2.  Trigger a sound.
3.  Look for a log entry like `[D][uart_debug:158]: >>> "CMD:PLAY_01\n"`.
4.  Open the **Dome Node** Logs and confirm it receives the same string.

### **3. Multimeter Probe Points**
*   **VCC Rail**: Should be **18V - 21V** (Main Battery).
*   **Logic Rail**: Should be **5.0V - 5.2V** (Buck Output).
*   **Signal GND**: Continuity should exist between ALL GND pins across ALL ESP32s.
