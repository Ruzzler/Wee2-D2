# 🧵 Master Wiring Guide: Body Controller (MCU 1)

This document serves as the "Imperial Standard" for the Wee2-D2 Body Controller (ESP32D). It integrates all verified wire colors, pin assignments, and physical orientation for the **38-pin variant**.

---

## 🧠 1. Core MCU Pinout (38-pin Rails)
The Body Controller manages all high-level RC interpretation and audio dispatching. The pins below follow the order printed on the board rail (starting from the USB side).

| Physical Label | ESP32 Pin | Wire Color | Function |
| :--- | :---: | :--- | :--- |
| **VIN** | `5V` | 🟥 Red | 5V Power In (from ESC) |
| **GND** | `GND` | 🟩 Green | Common Logic Ground |
| **D13** | `GPIO 13` | — | (Empty) |
| **D12** | `GPIO 12` | — | (Strapping Pin - Keep Clear) |
| **D14** | `GPIO 14` | — | (Empty) |
| **D27** | `GPIO 27` | ⬜ White | **Sound S4 (Scream)** |
| **D26** | `GPIO 26` | ⬛ Black | **Sound S3 (Alert)** |
| **RC CH3 Input** | D25 | GPIO25 | Trigger A (Grey/Blk) |
| **RC CH4 Input** | D33 | GPIO33 | Trigger B (Blue/Blk) |
| **RC CH5 Input** | D32 | GPIO32 | Bank Switch (Purple/Blk) |
| **Drive CH1** (Left) | ESC 1 | PPM | 3-Wire (Full Power/Gnd) |
| **Drive CH2** (Right)| ESC 2 | PPM | **2-Wire** (Signal/Gnd Only) |
| **Sound S1-S9** | D4, D5... | 4,5,26,27,18,19,21,22,23 | **Active LOW** Trigger Pins |
| **D35** | `GPIO 35` | — | (Empty) |
| **D34** | `GPIO 34` | — | (Empty) |
| **VN** | `GPIO 39` | — | (Empty) |
| **VP** | `GPIO 36` | — | (Empty) |
| **EN** | `EN` | — | (Reset Button) |

---

## 🔊 2. Audio Soundboard Triggers (S1-S9)
Triggers are **Active LOW**. Connecting a pin to Ground (GND) fires the sound.

| Trigger | Pin | Color | Notes |
| :--- | :---: | :--- | :--- |
| **S1** | `GPIO 4` | White | Happy/Startup |
| **S2** | `GPIO 5` | Green | Whistle |
| **S3** | `GPIO 26` | Black | Alert (Moved from 16) |
| **S4** | `GPIO 27` | White | Scream (Moved from 17) |
| **S5** | `GPIO 18` | Red | Angry Mode |
| **S6** | `GPIO 19` | Blue | Processing |
| **S7** | `GPIO 21` | Brown | Police Siren |
| **S8** | `GPIO 22` | Orange | Laugh |
| **S9** | `GPIO 23` | Yellow | Mystery Sound |

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

## 🛠️ 6. Temporary Dome Node (ESP32-D WROOM)
*Note: Use these pins only during the testing phase with the full-sized Dev Board. For S3 Mini, refer to the [Lighting Manual](../hardware/led-system.md).*

| Component | ESP32-D Pin | Wire Color |
| :--- | :---: | :--- |
| **UDNS RX** | `GPIO 3` | 🟨/⬛ Yellow/Blk |
| **UDNS TX** | `GPIO 1` | 🟩/⬛ Green/Blk |

---

## ⚡ 7. Dome ESC Pulse Calibration (goBILDA 15A)
*   **Signal (White)**: Connect to **MCU 3 (GPIO 2)**.
*   **Ground (Black)**: **MUST** be connected to the Dome Logic GND rail (Reference).
*   **Voltage (Red)**: **ISOLATE** (Do not connect) if using the Slip Ring 5V Logic Bus.

---

## 📊 6. Summary Check
- [x] S3/S4 moved to 26/27 (Hardware UART2 is now clear).
- [x] Bank switching moved to CH5 to match physical mapping.
- [x] Common logic ground established between MCU and Soundboard (Green GND).
- [x] 115200 Baud established as the Imperial Standard.
