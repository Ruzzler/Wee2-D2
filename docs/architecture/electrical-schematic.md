# Droid Electrical Schematic

This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system.

![Chassis Electronics Layout](../../assets/chassis-electronics-layout.png)

---

## Interactive Schematic

> [!TIP]
> **INTERACTIVE INTERFACE**: Click on any component node to instantly access its technical manual or firmware specification.

```mermaid
flowchart TD
 subgraph TRANSMITTERS [TX INTERFACE]
 TX1["TX 1: Body Drive"]:::signal
 TX2["TX 2: Dome Motion"]:::signal
 end

 subgraph POWER_CORE [20V DC POWER CORE]
 BAT["DeWalt 20V Battery"]:::power --> LVC["LVP-R1.5 (40A)"]:::power
 LVC --> POS_FUSE["Positive Fuse Box"]:::power
 LVC --> NEG_BUS["Negative Bus Bar"]:::power
 end

 subgraph HIGH_POWER [20V RAIL]
 POS_FUSE --> ESC1["FSESC (Left)"]:::drive
 POS_FUSE --> ESC2["FSESC (Right)"]:::drive
 POS_FUSE --> AMP["TPA3118 Amp"]:::audio
 POS_FUSE --> BODY_BUCK["Mini560 (5V Logic)"]:::logic
 POS_FUSE --> SLIP1["Slip C1/C2 (Motor)"]:::power
 POS_FUSE --> SLIP2["Slip C3/C4 (Logic)"]:::power

 NEG_BUS --> ESC1
 NEG_BUS --> ESC2
 NEG_BUS --> AMP
 NEG_BUS --> BODY_BUCK
 NEG_BUS --> SLIP1
 NEG_BUS --> SLIP2
 end

 subgraph DOME_DISTRIBUTION [DOME POWER]
 SLIP1["Slip Ring C1/C2 (Motor)"]:::power --> DOME_WAGO_20V["20V Wago Hub (2x5)"]:::power
 SLIP2["Slip Ring C3/C4 (Logic)"]:::power --> DOME_WAGO_20V
 
 DOME_WAGO_20V --> DOME_ESC["goBILDA 15A ESC"]:::drive
 DOME_WAGO_20V --> BUCK_LEDS["Mini560 Pro (5A): LEDs"]:::logic
 DOME_WAGO_20V --> BUCK_LOGIC["Mini560 Pro (5A): Logic"]:::logic
 
 BUCK_LEDS --> LEDS["LED Matrices"]:::lights
 BUCK_LOGIC --> DOME_WAGO_5V["5V Wago Hub (2x5)"]:::power
 end

 subgraph LOGIC_RAIL [5V LOGIC & SIGNALS]
 ESC1 -->|5V BEC| RC1["Body Receiver"]:::signal
 BODY_BUCK -->|5V| NODE_2["Node 2 (Sound Hub)"]:::brain
 NODE_2 -->|UART| AUDIO["DFPlayer Mini"]:::audio
 
 DOME_ESC -.->|Isolated| RC2["Dome Receiver"]:::signal

 DOME_WAGO_5V --> NODE_3["Node 3 (Lights WLED)"]:::brain
 DOME_WAGO_5V --> NODE_1["Node 1 (Dome S3)"]:::brain
 DOME_WAGO_5V --> RC2
 end

 subgraph INTERCONNECTS [COMMUNICATION]
 TX1 -.->|2.4GHz| RC1
 TX2 -.->|2.4GHz| RC2
 RC1 -->|PWM| ESC1
 RC1 -->|PWM| ESC2
 RC2 -->|PWM| NODE_1
 NODE_1 -->|PWM| DOME_ESC
 AUDIO -->|Analog| AMP
 NODE_1 <.->|ESP-NOW Mesh| NODE_2
 NODE_1 -->|UART| NODE_3
 end

 %% Technical Manual Links
 click BAT href "../maintenance/battery-runtime-guide.md" "Battery Guide"
 click LVC href "../hardware/mgcstem-lvp-r15-manual.md" "LVP Manual"
 click ESC1 href "../hardware/flipsky-fsesc-67-pro-manual.md" "ESC Manual"
 click ESC2 href "../hardware/flipsky-fsesc-67-pro-manual.md" "ESC Manual"
 click AUDIO href "../hardware/dfplayer-mini-spec.md" "Audio Hub Spec"
 click SLIP1 href "node-pinout-guide.md" "Slip Ring Pinouts"
 click BUCK_LOGIC href "../bill-of-materials.md" "BOM"
 click RC1 href "../hardware/hotrc-f06a-manual.md" "Receiver Manual"
 click RC2 href "../hardware/hotrc-f06a-manual.md" "Receiver Manual"
 click NODE_1 href "node-1-dome-motion.md" "Node 1"
 click NODE_2 href "node-2-sound-hub.md" "Node 2"
 click NODE_3 href "node-3-led-distribution.md" "Node 3"
 click DOME_ESC href "../hardware/gobilda-motor-manual.md" "Motor Manual"
 click BODY_BUCK href "../bill-of-materials.md" "BOM"

 classDef power fill:#ff9900,stroke:#333,stroke-width:2px,color:#000
 classDef drive fill:#cc3300,stroke:#fff,color:#fff
 classDef logic fill:#00cccc,stroke:#333,color:#000
 classDef brain fill:#0066cc,stroke:#fff,color:#fff
 classDef audio fill:#99cc00,stroke:#000,color:#000
 classDef signal fill:#ffcc00,stroke:#333,color:#000
 classDef lights fill:#6600cc,stroke:#fff,color:#fff
```

---

## Wiring & Pinout Reference

For detailed wire colors, GPIO assignments, and hardware-specific triggers, consult the master reference:

> [!IMPORTANT]
> **[Master Node Pinout & Wiring Guide](node-pinout-guide.md)**
> This document contains the absolute source of truth for all node wiring, BEC isolation, and star-grounding practices.

---

## Engineering Best Practices

- **Star-Grounding**: All system grounds **MUST** terminate at the central Negative Bus Bar to prevent signal noise.
- **Slip Ring Isolation**: The 20V Dome Motor line and 20V Dome Logic line must remain isolated through the slip ring.
- **ESC BEC Isolation**: When using multiple speed controllers, only one BEC (typically ESC 1) should provide 5.1V logic power to the receiver.

---

[View Power Architecture](power-architecture.md)