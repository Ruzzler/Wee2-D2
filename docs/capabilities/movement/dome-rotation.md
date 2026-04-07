# <i data-lucide="refresh-cw"></i> Dome Rotation System

Wee2-D2's 360° dome rotation is driven by a precision heavy-duty motor, interpreted exclusively by **Node 1 (Dome Motion Controller)** running ESPHome.


## The goBILDA Hardware

The physical rotation relies on a **goBILDA 5203 Yellow Jacket Motor** (117 RPM / 12V). This motor is incredibly torquey and interfaces perfectly with the 3D-printed dome ring gear.

To drive this motor, the droid uses a **goBILDA 15A Cont PWM ESC** securely mounted inside the **dome hub**.
- **Power Source**: Powered by 20V directly from the **Ganged Wago Hub** (See [Body Wiring Guide](../../architecture/body-wiring-guide.md)).
- **Signal (White)**: Connected to **Node 1 (GPIO 7)**.
- **Safety Interlock**: The ESC boots up fully disengaged. It requires a neutral 1500μs PWM signal to arm, preventing the dome from wildly spinning when you turn on the main power.


## Physical Voltage Handling

Unlike common brushed ESCs that are strictly 12V-only, the specialized **goBILDA 1x15A** speed controller used in the dome is a robust, discontinued model that natively supports **12V-24V input**.

- **Direct Rail Integration**: The ESC is wired directly to the **20V High-Power Rail** via the slip ring.
- **Native Output**: The controller internally manages the power delivery for the 12V Yellow Jacket motor, eliminating the need for a bulky external Buck Converter or specialized software voltage-clamping for electrical protection.


## Control Mapping

The dome is separated from the main drive logic.

1. **HOTRC #2**: The builder carries a second, miniaturized HOTRC DS-600 transmitter used exclusively by Node 1.
1. **CH1 Input**: This steering channel dictates the left/right rotation of the dome head.

Node 1 reads this PWM signal and filters out minor "stick drift" by employing a wide deadband around the 1500μs center point to ensure the dome rests perfectly still when the stick is released.


## Master Relay Role

In the **v2.6.0 Architecture**, Node 1 acts as the primary "System Dispatcher" for the dome.
- **Listens** for ESP-NOW dashboard triggers (`0xA0`, `0xA1`) from the Neural Command Center (Node 2).
- **Triggers** the WLED board locally via UART (GPIO 5) for synchronized effects.

---

**Relevant Hardware & Code:**
- [Node 1: Dome Master](../../architecture/node-1-dome-motion.md)
- [Node Pinout Guide](../../architecture/node-pinout-guide.md)