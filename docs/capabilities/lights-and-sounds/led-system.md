# 💡 LED Arrays & Displays
> **FUNCTIONAL CAPABILITY** | **SERIAL: CAP-LIGHT-v1.0**

The visual personality of Wee2-D2 is driven by high-density **WS2812B addressable LED** matrices, entirely controlled by **MCU 2 (Lighting Controller)** running the powerful **WLED** framework.

## 🔋 Power Constraints
Because there are hundreds of LEDs in the dome, they have their own dedicated **Mini560 5V Buck Converter** tied to the 20V slip ring. 
> [!CAUTION]
> The LED matrices (especially the GrnWave PSIs) will instantly blow if exposed to more than 5.2V. You must also enforce a **3500mA** software current limit in WLED to prevent the 3D printed dome mounts from melting.

## 🗺️ Physical LED Mapping
The LEDs are split across two primary data lines emitting from MCU 2:

| Display | Type | Configuration | Data Pin | Notes |
| :--- | :--- | :--- | :--- | :--- |
| **Front Logic** | WS2812B Strip | 12x2 Matrix (24 pixels) | Pin A | Main status display |
| **Rear Logic** | WS2812B Strip | 10x2 Matrix (20 pixels) | Pin B | Split into two 5x2 physical blocks |
| **Front/Rear PSI** | GrnWave 2020 | 76x2 Circular (152 pixels) | Pin C | Extremely sensitive micro-LEDs |

## ⚙️ WLED 2D Setup
To achieve authentic "Logic" scrolling, the WLED interface is configured using **2D Matrix segments**. 
1.  Even though the Rear Logic is physically split into two square windows, treating them as one consecutive 10x2 strip in WLED allows "Scanner" animations to flow beautifully across both windows seamlessly.
2.  The [GrnWave PSIs](../../hardware/grnwave-psi-manual.md) are mapped by concentric rings (Outer, Inner, Core) to allow layered breathing and strobing effects.

## 🔴 "Angry Mode" Integration
WLED is natively integrated into the **Unified Droid Nervous System (UDNS)**. 
When the Body Controller (MCU 1) detects the trigger for "Angry Mode", it transmits a UART signal across the slip ring to MCU 2. WLED interprets this serial command to instantly override the standard blue/white logic sweeps and force all 200 dome LEDs to pulse solid Red. 

---
**Relevant Hardware & Code:**
*   [MCU 2: Lighting Controller](../../../firmware/mcu2-lighting-controller/README.md)
*   [GrnWave PSI Manual](../../hardware/grnwave-psi-manual.md)
