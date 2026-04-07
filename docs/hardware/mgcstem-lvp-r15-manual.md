# <i data-lucide="battery-charging"></i> LVP Protection Manual

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: POWER PROTECTION** | **MODEL: MGCSTEM LVP-R1.5**


The power grid for the Wee2-D2 project is protected by a MgcSTEM Low Voltage Protection (LVP-R1.5) module. This unit monitors the 20V DeWalt trunk and prevents deep discharge of the Lithium-Ion battery cells.


---


## Hardware Specifications (Safety Focus)

The **MgcSTEM LVP-R1.5** is an adjustable voltage relay module. It is the primary safety-cutoff for the droid's high-current power trunk.


| Parameter | Specification | Value |
| :--- | :--- | :--- |
| **Model** | LVP-R1.5 (Adjustable) | Power Grid |
| **Cutoff Voltage** | **17.5V (Safety Floor)** | Battery Protection |
| **Hysteresis** | 1.0V (Recovery) | Standard |
| **Max Current** | 30A (Peak) / 20A (Sustained) | Trunk Protection |
| **Voltage Range** | 6V–60V (Input) | DeWalt 20V System |


---


## Logic Integration: Power Grid

The LVP module is physically located between the DeWalt battery and the primary **Negative Bus Bar**. It acts as a hard-wired E-Stop for the power system.


These settings are verified in the `v2.6.0` hardware stack.


- **Cutoff Accuracy**: ±0.1V Calibration.
- **Recovery Strategy**: The system will automatically reconnect if the battery voltage rises above **18.5V**, though a fresh battery swap is required for reliable operation.
- **System Protection**: [Power Architecture](../architecture/power-architecture.md)
- **Monitoring**: [Battery Runtime Guide](../maintenance/battery-runtime-guide.md)


---


## Physical Hookup & Wiring

The LVP module is connected to the primary 20V trunk using 12AWG high-current silicone wires and XT60 connectors.


1. **Voltage In (VCC/GND)**: From the DeWalt Battery Mount.
2. **Voltage Out (OUT+/OUT-)**: To the central Negative Bus Bar and Ganged Trunk.
3. **Common Ground**: Shared ground system with the VESC motor controllers.


---


## Hardware Calibration

To ensure the LVP system triggers correctly under the heavy torque loads of the FLD-5 hub motors, the potentiometer must be precisely tuned.


- **Voltage Sag**: Under high-current draw (30A peak), the battery will experience a "sag" of ~1.5V. The 17.5V cutoff is calibrated to account for this instantaneous dip.
- **Verification**: Regularly check the cutoff point using a variable DC power supply. 
- **Thermal Policy**: Although the LVP is efficient, ensure it is mounted away from the secondary buck converters to prevent cumulative heat buildup in the body's electronics bay.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View Power Architecture](../architecture/power-architecture.md)