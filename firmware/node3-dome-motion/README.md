# 🦾 Node 3: Dome Motion (ESPHome)
> **ESPHome Firmware** | **ESP32-S3 Super Mini**

The **Dome Motion** node provides high-torque, non-blocking control of the 5203 Yellow Jacket motor via a goBILDA 15A ESC. It translates RC receiver signals into brushed motor throttle commands with integrated safety clamping.

## 🚀 Core Features
*   **RC Steering Input**: Decodes CH1 from the dome's secondary HOTRC receiver.
*   **Voltage Clamping**: Limits maximum throttle to 60% (-0.6 to 0.6) to effectively step down the 20V battery input to a safe **12V limit** for the motor.
*   **Deadband Logic**: Prevents motor hum or stick drift around the 1500μs center point.
*   **Safety Interlocks**: 
    *   **Boot Stop**: Forces speed to 0% on controller power-up.
    *   **Shutdown Stop**: Disengages throttle if the ESP32 is rebooted or loses connection.
*   **Compact Form Factor**: Designed for the ESP32-S3 Super Mini (22x18mm) inside the dome hub.

## 🔌 Pinout Configuration
| Connection | ESP32 Pin | Logic |
| :--- | :---: | :--- |
| **RC CH1 (Steering)** | GPIO4 | PWM Input |
| **ESC PWM Signal** | GPIO18 | PWM Output (LEDC) |

## 🛠️ Configuration
The configuration is defined in [`dome-motion.yaml`](./dome-motion.yaml).

### ESC Calibration
The setup uses a standard ESC frequency of **50Hz**. 
*   **Zero Position**: `0.075` (1500μs).
*   **Min/Max Power**: `0.05` to `0.10` (1000μs to 2000μs).

### Voltage Safety (Clamping)
Because the droid runs on a **20V** battery bus but the motor is rated for **12V**, the following logic is used in the firmware to ensure longevity:
```cpp
float val = (x - 1.5e-3) / 0.5e-3; // Normalize input to -1.0 to 1.0
return val * 0.6; // Scale down to 60% (approx 12V effective)
```
