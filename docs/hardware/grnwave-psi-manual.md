# <i data-lucide="activity"></i> GrnWave PSI Manual

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: CINEMATIC LIGHTING** | **MODEL: GRNWAVE PSI (ADDRESSABLE)**


The cinematic lighting for the Wee2-D2 project is powered by GrnWave addressable LED arrays. These units provide movie-accurate logic and PSI status visuals, managed by Node 3 (LED Distro) using the WLED framework.


---


## Hardware Specifications (Visual Focus)

The **GrnWave PSI** is a specialized addressable LED matrix. It is designed to physically fit within the 3.5" sensor ports of the aluminum dome assembly and provide high-fidelity visual output.


| Parameter | Specification | Value |
| :--- | :--- | :--- |
| **Model** | PSI Logic (Addressable) | WS2812B |
| **LED Count** | 48 (Matrix Layout) | High Density |
| **Voltage** | 5V DC (Logic Rail) | PWM |
| **Signal In** | DI (Data In) | WS2812B RMT |
| **Baud Rate** | ~800 KHz (RMT Protocol) | Node 3 Logic |


---


## Logic Integration: Node 3 (LED Distro)

The PSI lighting is managed by **Node 3 (LED Distro)**, which follows the RMT timing protocol for WS2812 signals. Node 3 receives serial JSON triggers from **Node 1 (Dome Master)** to sync visuals with audio.


These settings are verified in the `v2.6.0-Dashboard` hardware sequence.


- **Master Node**: Node 3 (LED Distro / ESP32 Dev Board)
- **Data Pin (Front)**: **GPIO 13** (WS2812B Output)
- **Data Pin (Rear)**: **GPIO 12** (WS2812B Output)
- **Framework**: WLED (v0.14+ / Serial Trigger Synced)
- **Sync Prot**: [UART Sync Guide](../capabilities/led-system.md)


---


## Physical Hookup & Wiring

The PSI arrays are connected to the central **Dome LED Rail** via mandatory JST-XH connectors. Power is supplied by a dedicated **Mini560 Pro** buck converter in the dome.


1. **Data In (DI)**: From Node 3 GPIO 13/12.
2. **5V Logic**: From the Dome LED Wago Hub.
3. **Common Ground**: Shared Common Negative trunk with Node 3 and Node 1.
4. **Resistor**: A **470 Ohm Resistor** is recommended on the Data line to prevent signal spikes.


---


## Hardware Calibration

To ensure the PSI logic follows the 1977 movie-accurate timing, the WLED segments must be correctly mapped to the hardware indices.


- **Color Correction**: Adjust the RGB order to `GRB` in the WLED global settings.
- **Segment Sync**: Map the Front PSI to Segment 0 and the Rear PSI to Segment 1 in the `node-3-segments.json` config.
- **Thermal Policy**: Although addressable LEDs are efficient, full-brightness "All White" patterns can reach high temperatures. Ensure the dome logic stack has adequate ventilation.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View LED System Guide](../capabilities/led-system.md)