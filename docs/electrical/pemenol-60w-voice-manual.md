# 🏛️ IMPERIAL DATABANK: PEMENOL 60W AUDIO
> **DECRYPTED DATA REPOSITORY** | **SERIAL: PEMENOL-DY-HL50T**

![PEMENOL 60W Voice Module](assets/soundboard-top.jpg)

The **PEMENOL 60W** (DY-HL50T) is the primary voice playback module for Wee2-D2. It features a powerful 60W Class D mono amplifier.

> [!IMPORTANT]
> **NO UART CONTROL**: After evaluating the technical specifications of the **DY-HL50T** module currently in use, it is confirmed that this specific hardware **DOES NOT support UART / Serial control**. Control is achieved exclusively via the 9 segmented trigger pins (S1-S9) and the 3-bit DIP switch modes.

## ⚡ Power & Audio
*   **Operating Voltage**: DC 9V – 24V.
*   **Amplifier**: 60W Mono Class D.
*   **Volume**: Adjusted via the onboard blue potentiometer.

![Features & Specs](assets/soundboard-features.jpg)

## 🕹️ Trigger Modes (DIP Switch)
The module uses a 3-bit DIP switch to set the trigger behavior. **Power cycle the module after changing switches.**

![DIP Switch Modes](assets/soundboard-modes.jpg)

### Common Droid Configurations:
| Switch 1 | Switch 2 | Switch 3 | Mode | Behavior |
| :---: | :---: | :---: | :--- | :--- |
| **OFF** | **OFF** | **OFF** | Level Non-Interr. | Plays once; cannot be interrupted. |
| **ON** | **OFF** | **OFF** | Level Interr. | Plays once; restarts if triggered again. |
| **ON** | **ON** | **OFF** | Pulse Non-Interr. | Plays once; plays in order if multiple triggers. |

## 🔌 Pinout & Wiring
![Pinout Diagram](assets/soundboard-labels.webp)

*   **VCC/GND**: 9-24V Power Input.
*   **SPK+/SPK-**: Speaker Output.
*   **S1 - S9**: Trigger inputs (Active Low).
*   **COM**: Common Ground for triggers.

![Reference Wiring](assets/soundboard-wiring.jpg)

## 📐 Dimensions & PCB Layout
![PCB Schematic](assets/soundboard-schematic.jpg)
