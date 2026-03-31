# 🔊 Audio & Behavioral Triggers
> **FUNCTIONAL CAPABILITY** | **SERIAL: CAP-AUDIO-v1.8**

Wee2-D2's voice and sound system is a distributed modular stack built around the **DFPlayer Mini** (MP3 Hub) and a **TPA3118 60W Amplifier**. Triggers are managed wirelessly via the **ESP-NOW** bridge.

## 🧠 How it Works: The Wireless Trigger
Instead of physical wires running through the slip ring, the droid uses a **Wireless Behavioral Bridge**.
1.  **Event Capture**: The **Dome Master (MCU 3)** or **Body Hub (MCU 1)** detects an RC command or autonomous event.
2.  **Broadcast**: Node 3 broadcasts an **ESP-NOW** packet (e.g., `TRIGGER_SOUND_01`) across the 2.4GHz spectrum.
3.  **Command Translation**: The **Body Audio Hub (MCU 1)** receives the wireless packet and sends a precise **Serial (UART)** command to the **DFPlayer Mini**.
4.  **Amplification**: The DFPlayer outputs a low-level analog signal to the **TPA3118 Amplifier**, which drives the 60W Pyle speaker at 20V.

## 💾 SD Card Formatting (DFPlayer Standard)
For the DFPlayer Mini to recognize tracks, the SD card must follow the standard industrial naming convention. Ensure the card is formatted to **FAT32**.

The folders must be named `01` through `99`, and files must start with a 3-digit prefix.

```text
SD_ROOT/
├── 01/                     # Folder 1: Happy Sounds
│   ├── 001_beep_boop.mp3
│   └── 002_whistle.mp3
├── 02/                     # Folder 2: Alert Sounds
│   ├── 001_scream.mp3
│   └── 002_alarm.mp3
├── 03/                     # Folder 3: Ambient
│   ├── 001_low_hum.mp3
│   └── 002_processing.mp3
└── 04/                     # Folder 4: High Alert (Red)
```
*Note: The DFPlayer supports up to 255 tracks per folder, allowing for massive behavioral variety.*

## 🔄 Behavioral Bank Logic
By flicking **CH5** on your transmitter, the droid cycles through functional "Mood Banks." Node 3 broadcasts the bank change wirelessly, which updates the lighting patterns and the sound selection in Node 1:

| Behavioral Bank | Lighting Mode | Audio Character |
| :--- | :--- | :--- |
| **Bank 1 (Default)** | Blue/White | Happy / Inquisitive |
| **Bank 2 (Patrol)** | Cyan | Processing / Static |
| **Bank 3 (High Alert)** | Pulsing Red | Alarms / Screams |
| **Bank 4 (Silent)** | Dim Blue | Stealth / Event Safe |

## 🤖 Ambient Mode
When set to **Ambient Mode (Bank 1)**, the Body Hub will automatically fire random tracks from Folder `03` every 15-45 seconds to simulate droid "thinking" during idle periods.

## 🧰 Audio Stack Interconnect (UART)
Unlike the legacy 9-wire trigger system, the v1.8 stack uses a 4-wire serial bus for absolute control:

| Pin | Source (S3) | Destination (DFPlayer) | Role |
| :---: | :--- | :--- | :--- |
| **TX** | **GPIO 17** | RX Pin | Serial Data Output |
| **RX** | **GPIO 16** | TX Pin | Status Data Input |
| **VCC** | 5V Rail | VCC Pin | Power (5V/1A Peak) |
| **GND** | Star Ground | GND Pin | Logic Reference |

---
**Relevant Hardware & Code:**
*   [DFPlayer Mini Data Sheet](../../bill-of-materials.md)
*   [MCU 1: Body Audio Hub](../../../firmware/mcu1-body-controller/README.md)
