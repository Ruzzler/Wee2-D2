![manual-hero](../../assets/dfplayer-mini-module.jpg)


# <i data-lucide="music"></i> DFPlayer Mini Specification

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: AUDIO HUB** | **MODEL: DFPLAYER MINI (MP3-TF-16P)**


The sound hub for the Wee2-D2 project is powered by a DFPlayer Mini (MP3-TF-16P). This module provides hardware-level MP3 decoding and is managed via a dedicated serial bus from Node 2.


---


## Hardware Specifications (Audio Focus)

The **DFPlayer Mini** is a specialized sound module that integrates a microSD slot and a low-latency serial interface. It is the primary audio source for all behavioral triggers.


| Parameter | Specification | Value |
| :--- | :--- | :--- |
| **Model** | MP3-TF-16P (UART) | Sound Hub |
| **Storage** | MicroSD (FAT32) | 32GB Max |
| **Decoding** | MP3 / WAV (Hardware) | 24-bit DAC |
| **Voltage** | 3.2V–5.0V (Logic) | 5V Rail |
| **Signal Out** | DAC_L / DAC_R | Line Level |


---


## Logic Integration: Node 2 (Sound Hub)

The DFPlayer Mini is managed by **Node 2 (Sound Hub)** using a dedicated UART bus. The ESP32 provides a standard serial signal to trigger specific folders and files.


These settings are verified in the `v2.6.0-Dashboard` firmware sequence.


- **Master Node**: Node 2 (Sound Hub / ESP32-S3)
- **GPIO TX**: **GPIO 43** (UART Send)
- **GPIO RX**: **GPIO 44** (Serial Feedback)
- **Baud Rate**: 9600 bps (standard for MP3-TF-16P)
- **Protocol**: 1-byte Direct (Mesh Trigger) | [node-1.yaml:81](../../firmware/production/node-1-dome-motion.yaml#L81)


---


## Physical Hookup & Wiring

The sound module is connected to Node 2 and the TPA3118 amplifier using standard jumper wires. Power is supplied by the central **Mini560 Pro** buck converter in the body logic stack.


1. **Serial Link**: TX (Node 2) to RX (DFPlayer) | RX (Node 2) to TX (DFPlayer).
2. **Audio Link**: DAC_L / DAC_R to TPA3118 Input.
3. **Common Ground**: Shared GND with Node 2 and the TPA3118 Amplifier.
4. **Resistor**: A **1K Ohm Resistor** is required on the RX line to prevent serial noise.


---


## Hardware Calibration

To ensure audio triggers like "The Cantina Band" play predictably, the MicroSD card must be correctly organized.


- **Folders**: Name folders `01`, `02`, etc.
- **Files**: Name files `001.mp3`, `002.mp3`, etc.
- **MicroSD Card**: Ensure you use a high-quality (Class 10) card to prevent audio "stutter" during high-bitrate files.
- **Isolation**: Keep the analog audio wires separate from the 20V motor trunks to prevent electrical interference.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View Audio System Guide](../capabilities/audio-system.md)