# <i data-lucide="battery-charging"></i> Power Architecture

This document tracks the electrical routing, distribution, and protection systems for Wee2-D2. Locomotion and logic systems are isolated into distinct rails to ensure signal integrity and operational stability.

---

## 1. The Core Source

The droid operates on a **20V High-Power Standard**, sourcing energy from a ganged **DeWalt 20V Battery** array.

### Protection Layer

| Component | Role | Technical Specification |
| :--- | :--- | :--- |
| **Master LVP (MgcSTEM)** | 40A Safety Layer | Monitors battery source; **17.5V Cutoff** to prevent over-discharge. |
| **Positive Fuse Box** | Circuit Protection | Distributes 20V Positive to individually fused subsystems. |
| **Negative Bus Bar** | Star Ground Anchor | Central ground reference for all system logic and noise isolation. |

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
| [Node 1 (Motion)](node-1-dome-motion.md) | Dome motion processing | Mini560 Pro (5A) |
| [Node 2 (Sound)](node-2-sound-hub.md) | Body logic & sounds | Mini560 Pro (5A) |
| [Node 3 (LEDs)](node-3-led-distribution.md) | Dome lighting arrays | Mini560 Pro (5A) |
| [Body Receiver](node-pinout-guide.md#4-hardware-interconnects) | Body RC Input | FSESC 1 BEC (5V) |
| [Dome Receiver](node-pinout-guide.md#4-hardware-interconnects) | Dome RC Input | Mini560 Pro (5A) - Logic |
| [DFPlayer Mini](../hardware/dfplayer-mini-spec.md) | Audio Hub | Mini560 Pro (5A) - Logic |
| LED Matrices (Logic) | Visual Display | Mini560 Pro (5A) - LEDs |
| GrnWave PSIs | Circular Displays | Mini560 Pro (5A) - LEDs |

---

## 3. The Slip Ring Bridge (Body to Dome)

The **CNBTR Slip Ring** (6 wires) acts as the high-current bridge. We utilize a **Ganged Trunk Strategy** to provide maximum current overhead to the dome via the Slip Ring's multi-circuit capability.

| Circuit | Function | Current (Peak) | Pinout |
| :--- | :--- | :---: | :---: |
| **Circuit 1** | **Ganged 20V Trunk** | 10.0A | C1 (+) / C2 (-) |
| **Circuit 2** | **Ganged 20V Trunk** | 10.0A | C3 (+) / C4 (-) |
| **Expansion** | Reserved for Serial / Telemetry | — | C5 / C6 |

> [!IMPORTANT]
> **REFINED ISOLATION**: While the 20V lines are now ganged at the **Dome 2x 5-Port Wago Hub** to ensure amperage stability, isolation from motor noise is maintained downstream via **Dual Mini560 Pro (5A)** buck converters. One converter is dedicated to logic (Node 1/3/RC), while the other is dedicated solely to LED arrays.

---

## 4. Grounding & Safety Protocols

### Star Ground Rule
Every component in the droid (Nodes, ESCs, Receivers, and LED Strips) **MUST** share a common ground reference. All grounds trace back to the central **Negative Bus Bar**. Without this shared reference, PWM and UART data signals will become unreadable interference.

### BEC & Buck Isolation
To prevent ground loops and inductive spikes from motor transients, the following isolation rules are enforced:
- **Body isolation**: Only **FSESC 1** provides BEC power to the body receiver. FSESC 2's BEC is isolated (not connected).
- **Dome isolation**: The goBILDA 15A ESC's internal BEC is isolated. Logic power is sourced strictly from the ganged trunk via the Mini560 Pro (5A) Logic Rail.

### Processing Clamps
- **Dynamic Speed Multiplier**: Node 1 provides a dashboard-adjustable speed cap (0.1 - 1.0) to ensure cinematic motion regardless of raw voltage level.
- **Current Limiters**: Node 3 maintains an internal brightness limit of **3500mA** to protect the **Mini560 Pro (5A)** buck converters from thermal runaway.

---

[View Electrical Schematic](electrical-schematic.md)