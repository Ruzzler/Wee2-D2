# <i data-lucide="refresh-cw"></i> Dome Rotation System

Wee2-D2's 360° dome rotation is driven by a precision heavy-duty motor, interpreted exclusively by **Node 3 (Motion Controller)** running ESPHome.

## The goBILDA Hardware

The physical rotation relies on a **goBILDA 5203 Yellow Jacket Motor** (117 RPM / 12V). This motor is incredibly torquey and interfaces perfectly with the 3D-printed dome ring gear.

To drive this motor, the droid uses a **goBILDA 15A Cont PWM ESC** securely mounted inside the **dome hub**.
- **Power Source**: Powered by 20V directly from the **Ganged Wago Hub** (See [Body Wiring Guide](../../architecture/body-wiring-guide.md)).
- **Signal (White)**: Connected to **Node 3 (GPIO 18)**.
- **Safety Interlock**: The ESC boots up fully disengaged. It requires a neutral 1500μs PWM signal to arm, preventing the dome from wildly spinning when you turn on the main power.

## 60% Software Throttling (Crucial)

The single most important firmware logic for Dome Rotation handles the power mismatch between the battery and the motor.
> [!WARNING]
> The droid's main bus is **20V** (DeWalt Battery). However, the goBILDA motor is only rated for **12V**. Do not plug it directly into the battery!

Instead of buying a massive, expensive 12V Buck Converter just for the motor, I handle this in the **Node 3** software.
Node 3 listens to your joystick, calculates how fast you *want* to spin, and scales the signal down by exactly 60%. Thus, applying "100% Throttle" on the joystick only commands the ESC to output an effective 12V.

```cpp
// ESPHome Dome Clamp Logic Example
float val = (raw_pwm - 1.5e-3) / 0.5e-3; // Normalize input to -1.0 to 1.0
return val * 0.6; // Scale down safely to 60% max output
```

## Control Mapping

The dome is separated from the main drive logic.
1. **HOTRC #2**: The builder carries a second, miniaturized HOTRC DS-600 transmitter used exclusively by Node 3.
1. **CH1 Input**: This steering channel dictates the left/right rotation of the dome head.
Node 3 reads this PWM signal and filters out minor "stick drift" by employing a wide deadband around the 1500μs center point to ensure the dome rests perfectly still when the stick is released.

### Transmitter Mode: Standard (Unmixed)

Unlike the body, the dome uses a single-axis rotation. To prevent "signal bleed" from other joystick movements:
- **Correct Mode**: **[No Icon]** on the transmitter screen.
- **To Cycle Modes**: Turn the remote **OFF**. Hold **Button 3** and turn the remote **ON**. Repeat until the circle on the screen is **Empty**.

> [!TIP]
> Using **Standard Mode** ensures that accidental Up/Down movement of the thumb joystick does not trigger the dome's rotation ESC.

## Master Relay Role

In the **v1.6.2 Architecture**, Node 3 acts as the primary "System Dispatcher" for the dome.
- **Listens** for serial commands from the body (GPIO 16).
- **Triggers** the WLED board locally (GPIO 27) for synchronized effects.

---
**Relevant Hardware & Code:**
- [Node 3: Dome Motion Spec](../../architecture/node-3-dome-motion-spec.md)
- [Node Pinout Guide](../../architecture/node-pinout-guide.md)