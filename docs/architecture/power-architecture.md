# Wee2-D2 Power Architecture

This document tracks the electrical routing and protection systems for the Wee2-D2 droid.

## 🔋 Master Source
The droid is powered by **DeWalt 20V Batteries**.

## 🛡️ Protection Layer & Main Distribution
1.  **MgcSTEM LVP-R1.5 (40A Cutoff)**: Protects DeWalt batteries from over-discharge (17.5V recommended cutoff).
2.  **Positive Blade Fuse Box**: Receives the raw 20V Positive line from the MgcSTEM.
3.  **Negative Bus Bar (Star Ground)**: Receives the raw 20V Negative line. *Every single ground wire in the entire droid traces back to this massive metal bus bar to create a perfect "Star Ground" topology, ensuring crystal clear UART data transmission.*

From the Fuse Box and Bus Bar, **five** distinct 20V (+/-) power lines are sent outward:

### **Body Electronics (Lower)**
- **Left Drive ESC**: 20V ➔ [Flipsky Mini FSESC 6.7 Pro](../hardware/flipsky-fsesc-67-pro-manual.md) (Left). 
- **Right Drive ESC**: 20V ➔ Flipsky ESC (Right).
- **Sound System**: 20V ➔ [DY-HL50T Sound Module](../hardware/pemenol-60w-voice-manual.md) (60W Mono).

### **Dome Electronics (Upper)**
Because the CNBTR Slip Ring has exactly 6 wires (10A per circuit), I send **TWO separate 20V lines** (consuming 4 wires total) up into the dome to completely isolate the sensitive microchips from the noisy dome motor:
1.  **Slip Ring Line 1 (Motor Power)**: 20V ➔ goBILDA 15A Motor Controller.
2.  **Slip Ring Line 2 (Logic Power)**: 20V ➔ **Mini560 Pro Buck Converter** ➔ steps down to 5V ➔ 2x 5-Port Wago Connectors ➔ Powers MCU 2, MCU 3, and all Dome LEDs. 

*The remaining 2 slip ring wires carry the 3.3V UDNS UART TX and RX data.*

> [!CAUTION]
> **5V REGULATION**: All dome lighting components (Logic, PSIs, Strips) share a common 5V rail fed by the Wagos. **Never** connect the 5V BEC from the motor controller to the 5V lighting rail as it will immediately destroy the micro-LEDs.

## 🧠 5V BEC Logic Routing
Instead of packing the body with extra buck converters, I intelligently steal 5V from the massive motor controllers (which have built-in "BEC" step-down regulators):
*   **Body Logic**: The Flipsky ESCs output 5V to power the **Body HOTRC F-06A Receiver**. The receiver *then* outputs that 5V straight into **MCU 1 (Body Brain)**.
*   **Dome Motion Logic**: The goBILDA 15A ESC outputs 5V to power the **Dome HOTRC F-06A Receiver**.

## ⚠️ Safety Logic & Clamping
- **Motion Controller**: Software clamp in MCU 3 restricts the 20V source to 60% power to simulate a safe **12V** output for the motor.
- **Lighting Controller**: Brightness limiter enabled at **3500mA** to protect the Mini560 buck converter.
