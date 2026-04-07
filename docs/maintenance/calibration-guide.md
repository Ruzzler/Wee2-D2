# <i data-lucide="wrench"></i> System Calibration Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: CALIBRATION & TUNING** | **MODEL: ALL NODES**


This guide explains how to calibrate the drive, dome, and sound systems for the Wee2-D2 project. Proper calibration ensures that the droid remains stable and responsive during autonomous movement.


---


## Drive System Calibration (VESC)

To ensure the droid drives straight and handles torque correctly, a full hall-sensor calibration must be performed using the VESC Tool. This synchronization is verified in the `v2.6.0-Dashboard` firmware sequence.


1. **Hall Sensor Detection**: Connect the Flipsky 6.7 Pro to the VESC Tool. Run the "Motor Setup Wizard" to detect the Hall sensor table for the FLD-5 hub motors.
2. **Current Limits**: Verify that the **15A Software Clamp** is applied to prevent battery sag (firmware/esc-configs/left-motor-settings.xml).
3. **Neutral Deadzone**: Calibrate the PPM signal to ensure a 1500μs center-point for stationary operation.


---


## Dome Rotation Calibration (Node 1)

The dome motor is a brushed PWM system. Calibration is handled by adjusting the pulse-width levels in the **Node 1 (Dome Master)** configuration.


- **Center Point**: 1500μs (firmware/production/node-1-dome-motion.yaml:153)
- **Range (CW)**: 1950μs Max Speed
- **Range (CCW)**: 1050μs Max Speed
- **Transition**: Adjust the `transition_length` for smooth start/stop behavior.


---


## RC Stick Input Tuning

The RC receiver (HotRC DS-600) provides raw PWM signals to GPIO 4 on Node 1. Tuning these filters prevents jitter during stationary operation.


- **Deadzone Filter**: 20.0 (firmware/production/node-1-dome-motion.yaml:168)
- **Signal Delta**: 20.0μs
- **Multiplier**: 1000000 (Pulse Width Calculation)


---


## Audio & Visual Sync

Ensure that the **UART baud rate** for the sound hub matches the lighting distro to prevent lag during cinematic animations.


- **Sound Hub (Node 2)**: 9600 Baud (UART Link)
- **LED Distro (Node 3)**: 115200 Baud (UART Link)


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Troubleshooting](troubleshooting.md)