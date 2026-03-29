# 🧵 Master Wiring Guide: Body Controller (MCU 1)

This document serves as the "Imperial Standard" for the Wee2-D2 Body Controller (ESP32D). It integrates all verified wire colors, pin assignments, and logicREALIGNMENTS established during the Phase 1 build.

---

## 🧠 1. Core MCU Pinout (Body)
The Body Controller manages all high-level RC interpretation and audio dispatching.

| Component | ESP32 Pin | Wire Color | Function |
| :--- | :---: | :--- | :--- |
| **Status LED** | `GPIO 2` | Onboard | System Heartbeat |
| **UDNS TX** | `GPIO 17` | 🟨/⬛ Yellow/Blk | Serial Out (Command Bus) |
| **UDNS RX** | `GPIO 16` | 🟩/⬛ Green/Blk | Serial In (Telemetry) |
| **RC CH3** | `GPIO 25` | ⬜/⬛ Grey/Blk | Audio Trigger A |
| **RC CH4** | `GPIO 33` | 🟦/⬛ Blue/Blk | Audio Trigger B |
| **RC CH5** | `GPIO 32` | 🟪/⬛ Purple/Blk | Bank Switching |

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
| **Red (5V)** | Slot 5 (+) | `5V` | Master Logic Power |
| **Black (GND)** | Slot 5 (-) | `GND` | Master Logic Ground |
| **Grey/Black** | Slot 3 (S) | `GPIO 25` | CH3 Pulse Data |
| **Blue/Black** | Slot 4 (S) | `GPIO 33` | CH4 Pulse Data |
| **Purple/Black**| Slot 5 (S) | `GPIO 32` | CH5 Pulse Data |

---

## 🛞 4. Slip Ring Interconnects (6-Circuit)
The serial signal must pass through the **C5/C6** circuits.

| Circuit | Role | Wire Color | Path |
| :--- | :---: | :--- | :--- |
| **C5 (TX)** | UDNS TX | 🟨/⬛ Yellow/Blk | Body -> Dome (Command) |
| **C6 (RX)** | UDNS RX | 🟩/⬛ Green/Blk | Dome -> Body (Telemetry) |

---

## 🛠️ 5. Temporary Dome Node (ESP32-D WROOM)
*Note: Use these pins only during the testing phase with the full-sized Dev Board. For S3 Mini, refer to the [Lighting Manual](../hardware/led-system.md).*

| Component | ESP32-D Pin | Wire Color |
| :--- | :---: | :--- |
| **UDNS RX** | `GPIO 3` | 🟨/⬛ Yellow/Blk |
| **UDNS TX** | `GPIO 1` | 🟩/⬛ Green/Blk |

---

## 📊 6. Summary Check
- [x] S3/S4 moved to 26/27 (Hardware UART2 is now clear).
- [x] Bank switching moved to CH5 to match physical mapping.
- [x] Common logic ground established between MCU and Soundboard (Green GND).
- [x] 115200 Baud established as the Imperial Standard.
