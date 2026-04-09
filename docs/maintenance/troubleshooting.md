# <i data-lucide="alert-triangle"></i> System Troubleshooting

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: FAULT DIAGNOSIS** | **MODEL: ALL NODES**


This guide provides a systematic strategy for identifying and fixing common issues with the Wee2-D2 project. It covers the node mesh, power distribution, and animation synchronization.


---


## Node Connectivity (ESP-NOW Mesh)

If the droid is not responding to dashboard triggers or sound triggers, the issue is likely within the radio mesh connection between Node 1 and Node 2.


- **No Sound**: Ensure that Node 2 (Sound Hub) is powered and within range. Node 1 sends a 1-byte trigger (firmware/production/node-1-dome-motion.yaml:230) that must be received over 2.4GHz.
- **Heartbeat Lost**: Nodes check for a mesh signal every 5 seconds (firmware/production/node-1-dome-motion.yaml:474). Check the Node 2 dashboard to see if Node 1 is marked "Offline."
- **EM Interference**: If the radio bridge is unstable, ensure that the Wi-Fi power output is capped at **8.5dBm** (firmware/production/node-1-dome-motion.yaml:56) to prevent noise within the aluminum dome.


---


## Power & Movement Faults

Movement issues are typically related to voltage sag or incorrect VESC configurations. This synchronization is verified in the `v2.6.0-Dashboard` firmware sequence.


1. **Voltage Shutdown**: If the system turns off during high-speed turns, the LVP module has likely triggered due to a voltage dip below **17.5V**. Swap for a fresh 20V battery.
2. **Motor Stutter**: Verify the **15A Software Clamp** settings in the VESC tool. If the clamp is too restrictive, the motors will fail to overcome friction on convention carpet.
3. **Internal Logic**: Ensure the 5V logic rails are stable. A flickering PSI logic display is often a sign of a failing Mini560 Pro buck converter.


---


## Diagnostic Log Access

You can view the real-time technical logs for each node using the built-in web server or the serial USB port.


- **Debug Level**: The current firmware is set to `DEBUG` for all core configurations (firmware/production/node-1-dome-motion.yaml:66).
- **RC Logging**: To see raw RC stick inputs, check the logs for the `pulse_width` sensor on Node 1 (GPIO 4).
- **Serial Monitor**: Use a baud rate of **115200** when connecting via USB (firmware/production/node-1-dome-motion.yaml:69).


---


## Common Issues Table

The following table summarizes the most frequent technical roadblocks discovered during convention testing.


| Symptom | Probable Cause | Recommended Fix |
| :--- | :---: | :--- |
| **No Logic LEDs** | Node 3 Serial Bus Jam | Reboot Node 1 (Dome Master) |
| **Loud Audio Hum** | Ground Loop Issue | Check the Negative Bus Bar star-ground |
| **Jerky Dome Rotation** | Servo Deadzone Drift | Re-calibrate Node 1 PWM levels |


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Calibration](calibration-guide.md)