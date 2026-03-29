# 🚀 Body Drive System
> **FUNCTIONAL CAPABILITY** | **SERIAL: CAP-DRIVE-v1.0**

Wee2-D2 is an agile, 2-wheel-drive unit powered by two massive brushless hub motors embedded directly within its side feet. This system operates natively on the **Main 20V High-Power Rail** with zero Step-Down conversion. 

## 🔌 The VESC Speed Controllers
Locomotion is orchestrated by two **Flipsky Mini FSESC 6.7 Pro** motor controllers, based heavily on the open-source VESC architecture.

*   **Continuous Rating**: 70 Amps
*   **System Voltage**: Powered directly by the raw output of the 20V battery -> 40A Low Voltage Cutoff -> Main Fuse Bus.
*   **VESC Tool Integration**: These controllers must be programmed via USB using the open-source VESC Tool software. They manage motor resistance mapping, over-current protection, and the precision start/stop braking required by heavy droids moving around convention floors.

## 🛞 Hub Motor Specifications
The Flipsky controllers pump power down to two **L-faster FLD-5 5" Hub Motors**.
*   **Operating Voltage**: 24V (They easily spin on the 20V nominal rail).
*   **Current Limit**: Rated for 200W, meaning they naturally pull 8-10A each under load.
*   **Brushless Design**: Operates entirely silent without grinding gearbox gears. These are the same frictionless motors found in modern e-scooters.

## 🎮 RC Mixing & Interaction
Unlike the Audio and Dome systems, the Body Drive system operates **without** relying on an ESP32 MCU to translate signals. The Flipsky VESCs are incredibly intelligent.
1.  **Transmitter**: Powered by **HOTRC DS-600 #1** (The one-handed thumb joystick variant).
2.  **In-Radio V-Tail Mixing**: The HOTRC radio must be put into **Mixing Mode (1)**. When you push the joystick **UP**, it cleanly signals *both* motor controllers to move forward. When you push **LEFT/RIGHT**, it signals the motors to counter-rotate, letting Wee2-D2 spin seamlessly like a tank on its center axis!
3.  **Physical Link**: The PWM wires from CH1 and CH2 on the receiver run *straight* into the PWM input pins of the left and right Flipsky ESCS. 
4.  **Mixing Matrix Calibration**: The transmitter must be manually set to **Mode (1)** to enable the mechanical "Tank Mix."

### 🕹️ The DS-600 Mixing Matrix
If your droid is "one-legging" or steering incorrectly, check the icon in the circle on your remote screen:
*   **Mode (1)**: **REQUIRED FOR BODY**. Mixes CH1/CH2 for tank steering. 
*   **Mode (1)(2)**: **AVOID**. Mixes all 4 channels; will interfere with sound triggers.
*   **Mode (2)**: **INCORRECT**. Mixes CH3/CH4 only; droid will not steer.
*   **No Icon**: **INCORRECT**. Standard logic; droid will not steer.

> [!TIP]
> **To Cycle Modes**: Turn the remote **OFF**. Hold **Button 3** and turn the remote **ON**. Repeat until you see only the **(1)** icon.

---
**Relevant Hardware:**
*   [Flipsky Mini FSESC 6.7 Manual](../../hardware/flipsky-fsesc-67-pro-manual.md)
*   [Hub Motor Data Sheet](../../hardware/hub-motor-manual.md)
*   [HOTRC Receiver & Binding](../../hardware/hotrc-ds600-manual.md)
