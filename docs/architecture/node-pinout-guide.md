![manual-hero](../../assets/esp32-s3-super-mini.jpg)


# <i data-lucide="cpu"></i> Node Pinout & Wiring Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: DISTRIBUTED MESH** | **VERSION: v2.6.0-STABLE**


This guide provides a comprehensive technical reference for the distributed microcontroller nodes. It documents every GPIO mapping, physical wiring slot, and logic-bus role for the ESP32-S3 and ESP32 hardware.


---


## Node 1: Dome Motion Master (ESP32-S3)

Node 1 is the primary behavioral controller. It reads RC steering and manages the high-torque goBILDA rotation system.

### 📊 Pinout Table (GPIO)
| Pin | Function | Role | Target Component |
| :--- | :--- | :---: | :--- |
| **GPIO 7** | **PWM Out** | Signal 1 | Dome ESC (White Wire) |
| **GPIO 3** | **UART TX** | Logic Bus | To Node 3 (Lighting) |
| **GPIO 4** | **UART RX** | Logic Bus | From Node 3 (Logic) |
| **GPIO 38** | **ESP-NOW** | Sync | Mesh Heartbeat |
| **GPIO 43** | **TX (Debug)** | UART | PC Monitoring |
| **GPIO 44** | **RX (Debug)** | UART | PC Monitoring |
| **5V** | **Vin** | Power | Buck 2 Output |
| **GND** | **GND** | Ref | Star Ground |


---


## Node 2: Sound Hub & Gateway (ESP32-S3)

Node 2 hosts the interactive dashboard and initiates all behavioral audio triggers via the DFPlayer Mini.

### 📊 Pinout Table (GPIO)
| Pin | Function | Role | Target Component |
| :--- | :--- | :---: | :--- |
| **GPIO 1** | **UART TX** | Audio Bus | DFPlayer Mini (RX) |
| **GPIO 2** | **UART RX** | Audio Bus | DFPlayer Mini (TX) |
| **GPIO 9** | **I2C SDA** | Sensors | Future LiDAR Expansion |
| **GPIO 10** | **I2C SCL** | Sensors | Future LiDAR Expansion |
| **GPIO 18** | **ESP-NOW** | Sync | Mesh Heartbeat |
| **5V** | **Vin** | Power | Buck 1 Output |
| **GND** | **GND** | Ref | Star Ground |


---


## Node 3: Lighting Distribution (ESP32)

Node 3 is a dedicated visual hub running WLED. It is physically synced to Node 1 via the Dome Logic Bus.

### 📊 Pinout Table (GPIO)
| Pin | Function | Role | Target Component |
| :--- | :--- | :---: | :--- |
| **GPIO 2** | **Data Out** | WLED 1 | Front PSI Logic |
| **GPIO 4** | **Data Out** | WLED 2 | Rear PSI Logic |
| **GPIO 5** | **Data Out** | WLED 3 | Logic Display (Matrix) |
| **GPIO 16** | **UART RX** | Logic Bus | From Node 1 (Dome Master) |
| **5V** | **Vin** | Power | Buck 3 Output |
| **GND** | **GND** | Ref | Star Ground |


---


## Physical Interconnect Standards

- **Logic Grounding**: Every node ground must terminate at the central **Negative Bus Bar** to ensure clean signal resolution for ESP-NOW and UART.
- **UART Isolation**: Use 100-ohm series resistors on long UART runs (Body to Dome) to prevent ringing and EMI interference from motors.


---


[View Interactive Schematic](electrical-schematic.md) | [View Power Architecture](power-architecture.md)