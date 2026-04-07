# <i data-lucide="cpu"></i> Master Node Pinout & Wiring Guide

This guide is the main wiring reference for the Wee2-D2 distributed node mesh. It includes all verified pin assignments, wire colors, and hardware interfaces for the ESP32 platforms.


---


## 1. Node 1: Dome Motion Master (ESP32-S3 Super Mini)

The **Motion Master** manages 360° dome rotation and broadcasts behavioral triggers via ESP-NOW.

| ESP32 Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5.0V (Mini560 Pro 5A) |
| **GND** | Black | Ground | Common Logic Ground |
| **GPIO 4** | White | RC CH1 | Steering Input (PWM) |
| **GPIO 5** | Blue | WLED Sync | Single Wire UART TX |
| **GPIO 7** | Yellow | Dome ESC | PWM Command Out |
| **GPIO 47** | N/A | Status LED | Internal Neopixel (Logic) |


---


## 2. Node 2: Sound Hub (ESP32-S3 Super Mini)

The **Sound Hub** manages behavioral audio triggers and drive system monitoring.

| ESP32 Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5.0V (Mini560 Buck) |
| **GND** | Black | Ground | Common Logic Ground |
| **GPIO 12** | Yellow | DFPlayer TX | Serial Command Out |
| **GPIO 13** | Green | DFPlayer RX | Serial Status In (Optional) |
| **GPIO 47** | N/A | Status LED | Internal Neopixel (Logic) |


---


## 3. Node 3: LED Distribution (ESP32 Dev Board)

The **Lighting Controller** runs the **Native WLED (v0.14+)** framework to drive high-density addressable matrices.

| ESP32 Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5.0V (Mini560 Buck) |
| **GND** | Black | Ground | Common Logic Ground |
| **GPIO 16** | Yellow/Blk | UART RX | Serial Sync In (from Node 1) |
| **GPIO 17** | Green/Blk | UART TX | Serial Sync Out (Optional) |
| **GPIO 18** | Yellow | Data Out | Front Logic (10x2) |
| **GPIO 19** | Yel/Blk | Data Out | Rear Logic (12x2) |
| **GPIO 21** | Green | Data Out | Front PSI (GrnWave) |
| **GPIO 22** | White | Data Out | Rear PSI (GrnWave) |


---


## 4. Hardware Interconnects

### Audio Stack (DFPlayer + TPA3118)

- **Node 2 TX (GPIO 12)** --> **DFPlayer RX**.
- **DFPlayer DAC_R / DAC_L** --> **TPA3118 Analog Input** (High Fidelity).
- **TPA3118 Power** 20V Positive Fuse Box.
- **TPA3118 GND** **Star Ground** (-).


### Receiver Interface (HOTRC F-06A)

| Wire Color | Rec Slot | Node Pin | Role |
| :--- | :---: | :---: | :--- |
| **Red (5V)** | Slot 5 (+) | `5V / VIN` | Master Logic Power |
| **Black (GND)** | Slot 5 (-) | `GND` | Master Logic Ground |
| **Grey/Black** | Slot 3 (S) | `Node 1: GPIO 4` | CH1 (Dome Rotation) |


---


## 5. Dome Distribution: Power Hubs

To handle peak loads and ensure stable logic voltage, the dome uses two ganged Wago hubs, each consisting of **2x 5-port connectors** (Dedicated Positive and Negative rails).


### 20V High-Power Hub (2x 5-Port Wago)

1. **IN**: Slip Ring Circuit 1 (20V)
2. **IN**: Slip Ring Circuit 2 (20V)
3. **OUT**: goBILDA 15A Speed Controller
4. **OUT**: Mini560 Pro (5A) - **Logic Rail**
5. **OUT**: Mini560 Pro (5A) - **LED Rail**


### 5V Logic Hub (2x 5-Port Wago)

1. **IN**: Mini560 Pro (Logic Rail)
2. **OUT**: Node 1 (Dome Master)
3. **OUT**: Node 3 (LED Distribution)
4. **OUT**: HOTRC F-06A Receiver
5. **OUT**: Reserved / Expansion


---


[View Power Architecture](power-architecture.md)