# <i data-lucide="shopping-cart"></i> Bill of Materials

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: HARDWARE PROCUREMENT** | **BOM v2.6.0**


This document catalogs the verified hardware stack for the Wee2-D2 project. All components are selected for architectural parity with the `v2.6.0-Dashboard` firmware sequence.


---


## Microcontroller Nodes

The droid uses a distributed mesh of ESP32-S3 and standard ESP32 boards (firmware/production/node-1-dome-motion.yaml:34) to handle parallel animations.


| Channel | Component | Quantity | Role |
| :--- | :--- | :---: | :--- |
| **Node 1** | ESP32-S3 Super Mini | 1 | Dome Motion Master / RC Bridge |
| **Node 2** | ESP32-S3 Super Mini | 1 | Sound Hub / Dashboard Gateway |
| **Node 3** | ESP32D DevKit | 1 | LED Distribution / WLED Core |
| **Interface** | CP2102 Serial Adapter | 1 | Wired firmware deployment |


---


## Drive & Motion Hardware

Movement is handled by a combination of high-torque hub motors and a precision planetary dome drive (firmware/production/node-1-dome-motion.yaml:11).


| Category | Component | Quantity | Specification |
| :--- | :--- | :---: | :--- |
| **Dome Motor** | goBILDA 5203 Motor | 1 | 117 RPM (12V Hub) Yellow Jacket |
| **Dome ESC** | goBILDA 1x15A | 1 | Brushed PWM Controller (30V Max) |
| **Body Drive** | FLD-5 Hub Motor | 2 | 5" Direct Drive / 24V-36V |
| **Body ESC** | Flipsky 6.7 Pro | 2 | VESC® Compatible / 70A Peak |


---


## Power & Regulation

The power management system relies on high-efficiency buck converters to stabilize the 20V DeWalt trunk for logic-level circuitry.


| Circuit | Component | Quantity | Specification |
| :--- | :--- | :---: | :--- |
| **Main Power** | DeWalt 20V Battery | 1 | 4Ah / 6Ah / 9Ah Lithium Ion |
| **Protection** | MgcSTEM LVP-R1.5 | 1 | 17.5V Adjustable Low Voltage Cutoff |
| **Regulation** | Mini560 Pro | 3 | 5A High-Efficiency Buck (5V Fixed) |
| **Bus Dist.** | 5-Port Wago Hub | 2 | Dome Logic / Body Logic Rails |


---


## Audio & Visual Stack

Cinematic output is managed through specialized LED arrays and a high-fidelity 60W audio hub.


| Category | Component | Quantity | Specification |
| :--- | :--- | :---: | :--- |
| **Audio Hub** | DFPlayer Mini | 1 | MP3-TF-16P (9600 Baud UART) |
| **Amplifier** | TPA3118 60W | 1 | Mono Class-D (PBTL Mode) |
| **Speaker** | Pyle 3.5" Driver | 1 | 60W RMS / 4 Ohm Performance |
| **LED Logic** | GrnWave PSI/Logics | 3 | Addressable WS2812B Arrays |
| **Radio TX** | HotRC DS-600 | 1 | 6-Channel 2.4GHz Transmitter |
| **Radio RX** | HotRC F-06A | 2 | 6-Channel PWM Receivers |


---


## Mechanical & Structural

The chassis and joint systems bridge the gap between the 3D-printed exterior and the industrial internal grid.


| Component | Category | Quantity | Role |
| :--- | :--- | :---: | :--- |
| **3D Chassis** | Mr. Baddeley Files | 1 | Acclaimed 3D files (Big Baby) |
| **Slip Ring** | CNBTR 6-Circuit | 1 | 20A Ganged Power Trunk (Central) |


---


[View Master Schematic](architecture/electrical-schematic.md) | [View Node Pinout Guide](architecture/node-pinout-guide.md)