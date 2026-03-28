# 🏁 Calibration & Startup Guide: Wee2-D2

This guide ensures your droid is safely initialized and that all electronic systems are calibrated for professional operation.

---

## 🛠️ Pre-Flight Checklist
Before applying the 20V main power, verify:
*   [ ] **Main Fuse**: Ensure a 30A-40A fuse is seated in the main bus bar.
*   [ ] **Common Ground**: Check that all ESP32 grounds are tied to the star-ground point.
*   [ ] **Slip Ring Clearance**: Ensure the through-hole slip ring is clear of any debris or loose wires.
*   [ ] **Radio Bound**: Confirm both HOTRC DS-600 transmitters are bound to their respective receivers.

---

## 🏗️ Technical Calibration

### **1. ESC Throttle Calibration (Flipsky & goBILDA)**
To ensure the drive system and dome motor respond accurately:
1.  Remove the drive wheels (standard safety procedure).
2.  Turn on your **Body Transmitter** (TX #1).
3.  Set the drive stick to **Full Forward**.
4.  Apply 20V power to the droid.
5.  Wait for the ESC to beep (acknowledging full-throttle signal).
6.  Pull the stick to **Full Reverse** (or Neutral, depending on ESC model).
7.  Wait for the confirmation beep. **Calibration is complete.**

### **2. WLED Preset Configuration (UDNS Link)**
To sync your "Angry Mode" trigger:
1.  Navigate to the WLED Web UI via your phone (`http://WLED_IP`).
2.  Go to **Presets** and create a "Red Strobe" effect. Save as **Preset 5**.
3.  Go to **Settings > Macro / Button Actions**.
4.  Under "Button 0" (GPIO5 on S3 Mini), set the action to `P1=5&P2=1` (Pushes preset 5).
5.  Test by triggering an "Angry" sound on Node 1; the dome should instantly turn red via the **Unified Droid Nervous System (UDNS)**.

### **3. Dome Center Alignment**
The dome motor (goBILDA 15A ESC) operates on standard PWM (Servo) signals.
1.  Center the Dome Steering stick on your **Dome Transmitter** (TX #2).
2.  Physicaly rotate the dome until the main "Eye" is facing forward.
3.  If the dome is drifting slightly, use the **Trim** buttons on the HOTRC until the motor stops completely at neutral.

---

## 🚀 Startup Sequence
Follow this exact order to prevent "ghosting" signals:
1.  **Power ON Transmitters** (Body first, then Dome).
2.  **Slide DeWalt 20V Battery** into the LVC core.
3.  **Wait 10 Seconds** for the **Unified Droid Nervous System (UDNS)** to initialize and the "Imperial Databank Heartbeat" (GPIO 2 LED) to start blinking.
4.  **Confirm Sound Output**: Hit a small sound trigger to verify the 60W Amp is alive.
