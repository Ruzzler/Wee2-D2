# 🧵 Master Wiring Guide: Body Controller (MCU 1)

This document serves as the master wiring reference for the Wee2-D2 Body Controller (ESP32-S3). It integrates all verified wire colors, pin assignments, and physical orientation for the S3 Super Mini platform.

---

## 🧠 1. Core MCU Pinout (S3 Super Mini)
The Body Controller manages all high-level Audio triggering and Drive system monitoring. The pins follow the standard S3 Super Mini layout.

| ESP32 Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | 🟥 Red | Power In | 5V BEC (from ESC 1) |
| **GND** | 🟩 Green | Ground | Common Logic Ground |
| **GPIO 4** | ⬜ White | RC CH3 | Behavioral Trigger A |
| **GPIO 5** | 🟩 Green | RC CH4 | Behavioral Trigger B |
| **GPIO 6** | 🟪 Purple | RC CH5 | Bank Switch |
| **GPIO 17** | 🟨 Yellow | DFPlayer TX | Serial Command Out |
| **GPIO 16** | 🟩 Green | DFPlayer RX | Serial Status In (Optional) |
| **GPIO 47** | N/A | Status LED | Internal Neopixel (Logic) |

---

## 🔊 2. Audio Stack (DFPlayer + TPA3118)
Audio triggers are processed via Node 1 and sent to the DFPlayer Mini. The analog signal is then amplified via the TPA3118.

### **DFPlayer Mini Interface**
- **VCC/GND**: Connected to 5V Logic Rail.
- **TX/RX**: Connected to S3 GPIO 16/17 (Crossed: TX -> RX).
- **SPK_1/SPK_2**: Connected to **TPA3118 Input**.

### **TPA3118 Amplifier**
- **POWER**: Connected to 20V Positive Fuse Box (+).
- **GND**: Connected to **Star Ground** (-).
- **INPUT**: Connected to DFPlayer SPK_1/SPK_2 or DAC pads.
- **OUTPUT**: Connected to Pyle 3.5" Speaker.

---

## 📡 3. Receiver Interface (F-06A)
The receiver is powered directly via the **Slot 5** bridge.

| Wire Color | Rec Slot | ESP Pin | Role |
| :--- | :---: | :---: | :--- |
| **Red (5V)** | Slot 5 (+) | `VIN` | Master Logic Power |
| **Black (GND)** | Slot 5 (-) | `GND` | Master Logic Ground |
| **Grey/Black** | Slot 3 (S) | `GPIO 25` | CH3 Pulse Data |
| **Blue/Black** | Slot 4 (S) | `GPIO 33` | CH4 Pulse Data |
| **Purple/Black**| Slot 5 (S) | `GPIO 32` | CH5 Pulse Data |

---

## 🛞 4. Drive System: Parallel ESC Wiring (No CAN)
Because the remote is in **Mode 1 (Mixed)**, each ESC needs its own logic pulse. We use the "High-Fidelity Signal" method to ensure smooth steering at high currents.

| Source | Connection | ESC 1 (Left) | ESC 2 (Right) |
| :--- | :--- | :---: | :---: |
| **Receiver CH1** | Signal (White) | **CONNECT** | — |
| **Receiver CH2** | Signal (White) | — | **CONNECT** |
| **BEC Power** | Red (5V) | **CONNECT** | **ISOLATE (Red)** |
| **Signal Reference**| Black (GND) | **CONNECT** | **CONNECT (Black)** |

> [!IMPORTANT]
> **Signal Jitter Prevention**: While the main power ground goes to the bus bar, keeping the small Black ground wire on ESC 2 provides a clean reference for the PWM signal, preventing "twitches" caused by motor noise.

---

## 🛰️ 5. Dome Distribution: Ganged Wago Hub
To handle the 15A+ peak loads of the dome motor and LED matrices, the slip ring circuits must be ganged at the entry Wagos.

### **Positive 20V Hub (Wago A - 5 Port)**
1. **IN**: Slip Ring Circuit 1 (20V)
2. **IN**: Slip Ring Circuit 2 (20V) - **GANGED**
3. **OUT**: goBILDA 15A Speed Controller (+)
4. **OUT**: Mini560 Pro Buck 1 (LED Power)
5. **OUT**: Mini560 Pro Buck 2 (Logic Power)

### **GND Star Hub (Wago B - 5 Port)**
1. **IN**: Slip Ring Circuit 3 (GND)
2. **IN**: Slip Ring Circuit 4 (GND) - **GANGED**
3. **OUT**: goBILDA 15A Speed Controller (-)
4. **OUT**: Mini560 Pro Buck 1 (GND)
5. **OUT**: Mini560 Pro Buck 2 (GND)

---

## 🛠️ 5. Wireless Interconnect (ESP-NOW)
*Note: Node 1 (Body) is a wireless slave. It contains NO physical signal wires through the slip ring.*

| Circuit | Role | Logic | Notes |
| :---: | :--- | :--- | :--- |
| **Wireless** | **ESP-NOW** | 2.4GHz | Behavioral sync from Dome Master |
| **C5/C6** | **RESERVED** | N/A | Available for future logic / telemetry |

---

## ⚡ 7. Dome ESC Pulse Calibration (goBILDA 15A)
*   **Signal (White)**: Connect to **MCU 3 (GPIO 18)**.
*   **Ground (Black)**: **MUST** be connected to the Dome Logic GND rail (Reference).
*   **Voltage (Red)**: **ISOLATE** (Do not connect) if using the Slip Ring 5V Logic Bus.

---

## 📊 6. Summary Check
- [x] Body MCU upgraded to **ESP32-S3 Super Mini**.
- [x] **DFPlayer Mini** integrated as the primary audio source.
- [x] **TPA3118 Amplifier** powered directly from 20V rail.
- [x] **ESP-NOW** established as the wireless behavioral link.
- [x] **Slip Ring C5/C6** isolated and reserved for future logic.
