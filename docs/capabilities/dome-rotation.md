# <i data-lucide="rotate-ccw"></i> Dome Rotation System

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: DOME MOTION** | **MODEL: GOBILDA YELLOW JACKET**


This guide explains the dome motion mechanics for the Wee2-D2 project. It covers the high-torque planetary motor, PWM signal scaling, and behavioral movement logic managed by Node 1.


---


## Hardware Components (Motor & Drive)

The dome rotated by a **goBILDA 5203 Series Yellow Jacket** planetary gearmotor. This motor is selected for its high torque (117 RPM) and its ability to handle the overhung load of the aluminum dome assembly.


- **Model**: Yellow Jacket 5203 (12V Hub)
- **Drive Gear**: goBILDA 10-tooth Pinion (REX Profile)
- **Dome Gear**: 3D-Printed Internal Ring Gear
- **Coupling**: Structural 32mm Grid Mount


---


## PWM Signal Configuration (Software Scaling)

The dome motor is managed by a brushed PWM controller receiving signals from **Node 1 (Dome Master)** on GPIO 7. These levels are calibrated for the hotRC DS-600 radio system.


These levels are verified in the `v2.6.0-Dashboard` firmware sequence.


| PWM Parameter | Signal Level | Function | Citation |
| :--- | :--- | :--- | :--- |
| **GPIO Pin** | **GPIO 7** | Dome PWM Output | [node-1.yaml:11](../../firmware/production/node-1-dome-motion.yaml#L11) |
| **Min Level** | **0.05** | Counter-Clockwise Max | [node-1.yaml:152](../../firmware/production/node-1-dome-motion.yaml#L152) |
| **Idle Level** | **0.075** | Deadzone (Stationary) | [node-1.yaml:153](../../firmware/production/node-1-dome-motion.yaml#L153) |
| **Max Level** | **0.1** | Clockwise Max | [node-1.yaml:154](../../firmware/production/node-1-dome-motion.yaml#L154) |


---


## Movement Logic & Behavioral Tuning

Dome rotation is secondary to safety. If a manual RC stick command is detected on GPIO 4, all autonomous animations are immediately stopped to give the pilot full control.


1. **Idle Bobbing**: When the droid is idle, Node 1 executes random, slow-speed "scans" to create a living appearance.
2. **Angry Tantrum**: Rapid clockwise/counter-clockwise snaps are triggered by the sound hub relative to audio triggers.
3. **Smooth Stops**: A **0.8s transition length** (firmware/production/node-1-dome-motion.yaml:155) is applied to prevent the dome from "jerking" when reaching the limit of the internal slip ring.


---


## Maintenance & Calibration

Regularly check the internal ring gear for debris and ensure the 3.5mm bullet connectors are secured.


- **Lubrication**: A light coating of lithium grease on the 3D-printed gears will reduce domestic noise.
- **Tension**: Ensure the 32mm grid mount remains torqued; a loose mount can cause "gear slip" during high-speed tantrums.
- **Slip Ring**: Check for "binding" in the central wires which can increase rotational resistance.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View Node Pinout Guide](../architecture/node-pinout-guide.md)
