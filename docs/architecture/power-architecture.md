# Wee2-D2 <i data-lucide="battery-charging"></i> Power Architecture

This document tracks the electrical routing and protection systems for the Wee2-D2 droid.

## <i data-lucide="database"></i> Master Source
The droid is powered by **DeWalt 20V Batteries**.

##  Protection Layer & Main Distribution
1.  **MgcSTEM LVP-R1.5 (40A Cutoff)**: Protects DeWalt batteries from over-discharge (17.5V recommended cutoff).
2.  **Positive Blade Fuse Box**: Receives the raw 20V Positive line from the MgcSTEM.
3.  **Negative Bus Bar (Star Ground)**: Receives the raw 20V Negative line. 

> [!IMPORTANT]
> **THE GOLDEN RULE OF GROUNDS**: Every component in the droid (MCUs, ESCs, Receivers, and LED Strips) MUST share a common ground reference. Every ground wire traces back to this central Negative Bus Bar to create a "Star Ground" topology. This is critical for signal integrity; without a shared reference, UART and PWM data signals will become unreadable static.

From the Fuse Box and Bus Bar, **five** distinct 20V (+/-) power lines are sent outward:

### **Body Electronics (Lower)**
- **Left Drive ESC**: 20V  [Flipsky Mini FSESC 6.7 Pro](../hardware/flipsky-fsesc-67-pro-manual.md) (Left). 
- **Right Drive ESC**: 20V  Flipsky ESC (Right).
- **Sound System**: 20V  [DFPlayer Mini / TPA3118 Amp](../hardware/dfplayer-mini-manual.md) (60W Mono).

### **Dome Electronics (Upper)**
Because the CNBTR Slip Ring has exactly 6 wires (10A per circuit), I send **TWO separate 20V lines** (consuming 4 wires total) up into the dome to completely isolate the sensitive microchips from the noisy dome motor:
1.  **Slip| System Tier | Voltage | Current Peak | Source |
| :--- | :---: | :---: | :--- |
| **Node 1 (Sound Hub)** | 5.1V | 2.5A | Internal 5V Buck |
| **Node 2 (LEDs)** | 5.1V | 8.0A | Dedicated 10A Buck |
| **Node 3 (Dome Motion)** | 5.1V | 1.5A | Internal 5V Buck |
2x 5-Port Wago Connectors  Powers MCU 2, MCU 3, and all Dome LEDs. 

*The remaining 2 slip ring wires (C5/C6) are RESERVED for future logic / telemetry expansion.*

> [!CAUTION]
> **5V REGULATION**: All dome lighting components (Logic, PSIs, Strips) share a common 5V rail fed by the Wagos. **Never** connect the 5V BEC from the motor controller to the 5V lighting rail as it will immediately destroy the micro-LEDs.

##  5V BEC Logic Routing
Instead of packing the body with extra buck converters, I intelligently steal 5V from the massive motor controllers (which have built-in "BEC" step-down regulators):
*   **Body Logic**: The Flipsky ESCs output 5V to power the **Body HOTRC F-06A Receiver**. The receiver *then* outputs that 5V straight into **MCU 1 (Body Audio Hub)**.
*   **Dome Motion Logic**: The goBILDA 15A ESC outputs 5V to power the **Dome HOTRC F-06A Receiver**.

##  Safety Logic & Clamping
- **Motion Controller**: Software clamp in MCU 3 restricts the 20V source to 60% power to simulate a safe **12V** output for the motor.
- **Lighting Controller**: Brightness limiter enabled at **3500mA** to protect the Mini560 buck converter.
