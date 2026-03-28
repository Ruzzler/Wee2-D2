# 🏛️ IMPERIAL DATABANK: PEMENOL 60W AUDIO
> **DECRYPTED DATA REPOSITORY** | **SERIAL: PEMENOL-DY-HL50T**

![PEMENOL 60W Voice Module](../../assets/soundboard-top.jpg)

The **PEMENOL 60W** (DY-HL50T) is the primary voice playback module for Wee2-D2. It features a powerful 60W Class D mono amplifier.

![DIP Switch Modes 1](../../assets/soundboard-modes.jpg)
![DIP Switch Modes 2](../../assets/soundboard-modes-2.jpg)
![DIP Switch Modes 3](../../assets/soundboard-modes-3.jpg)

### Common Droid Configurations:
| Switch 1 | Switch 2 | Switch 3 | Mode | Behavior |
| :---: | :---: | :---: | :--- | :--- |
| **OFF** | **OFF** | **OFF** | Level Non-Interr. | Plays once; cannot be interrupted. |
| **ON** | **OFF** | **OFF** | Level Interr. | Plays once; restarts if triggered again. |
| **ON** | **ON** | **OFF** | Pulse Non-Interr. | Plays once; plays in order if multiple triggers. |
| **OFF** | **OFF** | **ON** | MP3 Mode 2 | Automatic loop all folder files after Power ON. |

## 🔌 Pinout & Wiring
![Pinout Diagram](../../assets/soundboard-labels.webp)

*   **VCC/GND**: 9-24V Power Input.
*   **SPK+/SPK-**: Speaker Output.
*   **S1 - S9**: Trigger inputs (Active Low).
*   **COM**: Common Ground for triggers.

![Reference Wiring](../../assets/soundboard-wiring.jpg)

## 📐 Dimensions & PCB Layout
![PCB Schematic](../../assets/soundboard-schematic.jpg)
