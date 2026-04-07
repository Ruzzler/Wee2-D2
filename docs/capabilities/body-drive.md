# <i data-lucide="truck"></i> Body Drive System

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: BODY DRIVE** | **MODEL: DUAL FLD-5 HUB MOTORS**


This guide explains the drive mechanics for the Wee2-D2 project. It covers the hub motor specifications, VESC® configuration, and movement logic for the droid's primary body.


---


## Hardware Components (Hub Motors)

The project uses two **FLD-5 5" Hub Motors**. These are direct-drive motors that integrate the wheel and the motor into a single unit, reducing mechanical complexity.


- **Model**: FLD-5 (L-faster)
- **Voltage**: 24V-36V (Running at 20V Nominal)
- **Peak Current**: 30A (Software Clamped to **15A**)
- **Tire**: Solid Rubber (Anti-Skid)


---


## VESC® Motor Controller Configuration

The drive system is managed by two **Flipsky Mini FSESC 6.7 Pro** controllers. These are configured for **FOC (Field Oriented Control)** for smooth, quiet operation.


These settings are verified in the `v2.6.0-Dashboard` firmware sequence.


| Setting | Value | Function | Citation |
| :--- | :--- | :--- | :--- |
| **Motor Current Max** | **15.0 A** | Soft Current Clamp | [left-motor.xml](../../firmware/esc-configs/left-motor-settings.xml) |
| **Brake Current Max** | **15.0 A** | Aggressive Braking | [left-motor.xml](../../firmware/esc-configs/left-motor-settings.xml) |
| **Battery Cutoff Start** | **16.5 V** | Safety Voltage Floor | [left-motor.xml](../../firmware/esc-configs/left-motor-settings.xml) |
| **Battery Cutoff End** | **15.0 V** | Critical Minimum | [left-motor.xml](../../firmware/esc-configs/left-motor-settings.xml) |


---


## Drive Strategy & Movement Logic

The droid uses a **Differential Drive** model. Steering and acceleration are achieved by varying the speed and direction of the two hub motors.


1. **Acceleration Curves**: Acceleration is ramped to prevent "tipping" during sudden starts. This is managed by the ESP32 logic before the signal reaches the VESC.
2. **Torque Balancing**: The controllers are synced to ensure the droid drives straight on flat convention floors.
3. **Emergency Stop**: If the wireless bridge signal is lost for >100ms, the VESC enters a "Neutral" state to prevent runaway movement.


---


## Maintenance & Calibration

Regular calibration of the VESC hall sensors is required to maintain smooth low-speed performance.


- **Heat Management**: While the 15A clamp protects the electronics, extended driving on thick carpet can cause the FSESC to reach its thermal limit.
- **Tire Wear**: Ensure the solid rubber tires are free of debris to maintain traction on smooth floors.
- **Cable Management**: Check the 12AWG Phase Wires for any fraying near the internal axis.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View Power Architecture](../architecture/power-architecture.md)
