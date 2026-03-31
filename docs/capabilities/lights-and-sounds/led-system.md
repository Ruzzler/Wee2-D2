# 💡 LED Arrays & Displays
> **FUNCTIONAL CAPABILITY** | **SERIAL: CAP-LIGHT-v1.0**

The visual personality of Wee2-D2 is driven by high-density **WS2812B addressable LED** matrices, controlled by **MCU 2 (Lighting Controller)** running the **WLED** framework with **ESP-NOW** wireless synchronization.

## 🔋 Power Constraints
Because there are hundreds of LEDs in the dome, they have their own dedicated **Mini560 5V Buck Converter (Buck 1)** tied to the 20V Ganged Wago Hub. 
> [!CAUTION]
> The LED matrices (especially the GrnWave PSIs) will instantly blow if exposed to more than 5.2V. By using the **Dual-Buck Strategy**, we isolate these high-current light sweeps from the sensitive logic pins of the ESP32.

## 🗺️ Physical LED Mapping
The LEDs are split across two primary data lines emitting from MCU 2:

| Display | Type | Configuration | Pin (GPIO) | Wire Color |
| :--- | :--- | :--- | :---: | :--- |
| **Front Logic** | WS2812B | 10x2 Matrix (20 pixels) | **18** | 🟨 Yellow |
| **Rear Logic** | WS2812B | 12x2 Matrix (24 pixels) | **19** | 🟨/⬛ Yellow/Blk |
| **Front PSI** | GrnWave | Circular (76 pixels) | **21** | 🟩 Green |
| **Back PSI** | GrnWave | Circular (76 pixels) | **22** | ⬜ White |

## ⚙️ WLED 2D Setup
To achieve cinematic animations, the WLED interface is configured using **2D Matrix segments**. 
1.  Even though the Rear Logic is physically split into two square windows, treating them as one consecutive 10x2 strip in WLED allows scanning animations to flow across both windows.
2.  The [GrnWave PSIs](../../hardware/grnwave-psi-manual.md) are mapped by concentric rings (Outer, Inner, Core) to allow layered breathing and strobing effects.

---
**Relevant Hardware & Code:**
*   [MCU 2: Lighting Controller](../../../firmware/mcu2-lighting-controller/README.md)
*   [GrnWave PSI Manual](../../hardware/grnwave-psi-manual.md)
