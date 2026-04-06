# <i data-lucide="settings"></i> Calibration & Startup Guide: Wee2-D2

This guide ensures your droid is safely initialized and that all electronic systems are calibrated for professional operation.

---

## Pre-Flight Checklist

Before applying the 20V main power, verify:
- [ ] **Main Fuse**: Ensure a 30A-40A fuse is seated in the main bus bar.
- [ ] **Common Ground**: Check that all ESP32 grounds are tied to the star-ground point.
- [ ] **Slip Ring Clearance**: Ensure the through-hole slip ring is clear of any debris or loose wires.
- [ ] **Radio Bound**: Confirm both HOTRC DS-600 transmitters are bound to their respective receivers.

---

## Technical Calibration

### **1. ESC Throttle Calibration (Flipsky & goBILDA)**

To ensure the drive system and dome motor respond accurately:
1. Remove the drive wheels (standard safety procedure).
1. Turn on your **Body Transmitter** (TX #1).
1. Set the drive stick to **Full Forward**.
1. Apply 20V power to the droid.
1. Wait for the ESC to beep (acknowledging full-throttle signal).
1. Pull the stick to **Full Reverse** (or Neutral, depending on ESC model).
1. Wait for the confirmation beep. **Calibration is complete.**

### **2. WLED Preset Configuration (UART Link)**

To sync your behavioral triggers:
1. Navigate to the WLED Web UI via your phone (`http://WLED_IP`).
1. Go to **Presets** and create a "Red Strobe" effect. Save as **Preset 5**.
1. Go to **Settings > Macro / Button Actions**.
1. Under "Button 0" (GPIO5 on S3 Mini), set the action to `P1=5&P2=1` (Pushes preset 5).
1. Test by triggering a sound on Node 2 via the Dashboard; the dome should instantly turn red via the **UART Serial Sync**.

### **3. Dome Center Alignment**

The dome motor (goBILDA 15A ESC) operates on standard PWM (Servo) signals.
1. Center the Dome Steering stick on your **Dome Transmitter** (TX #2).
1. Physicaly rotate the dome until the main "Eye" is facing forward.
1. If the dome is drifting slightly, use the **Trim** buttons on the HOTRC until the motor stops completely at neutral.

---

## Startup Sequence

Follow this exact order to prevent "ghosting" signals:
1. **Power ON Transmitters** (Body first, then Dome).
1. **Slide DeWalt 20V Battery** into the LVC core.
1. **Wait 10 Seconds** for the **ESP-NOW Mesh** to initialize and the **System Status LED** (GPIO 2) to start blinking.
1. **Confirm Sound Output**: Hit a small sound trigger to verify the 60W Amp is alive.