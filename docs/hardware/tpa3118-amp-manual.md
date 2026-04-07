# <i data-lucide="volume-1"></i> TPA3118 Amplifier Manual

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: AUDIO HUB** | **MODEL: TPA3118 (MONO)**


The audio amplification for the Wee2-D2 project is handled by a TPA3118 Class-D Mono amplifier. This module is configured in PBTL (Parallel Bridge-Tied Load) mode to deliver high-volume cinematic sound through a single 4-ohm driver.


---


## Hardware Specifications (Audio Focus)

The **TPA3118** is a high-efficiency Class-D amplifier module. It is selected for its compact footprint and its ability to provide 60W of power while running on the 5V logic rail.


| Parameter | Specification | Value |
| :--- | :--- | :--- |
| **Model** | TPA3118 (Mono) | PBTL Mode |
| **Power Output** | 60W RMS (Max) | Class-D |
| **Voltage** | 12V–24V (Running at 12V Boosted) | Dual Buck Opt. |
| **Resistance** | 4–8 Ohm | (4 Ohm Opt.) |
| **Signal In** | Line-Level (DAC) | Mono |


---


## Logic Integration: Node 2 (Sound Hub)

The amplifier receives an analog line-level signal from the DFPlayer Mini, which is managed by **Node 2 (Sound Hub)**. Gain is controlled through the hardware potentiometer on the TPA3118 module.


These settings are verified in the `v2.6.0-Dashboard` hardware stack.


- **Input Feed**: DAC_L / DAC_R from DFPlayer Mini.
- **Master Ground**: Shared Common Negative with Node 2 and the Sound Hub Logic.
- **Power Source**: Dedicated Mini560 Pro 5V rail (boosted via secondary buck if required).
- **Gain Config**: Set to 80% to prevent driver clipping.


---


## Physical Hookup & Wiring

The TPA3118 is connected to the Sound Hub logic stack using standard 18AWG power wires and analog audio jumpers. Power is supplied by the central **Mini560 Pro** buck converter in the body.


1. **Power In**: VCC (12-24V) / GND (Common Negative trunk).
2. **Signal In**: LIN / RIN (from DFPlayer DAC pins).
3. **Speaker Out**: L+/L- (to Pyle 3.5" Driver).
4. **Common Ground**: Ensure the amplifier ground is tied to the central Negative Bus Bar to prevent "audio hum."


---


## Hardware Calibration

To ensure clear sound during long playbacks, the amplifier must be heat-shielded and correctly grounded.


- **Thermal Management**: Class-D amplifiers are efficient, but the TPA3118 will get warm under 60W loads. Ensure it is mounted with adequate airflow in the body cavity.
- **Noise Filtering**: If you hear "hissing," verify that the DAC signal wires are shielded or kept separate from the 20V motor trunks. 
- **Star-Grounding**: If "motor whine" is audible in the speaker, check that the amplifier ground is not in a series-loop with the FSESC ground.


---


[View Master Schematic](../architecture/electrical-schematic.md) | [View Audio System Guide](../capabilities/audio-system.md)
