# <i data-lucide="battery-charging"></i> Power Architecture

This document tracks the electrical routing, distribution, and protection systems for Wee2-D2. Locomotion and logic systems are isolated into distinct rails to ensure signal integrity and operational stability.

---

## 1. The Core Source

The droid operates on a **20V High-Power Standard**, sourcing energy from a ganged **DeWalt 20V Battery** array.

### Protection Layer

- **Master LVP (MgcSTEM LVP-R1.5)**: A 40A low-voltage protector monitors the battery source. It is configured with a **17.5V Cutoff** to prevent over-discharge and permanent battery cell damage.
- **Positive Blade Fuse Box**: Receives the raw 20V Positive line from the LVP. Individual systems are fused for over-current protection.
- **Negative Bus Bar (Star Ground)**: Receives the raw 20V Negative line. All system grounds trace back to this central anchor for signal integrity.

---

## 2. Power Rail Hierarchy

Wee2-D2 utilizes isolated voltage rails to protect sensitive logic from motor-induced EMF noise.

### A. 20V High-Power Rail
| Component | Function | Source |
| :--- | :--- | :--- |
| [Drive System](../hardware/flipsky-fsesc-67-pro-manual.md) | Dual Flipsky 6.7 Pro ESCs | Fuse Box (20V) |
| [Dome Motion](../hardware/gobilda-motor-manual.md) | goBILDA 15A PWM ESC | Slip Ring (20V) |
| [Audio Amp](..\capabilities\lights-and-sounds\audio-system.md) | TPA3118 60W Mono | Fuse Box (20V) |

### B. 5.1V Logic & Audio Rail
| Component | Role | Regulation Source |
| :--- | :--- | :--- |
| [Node 1 (Sound)](node-1-sound-hub-spec.md) | Body logic & sounds | Flipsky BEC (5.1V) |
| [Node 2 (LEDs)](node-2-led-distribution-spec.md) | Dome lighting arrays | Mini560 Buck (5.1V) |
| [Node 3 (Motion)](node-3-dome-motion-spec.md) | Dome motion processing | goBILDA BEC (5.1V) |

---

## 3. The Slip Ring Bridge (Body to Dome)

The **CNBTR Slip Ring** (6 wires) acts as the high-current bridge. We utilize a **Dual-Circuit Isolation Strategy** to separate motor noise from logic.

| Circuit | Function | Current (Peak) | Pinout |
| :--- | :--- | :---: | :---: |
| **Circuit 1** | **Dome Motor (20V)** | 10.0A | C1 (+) / C2 (-) |
| **Circuit 2** | **Dome Logic & LEDs (20V)** | 10.0A | C3 (+) / C4 (-) |
| **Expansion** | Reserved for Serial / Telemetry | — | C5 / C6 |

> [!CAUTION]
> **SIGNAL ISOLATION**: Never bridge the 20V (+) lines of Circuit 1 and Circuit 2. Inductive spikes from the dome motor will destabilize the LED logic if rails share a positive leg through the slip ring.

---

## 4. Grounding & Safety Protocols

### Star Ground Rule
Every component in the droid (Nodes, ESCs, Receivers, and LED Strips) **MUST** share a common ground reference. All grounds trace back to the central **Negative Bus Bar**. Without this shared reference, PWM and UART data signals will become unreadable interference.

### Processing Clamps
- **Dynamic Speed Multiplier**: Node 3 provides a dashboard-adjustable speed cap (0.1 - 1.0) to ensure cinematic motion regardless of raw voltage level.
- **Current Limiters**: Node 2 maintains an internal brightness limit of **3500mA** to protect the buck converters from thermal runaway.

---

[View Electrical Schematic](electrical-schematic.md)