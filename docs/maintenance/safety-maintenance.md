# <i data-lucide="shield-check"></i> Safety & Maintenance

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: SAFETY & UPKEEP** | **MODEL: ALL COMPONENTS**


This guide lists the mandatory safety and maintenance procedures for the Wee2-D2 project. Proper upkeep is required to prevent electrical fires, gear damage, and motor failures during long convention deployments.


---


## Electrical Safety (Power Trunk)

The droid's power source is a high-current 20V Lithium-Ion battery. The electrical trunk must be inspected regularly to ensure all connections are tight and free of thermal damage.


1. **Voltage Range**: The DeWalt battery system operates at **20V (18.5V Nom)**. Ensure the MgcSTEM LVP module is set to a **17.5V safety cutoff** (firmware/production/node-1-dome-motion.yaml:425).
2. **Terminal Inspection**: Check the central Negative Bus Bar and Wago hubs for loose wires. High-current loads (30A peak) from the FLD-5 motors can cause localized heat if a terminal is loose.
3. **Emergency Shutdown**: If you smell "burning" or see smoke, immediately pull the battery from the body mount. The system does not have a software e-stop for electrical short-circuits.


---


## Drive & Mechanical Upkeep

Hub motors and domestic gears are subject to mechanical wear and require regular inspection before each deployment.


| Component | Frequency | Action | Citation |
| :--- | :--- | :--- | :--- |
| **Hub Motors** | Daily | Check M8 axle nuts for torque | [Drive Guide](../capabilities/body-drive.md) |
| **Dome Ring Gear**| Monthly | Lubricate with lithium grease | [Motion Guide](../capabilities/dome-rotation.md) |
| **Slip Ring** | Monthly | Check for physical wire fatigue | [Power Guide](../architecture/power-architecture.md) |


---


## Firmware & Software Stability

The droid relies on three ESP32 nodes to function. These nodes should be running the verified `v2.6.0-Dashboard` firmware sequence.


- **OTA Updates**: Only perform Over-The-Air updates when the battery is at >50% charge to prevent brownouts during the write cycle.
- **Mesh Integrity**: If the droid behaves erratically, reboot Node 1 (Dome Master) to re-establish the ESP-NOW handshake (firmware/production/node-1-dome-motion.yaml:474).
- **Log Review**: Use the `wee2d2-dome-master.local` web dashboard to check for recurring technical errors in the system logs.


---


## Con-Floor Best Practices

When operating the droid in a public space, follow these safety standards to avoid accidents or hardware failures.


- **Carpeting**: Driving on thick convention carpet increases the current draw for the hub motors. Monitor battery sag frequently.
- **Battery Swap**: Swap the battery at **18.2V** to ensure the droid has enough reserve power for a safe, controlled motor shutdown. 
- **Crowds**: Use the dashboard's "Speed Slider" to cap movement at 40% when in high-density areas. 


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Troubleshooting](troubleshooting.md)