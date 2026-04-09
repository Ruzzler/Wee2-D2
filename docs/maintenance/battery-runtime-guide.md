# <i data-lucide="battery"></i> Battery Runtime & Power Estimates

> **POWER MANAGEMENT** | **SYSTEM: DEWALT 20V (4Ah/6Ah/9Ah)** | **LVP: 17.5V**


This guide provides high-fidelity power estimates for the Wee2-D2 project. It factors in resistive line losses (I2R) and RF mesh drainage across the distributed node network (firmware/production/node-1-dome-motion.yaml:478).


---


## Energy Capacity (Real-World Usable)

The 20V DeWalt battery system operates at **18.5V Nominal**. While raw Watt-Hour (Wh) ratings are calculated at the cell level, the **MgcSTEM LVP-R1.5** cutoff at **17.5V** creates a safety buffer, reducing the usable energy reservoir to protect the Li-ion chemistry.


| Pack Size | Raw Energy (18.5V Nom) | Usable Energy (17.5V LVP) | Sector Duty (Patrol) |
| :--- | :---: | :---: | :--- |
| **4Ah (Standard)** | 74Wh | **~60Wh** | Short Deployment |
| **6Ah (FlexVolt)** | 111Wh | **~94Wh** | Full Day Usage |
| **9Ah (FlexVolt)** | 166Wh | **~142Wh** | Full Day Usage |


---


## Power Consumption Breakdown (Deep-Audit)

These recalibrated calculations factor in resistive losses and active logic mesh drainage observed in the `v2.6.0-Dashboard` firmware sequence.


### 1. Baseline (Always-On Signal & Logic)

This represents the "Stationary" draw when the droid is on and the mesh is active.
- **RF Mesh Logic**: 3x ESP32 nodes (Nodes 1, 2, 3) + RC Receivers. Sustained Wi-Fi/ESP-NOW active draw. (**5.5W**)
- **Cinematic Patterns**: Front/Rear Logics + Circular PSIs at 40% Global Brightness (Mixed pattern). (**18.0W**)
- **Conversion & Line Loss**: Cumulative Mini560 Pro buck efficiency (90%) + I2R resistive loss through the slip ring. (**15% Overhead**)
- **Total Baseline Average**: **~28.0 Watts**


### 2. Audio System (Chatter & Processing)

The sound hub acts as the primary relay for animation audio triggers.
- **System**: DFPlayer Mini + TPA3118 Amplifier + Pyle 3.5" Driver.
- **Duty Cycle**: Variable (Chatter every 15–30s).
- **Average Load**: **~2.5 Watts**


### 3. Drive System (VESC Kinetic Peaks)

Recalibrated requirements based on your specific **15A Software Clamp** ($30A$ total battery draw).
- **Current Limit Max**: 70A. (Software Clamped to **15A** for Wee2-D2 in `left-motor-settings.xml`).
- **Voltage Cutoff**: Start at 16.5V for DeWalt batteries.
- **Verified Configs**: [Motor Settings](../../firmware/esc-configs/left-motor-settings.xml) | [App Settings](../../firmware/esc-configs/left-app-settings.xml)
- **Kinetic Peak Acceleration**: Instantaneous high-torque maneuvers. (**600W Peak / 30A**)
- **Active Drive**: High-torque movement on level convention surfaces (40% Duty Cycle). (**~21.0W Avg**)
- **The "7.5C" Sag Factor**: Pulling 30A from a 4Ah battery induces a **~2.5V dip**, triggering the 17.5V LVP cutoff even when at **50% charge**.
- **Total Motion Average**: **~23.5 Watts**


---


## Operational Estimates: Runtime Windows

The following windows represent the **Active Deployment Time** remaining before the LVP system triggers an emergency shutdown. 


| Mode | Total Avg Load | 4Ah Runtime | 6Ah Runtime | 9Ah Runtime |
| :--- | :---: | :---: | :---: | :---: |
| **Active Patrol** (Moving/Beeping/Lights) | **54.0 Watts** | **~65 Min** | **~105 Min** | **~160 Min** |
| **Booth Guard** (Static/Beeping/Lights) | **30.5 Watts** | **~115 Min** | **~185 Min** | **~280 Min** |
| **Stealth Deck** (Logic Mesh Only) | **5.5 Watts** | **~11 Hours** | **~17 Hours** | **~25 Hours** |


---


## Tactical Power Advisories

### 1. The "Voltage Sag" Threshold
When the battery is below 30% Charge (approx. 18.2V), heavy torque commands to the hub motors can cause a temporary **Voltage Sag** that dips below the 17.5V LVP floor. This will trigger a sudden system shutdown even if the battery has remaining capacity. 

> [!TIP]
> **CON-FLOOR STRATEGY**: When at low SOC, reduce drive speed and dome rotation frequency to extend your operational window.


### 2. Trunk Thermal Management
The 20V power trunk passing through the **CNBTR Slip Ring** carries the full current for the Dome Logic, LED, and Dome Motor bucks. Under full cinematic sequences, this trunk can dissipate significant heat.
- **Cooling**: Ensure the dome's internal Mini560 Pro logic buck has adequate ventilation. 
- **Isolation**: Keep high-current LED wiring isolated from Node 1 RX signal wires to prevent induction noise.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View BOM](../bill-of-materials.md)