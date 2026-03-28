# Node 2: Dome Lights (WLED)

This node is dedicated to controlling the WS2812 addressable LED system in the dome using **WLED**.

## 🔋 Power Management & Safety
> [!IMPORTANT]
> To protect the Mini560 5V buck converter from overheating or melting during high-intensity light shows (e.g., full-white flashes), the WLED brightness limiter **MUST** be enabled.

- **Current Limit**: Clamp to **3500mA** in the WLED "LED Preferences" menu.
- **Hardware**: Mini560 5V Buck Converter powered by 20V from the slip ring.

## 💡 LED Hardware Layout
| Device | LED Type | Qty | Dimensions | Notes |
| :--- | :--- | :---: | :---: | :--- |
| **Front Logic** | WS2812B | 24 | 12 x 2 | Main status display (Data Pin A) |
| **Rear Logic** | WS2812B | 20 | 10 x 2 | Split into 2x (5x2) blocks (Data Pin B) |
| **Front/Rear PSI** | WS2812B-2020 | 152 | 76 x 2 | GrnWave Circular Boards. **5V ONLY!** |

> [!CAUTION]
> **VOLTAGE SENSITIVITY**: The GrnWave PSI boards use micro 2020-size LEDs that are extremely sensitive. **Do not exceed 5.0V**. Powering them from the 6V BEC of the motor controller will cause immediate failure. Use the dedicated **Mini560 5V Regulator**.

## ⚙️ WLED 2D Configuration
To achieve authentic "Logic" scrolling:
1.  **Front Logic**: In WLED 2D settings, set as a matrix of **12 Width x 2 Height**.
2.  **Rear Logic**: Set as a matrix of **10 Width x 2 Height**. Even though they are physically separated, treating them as one 10x2 strip in WLED allows animations to flow across both windows.

- **Total Pixels**: ~200 LEDs.
- **PSI Boards**: 2x Grnwave PSI boards.
- **Support Strips**: 1x 12-pixel strip, 2x 5-pixel strips.

## 🔴 "Angry/Red" Trigger Logic
WLED is configured to listen for a hardwired HIGH/LOW signal from the **Body Brain**.

### Physical Button Configuration
1. Connect a spare GPIO on the Dome Lights ESP32 to a signal wire coming from the Body Brain.
2. In WLED **Config > Time & Macros**:
   - Define a Macro (e.g., Macro 1) that activates a Red/Angry preset.
3. In WLED **Config > LED Preferences**:
   - Assign the GPIO to "Button 0".
   - Set the button type to "Pushbutton" or "Switch" depending on the trigger logic.
   - Assign the Macro to the button's "on" state.

## 🔗 Useful Links
- [WLED Documentation](https://kno.wled.ge/)
- [Grnwave PSI Setup Guide](https://grnwave.com/)
