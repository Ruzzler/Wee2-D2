# 🔊 Audio & Voice Triggers
> **FUNCTIONAL CAPABILITY** | **SERIAL: CAP-AUDIO-v1.0**

Wee2-D2's voice and sound system is built around the **PEMENOL 60W Soundboard** (DY-HL50T) controlled digitally by **MCU 1 (Body Controller)**.

## 🧠 How it Works
Instead of simply tying 9 buttons on a remote to 9 sounds, the droid uses complex **"Bank Switching" logic** running on the ESP32 to drastically multiply the number of available audio triggers.
1.  Your RC Receiver reads the button pulses.
2.  **MCU 1** interprets those pulses and checks which "Bank" you are currently in.
3.  **MCU 1** grounds out one of the 9 trigger pins on the PEMENOL board.
4.  The PEMENOL board reads the micro-SD card and plays the corresponding MP3 class-D amplified audio out to the 60W Pyle speaker.

## 💾 SD Card Formatting (CRITICAL)
For the ESPHome bank logic to work, the soundboard's DIP switches must be set to `000` (Level Non-Interruptible) or `100` (Level Interruptible). This creates a 1-to-1 map between the 9 trigger pins and 9 specific folders on your SD card. 

The folders **must** be named exactly `01` through `09`. 

```text
SD_ROOT/
├── 01/                     # Triggered by S1
│   ├── 001_happy.mp3
│   └── 002_excited.mp3
├── 02/                     # Triggered by S2
│   ├── 001_sad.mp3
├── 03/                     # Triggered by S3 (etc.)
├── 04/
├── 05/
├── 06/
├── 07/
├── 08/
└── 09/                     # Triggered by S9
```
*Note: If a trigger is hit twice, the PEMENOL board automatically shuffles to the next MP3 in that folder.*

## 🔄 The ESPHome Bank Logic
By flicking **CH5** on your transmitter, MCU 1 cycles through 4 internal "Banks." This routes your standard CH3 and CH4 joystick movements to completely different audio folders on the SD card:

| ESPHome Bank | Trigger Mode | Mapped Audio Folder |
| :--- | :--- | :--- |
| **Bank 1 (Default)** | CH3 Up / Down | Folder `01` / `02` |
| **Bank 1 (Default)** | CH4 Up / Down | Folder `03` / `04` |
| **Bank 2 (Alt 1)** | CH3 Up / Down | Folder `05` / `06` |
| **Bank 2 (Alt 1)** | CH4 Up / Down | Folder `07` / `08` |
| **Bank 3 (Alt 2)** | CH3 Up only | Folder `09` (Angry/Red) |

## 🤖 Bank 4 (Auto-Mode)
When you cycle into **Bank 4**, the ESP32 enters "Ambient Mode." Every 5 to 15 seconds, MCU 1 will automatically fire a random trigger from S1 to S9. Ensure every folder (`01`-`09`) has at least one MP3, otherwise Auto-Mode may randomly trigger a silent folder during an event!

## 🧰 Physical Wiring Guide (S1-S9)
When physically wiring the ESP32 (MCU 1) to the PEMENOL soundboard, ensure the following wire colors map exactly to the S1-S9 triggers:

| Trigger | ESP32 GPIO | Wire Color |
| :--- | :---: | :--- |
| **S1** | GPIO4 | 🟨 Yellow |
| **S2** | GPIO5 | 🟥 Red |
| **S3** | **GPIO26** | ⬛ Black |
| **S4** | **GPIO27** | ⬜ White |
| **S5** | GPIO18 | 🟫 Brown |
| **S6** | GPIO19 | 🟪 Purple |
| **S7** | GPIO21 | 🟦 Blue |
| **S8** | GPIO22 | ⬜ Grey |
| **S9** | GPIO23 | 🟧 Orange |
| **GND Line**| GND (near 3V3) | 🟩 Green |

---
**Relevant Hardware & Code:**
*   [PEMENOL 60W Soundboard Data](../../hardware/pemenol-60w-voice-manual.md)
*   [MCU 1: Body Controller](../../../firmware/mcu1-body-controller/README.md)
