# <i data-lucide="cpu"></i> Node Pinout & Wiring Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: PINOUT & WIRING** | **MODEL: ESP32-S3 / ESP32**


This guide lists the physical wiring and GPIO assignments for every microcontroller node in the Wee2-D2 project. These connections are verified for the `v2.6.0-Dashboard` firmware sequence.


---


## Node 1: Dome Master (ESP32-S3)

The Dome Master manages dome rotation, RC inputs, and logic communication. It is powered by a dedicated 5V buck converter in the dome.


| Assignment | GPIO Pin | Function | Citation |
| :--- | :--- | :--- | :--- |
| **Dome Motor (PWM)** | **GPIO 7** | Output to 15A Servo ESC | [node-1.yaml:11](../../firmware/production/node-1-dome-motion.yaml#L11) |
| **RC Stick (X-Axis)** | **GPIO 4** | Input from HotRC Receiver | [node-1.yaml:12](../../firmware/production/node-1-dome-motion.yaml#L12) |
| **WLED Data (TX)** | **GPIO 5** | Serial Out to Node 3 | [node-1.yaml:13](../../firmware/production/node-1-dome-motion.yaml#L13) |
| **UART Heartbeat** | **TX0** | Hardware Serial Logging | [node-1.yaml:68](../../firmware/production/node-1-dome-motion.yaml#L68) |


---


## Node 2: Sound Hub (ESP32-S3)

The Sound Hub manages the DFPlayer Mini and hosts the Web Dashboard. It receives radio triggers from Node 1.


| Assignment | GPIO Pin | Function | Protocol |
| :--- | :--- | :--- | :--- |
| **DFPlayer TX** | **GPIO 43** | Serial Out to MP3 Player | UART (9600) |
| **DFPlayer RX** | **GPIO 44** | Serial In (Diagnostics) | UART (9600) |
| **Status LED** | **GPIO 15** | Onboard NeoPixel (Optional) | WS2812B |


---


## Node 3: LED Distro (ESP32 Dev V1)

Node 3 is a dedicated WLED controller that handles all addressable visuals. It follows the RMT timing protocol for WS2812 signals.


| Assignment | GPIO Pin | Function | Specification |
| :--- | :--- | :--- | :--- |
| **Logic Display** | **GPIO 13** | Main LED Matrix Array | WS2812B (RMT) |
| **PSI Lights** | **GPIO 12** | Front/Rear PSI Status | WS2812B (RMT) |
| **Sync Data (RX)** | **GPIO 3** | Serial In from Node 1 | UART (115200) |


---


## Standard Wiring Colors

Follow the project color code to prevent ground loops or reverse-polarity events in the dome logic stack.


- **Red (18AWG)**: 20V Raw Trunk (Battery)
- **Orange (20AWG)**: 5V Regulated (Logic Rail)
- **Black (18AWG)**: Common Negative (GND)
- **Blue (24AWG)**: Serial Data (Nodes 1 to 3)
- **White (24AWG)**: PWM PWM Signals (Node 1 to Dome ESC)


---


[View Master Schematic](electrical-schematic.md) | [View Power Architecture](power-architecture.md)