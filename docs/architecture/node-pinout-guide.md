# <i data-lucide="cpu"></i> Master Node Pinout & Wiring Guide

This document serves as the master wiring reference for the Wee2-D2 distributed node mesh. It integrates all verified pin assignments, wire colors, and hardware interfaces for the ESP32 platforms.

---

## 1. Node 1: Sound Hub (ESP32-S3 Super Mini)

The **Sound Hub** manages behavioral audio triggers and drive system monitoring.

| ESP32 Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5.1V BEC (Primary Logic) |
| **GND** | Black | Ground | Common Logic Ground |
| **GPIO 4** | White | RC CH3 | Behavioral Trigger A |
| **GPIO 5** | Green | RC CH4 | Behavioral Trigger B |
| **GPIO 6** | Purple | RC CH5 | Bank Switch / Mode |
| **GPIO 17** | Yellow | DFPlayer TX | Serial Command Out |
| **GPIO 16** | Green | DFPlayer RX | Serial Status In (Optional) |
| **GPIO 47** | N/A | Status LED | Internal Neopixel (Logic) |

---

## 2. Node 2: LED Distribution (ESP32 Dev Board)

The **Lighting Controller** runs the WLED framework to drive high-density addressable matrices.

| ESP32 Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5.1V (Dedicated 10A Buck) |
| **GND** | Black | Ground | Common Logic Ground |
| **GPIO 18** | Yellow | Data Out | Front Logic (10x2) |
| **GPIO 19** | Yel/Blk | Data Out | Rear Logic (12x2) |
| **GPIO 21** | Green | Data Out | Front PSI Logic |
| **GPIO 22** | White | Data Out | Back PSI Logic |
| **GPIO 16** | Blue/Blk | UART RX | Serial Command In (Sync) |

---

## 3. Node 3: Dome Motion Master (ESP32-S3 Super Mini)

The **Motion Master** manages 360° dome rotation and broadcasts behavioral triggers via ESP-NOW.

| ESP32 Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5.1V BEC (from goBILDA ESC) |
| **GND** | Black | Ground | Common Logic Ground |
| **GPIO 4** | White | RC CH1 | Steering Input (PWM) |
| **GPIO 7** | Yellow | Dome ESC | PWM Command Out |
| **GPIO 47** | N/A | Status LED | Internal Neopixel (Logic) |

---

## 4. Hardware Interconnects

### Audio Stack (DFPlayer + TPA3118)

- **S3 TX (GPIO 17)** **DFPlayer RX**.
- **DFPlayer SPK_1/2** **TPA3118 Analog Input**.
- **TPA3118 Power** 20V Positive Fuse Box.
- **TPA3118 GND** **Star Ground** (-).

### Receiver Interface (HOTRC F-06A)

| Wire Color | Rec Slot | Node Pin | Role |
| :--- | :---: | :---: | :--- |
| **Red (5V)** | Slot 5 (+) | `5V / VIN` | Master Logic Power |
| **Black (GND)** | Slot 5 (-) | `GND` | Master Logic Ground |
| **Grey/Black** | Slot 3 (S) | `Node 1: GPIO 4` | CH1 Pulse Data |
| **Blue/Black** | Slot 4 (S) | `Node 1: GPIO 5` | CH2 Pulse Data |
| **Purple/Black**| Slot 5 (S) | `Node 1: GPIO 6` | CH3 Pulse Data |

---

## 5. Dome Distribution: Ganged Wagos

To handle the 15A+ peak loads, the slip ring circuits are ganged at the entry points.

### Positive 20V Wago (5-Port)

1. **IN**: Slip Ring Circuit 1 (20V)
1. **IN**: Slip Ring Circuit 2 (20V)
1. **OUT**: goBILDA 15A Speed Controller (+)
1. **OUT**: Mini560 Pro Buck (Logic Power)

### Negative GND Wago (5-Port)

1. **IN**: Slip Ring Circuit 3 (GND)
1. **IN**: Slip Ring Circuit 4 (GND)
1. **OUT**: goBILDA 15A Speed Controller (-)
1. **OUT**: Mini560 Pro Buck (GND)

---

[View Power Architecture](power-architecture.md)
gic.