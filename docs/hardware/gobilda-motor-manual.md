![manual-hero](../../assets/gobilda-5203-motor.webp)


# <i data-lucide="cog"></i> goBILDA Motor Manual

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: DOME MOTION** | **MODEL: YELLOW JACKET 5203**


The dome rotation for the Wee2-D2 project is managed by a high-torque planetary motor and a dedicated brushed PWM controller. This manual catalogs the physical configuration and logic integration for the dome drive.


---


## Motor Specifications (Hardware Focus)

The **Yellow Jacket 5203 Series** is a planetary gearmotor optimized for high-torque, low-speed applications. It is the primary driver for the droid's dome rotation.


| Parameter | Specification | Value |
| :--- | :--- | :--- |
| **Model** | 5203 Series (12V Hub) | Yellow Jacket |
| **Reduction** | 50.9:1 | Planetary Gearbox |
| **No-Load Speed** | 117 RPM | (12V Nominal) |
| **Stall Torque** | 22.0 kg-cm | High Output |
| **Output Shaft** | 6mm REX® | (Structural Profile) |


---


## Logic Integration: Node 1 (Dome Master)

Motor speed and direction are managed by **Node 1 (Dome Master)** on GPIO 7. The ESP32 logic provides a standard PWM signal to the brushed motor controller.


These settings are verified in the `v2.6.0-Dashboard` firmware sequence.


- **Master Node**: Node 1 (Dome Master / ESP32-S3)
- **GPIO Pin**: **GPIO 7** (firmware/production/node-1-dome-motion.yaml:11)
- **Protocol**: Standard PWM (50Hz)
- **PWM Range**: 1050μs (Counter-Clockwise) to 1950μs (Clockwise)
- **Deadzone**: 1500μs (Stationary)


---


## Physical Hookup & Wiring

The motor is connected to the brushed controller using standard bullet connectors. Power is supplied by a dedicated **Mini560 Pro** buck converter in the dome logic stack.


1. **Drive Connection**: 3.5mm Gold Bullet Connectors (Motor to Controller).
2. **Logic Power**: 5V Logic In (from Dome Wago Hub).
3. **Control Wire**: PWM Signal In (from Node 1 GPIO 7).
4. **Trunk Connection**: 20V Raw Trunk In (through Slip Ring C1/C2).


---


## Hardware Calibration

To ensure the dome behaves predictably during animations like "The Cantina Band," the gearing must be free of debris and correctly lubricated.


- **Gearing**: Check the drive gears for wear and ensure proper alignment.
- **Tension**: If the dome "stutters," verify that the Mini560 Pro logic buck is providing a steady 5V. voltage drops can cause the PWM signal to drift. 
- **Thermal Policy**: The 5203 series motor is capable of heavy duty-cycles, but the brushed controller may reach its thermal limit if stalled against a physical obstruction for >5 seconds.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View Power Architecture](../architecture/power-architecture.md)