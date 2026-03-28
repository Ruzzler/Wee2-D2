# 🏛️ IMPERIAL DATABANK: DY-HL50T AUDIO
> **DECRYPTED DATA REPOSITORY** | **SERIAL: DY-HL50T-60W**

The **DY-HL50T** is the primary voice playback module for Wee2-D2. It features a powerful 60W Class D mono amplifier capable of driving large speakers directly from the main 20V battery.

## ⚡ Power & Audio
*   **Operating Voltage**: DC 9V – 24V (Can be powered directly from the fused 20V bus).
*   **Amplifier**: 60W Mono Class D (Supports 4-8Ω speakers, 20-60W).
*   **Volume**: Adjusted via the onboard blue potentiometer (CW to increase).

## 📂 File Management
*   **Storage**: TF Card (MicroSD) up to 32GB, formatted to **FAT32**.
*   **Naming Convention**: Files must be in the root directory and named as 5-digit numbers:
    *   `00001.mp3` corresponds to trigger **S1**
    *   `00002.mp3` corresponds to trigger **S2**
    *   ...up to `00009.mp3` for **S9**.

## 🕹️ Trigger Modes (DIP Switch)
The module uses a 3-bit DIP switch to set the trigger behavior. **Power cycle the module after changing switches.**

### Common Droid Configurations:
| Switch 1 | Switch 2 | Switch 3 | Mode | Behavior |
| :---: | :---: | :---: | :--- | :--- |
| **OFF** | **OFF** | **OFF** | 9-Way Standard | Play once when triggered; cannot be interrupted. |
| **OFF** | **OFF** | **ON** | 9-Way Loop | Plays while pin is held GND; loops continuously. |
| **ON** | **ON** | **OFF** | UART Mode | Used for serial control (Note: HW revision dependent). |

> [!TIP]
> **NPN/GND Triggering**: The S1-S9 pins are active-low. To trigger a sound from an ESP32 (Node 1), briefly pull the corresponding GPIO to **GND**.

## 🔌 Pinout
*   **VCC/GND**: 9-24V Power Input.
*   **SPK+/SPK-**: Speaker Output.
*   **S1 - S9**: Trigger inputs (Active Low).
*   **COM**: Common Ground for triggers.
*   **Micro USB**: For direct file transfer from a PC.
