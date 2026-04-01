# <i data-lucide="battery-charging"></i> Power Architecture

This document tracks the electrical routing, distribution, and protection systems for Wee2-D2. Locomotion and logic systems are isolated into distinct rails to ensure signal integrity and operational stability.

---

## 1. The Core Source

The droid operates on a **20V High-Power Standard**, sourcing energy from a ganged **DeWalt 20V Battery** array.

### Protection Layer

- **Master LVP (MgcSTEM LVP-R1.5)**: A 40A low-voltage protector monitors the battery source. It is configured with a **17.5V Cutoff** to prevent over-discharge and permanent battery cell damage.
- **Positive Blade Fuse Box**: Receives the raw 20V Positive line from the LVP. Individual systems are fused for over-current protection.
- **Negative Bus Bar (Star Ground)**: Receives the raw 20V Negative line. All system grounds trace back to this central anchor for signal integrity.

---

## 2. Power Rail Hierarchy

Wee2-D2 utilizes two primary voltage rails to isolate high-current inductive motor noise from sensitive logic circuits.

### A. The 20V High-Power Rail

High-current components pull directly from the DeWalt batteries via the master fuse box:
- **Drive System**: 2x [Flipsky Mini FSESC 6.7 Pro](../hardware/flipsky-fsesc-67-pro-manual.md) (Left/Right) draw direct 20V.
- **Dome Motion**: The goBILDA 15A ESC draws 20V via the Slip Ring bridge.
- **Audio System**: The **TPA3118 60W Amplifier** draws 20V for maximum sonic output.

### B. The 5.1V Logic & Audio Rail

Sensitive micro-electronics utilize step-down regulators to provide stable 5.1V logic power:
- **Body Logic**: Steals 5.1V from the Flipsky ESC built-in BEC to power [Node 1 (Sound Hub)](node-1-sound-hub-spec.md) and the body receiver.
- **Dome Logic**: [Node 2 (LEDs)](node-2-led-distribution-spec.md) uses a dedicated **Mini560 10A Buck Converter** to drive high-density LED arrays.
- **Dome Motion Logic**: [Node 3 (Motion)](node-3-dome-motion-spec.md) steals 5.1V from the goBILDA BEC to power the motion controller and dome receiver.

---

## 3. The Slip Ring Bridge (Body Dome)

The **CNBTR Slip Ring** (6 wires) acts as the high-current bridge between the chassis and the rotating dome. To ensure stability, we utilize a **Dual-Circuit Isolation Strategy**:

| Circuit | Function | Current (Peak) | Slip Ring Wires |
| :--- | :--- | :---: | :---: |
| **Circuit 1** | **Dome Motor (20V)** | 10.0A | C1 (+) / C2 (-) |
| **Circuit 2** | **Dome Logic & LEDs (20V)** | 10.0A | C3 (+) / C4 (-) |
| **Expansion** | Reserved for Serial / Telemetry | — | C5 / C6 |

> [!CAUTION]
> **ISOLATION REQUIRED**: Never bridge the 20V (+) lines of Circuit 1 and Circuit 2. The dome motor generates significant inductive spikes that will destabilize the LED logic if the rails are not isolated through the slip ring.

---

## 4. Grounding & Safety
### Grounding Rule
Every component in the droid (Nodes, ESCs, Receivers, and LED Strips) **MUST** share a common ground reference. All grounds trace back to the central Negative Bus Bar.
Without this shared reference, the UART and PWM data signals will become unreadable atmospheric noise.

### Logic Clamping & Safety
- **Motion Clamp**: Node 3 restricts the 20V source to 60% software power to simulate 12V for the goBILDA motor.
- **Current Limiters**: Node 2 maintains an internal brightness limit of **3500mA** to protect the buck converters from thermal runaway.

---

[View Electrical Schematic](electrical-schematic.md)