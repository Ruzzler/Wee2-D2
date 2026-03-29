# 🔄 Dome Rotation System
> **FUNCTIONAL CAPABILITY** | **SERIAL: CAP-DOME-v1.0**

Wee2-D2's 360° dome rotation is driven by a precision heavy-duty motor, interpreted exclusively by **MCU 3 (Motion Controller)** running ESPHome.

## 🛞 The goBILDA Hardware
The physical rotation relies on a **goBILDA 5203 Yellow Jacket Motor** (117 RPM / 12V). This motor is incredibly torquey and interfaces perfectly with the 3D-printed dome ring gear.

To drive this motor, the droid uses a **goBILDA 15A Cont PWM ESC** securely mounted inside the body.
*   **Safety Interlock**: The ESC boots up fully disengaged. It requires a neutral 1500μs PWM signal to arm, preventing the dome from wildly spinning when you turn on the main power.

## ⚡ 60% Software Throttling (Crucial)
The single most important firmware logic for Dome Rotation handles the power mismatch between the battery and the motor.
> [!WARNING]
> The droid's main bus is **20V** (DeWalt Battery). However, the goBILDA motor is only rated for **12V**. Do not plug it directly into the battery!

Instead of buying a massive, expensive 12V Buck Converter just for the motor, we handle this in the **MCU 3** software. MCU 3 listens to your joystick, calculates how fast you *want* to spin, and scales the signal down by exactly 60%. Thus, applying "100% Throttle" on the joystick only commands the ESC to output an effective 12V. 

```cpp
// ESPHome Dome Clamp Logic Example
float val = (raw_pwm - 1.5e-3) / 0.5e-3; // Normalize input to -1.0 to 1.0
return val * 0.6; // Scale down safely to 60% max output
```

## 🎮 Control Mapping
The dome is separated from the main drive logic.
1.  **HOTRC #2**: The builder carries a second, miniaturized HOTRC DS-600 transmitter used exclusively by MCU 3.
2.  **CH1 Input**: This steering channel dictates the left/right rotation of the dome head. MCU 3 reads this PWM signal and filters out minor "stick drift" by employing a wide deadband around the 1500μs center point to ensure the dome rests perfectly still when the stick is released.

---
**Relevant Hardware & Code:**
*   [MCU 3: Motion Controller](../../../firmware/mcu3-motion-controller/README.md)
*   [goBILDA 5203 Hardware Manual](../../hardware/gobilda-motor-manual.md)
