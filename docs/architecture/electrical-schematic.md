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
 POS_FUSE --> SLIP1["Slip C1/C2 (Motor)"]:::power
 POS_FUSE --> SLIP2["Slip C3/C4 (Logic)"]:::power

 NEG_BUS --> ESC1
 NEG_BUS --> ESC2
 NEG_BUS --> AMP
 NEG_BUS --> SLIP1
 NEG_BUS --> SLIP2
 end

 subgraph DOME_DISTRIBUTION [DOME POWER]
 SLIP1 --> DOME_ESC["goBILDA 15A ESC"]:::drive
 SLIP2 --> DOME_BUCK["Mini560 (5V Logic)"]:::logic
 DOME_BUCK --> DOME_WAGOS["Dome Wago Hub"]:::power
 end

 subgraph LOGIC_RAIL [5V LOGIC & SIGNALS]
 ESC1 -->|5V BEC| RC1["Body Receiver"]:::signal
 RC1 -->|5V| Node2["Node 2 (Sound Hub)"]:::brain
 Node2 -->|UART| AUDIO["DFPlayer Mini"]:::audio
 
 DOME_ESC -.->|Isolated| RC2["Dome Receiver"]:::signal

 DOME_WAGOS --> Node3["Node 3 (Lights WLED)"]:::brain
 DOME_ESC -->|PWM| Node1["Node 1 (Dome S3)"]:::brain
 DOME_WAGOS --> LEDS["LED Matrices"]:::lights
 end

 subgraph INTERCONNECTS [COMMUNICATION]
 TX1 -.->|2.4GHz| RC1
 TX2 -.->|2.4GHz| RC2
 RC1 -->|PWM| ESC1
 RC1 -->|PWM| ESC2
 RC1 -->|PWM| Node2
 RC2 -->|PWM| Node1
 Node1 -->|PWM| DOME_ESC
 AUDIO -->|Analog| AMP
 Node1 -.->|ESP-NOW| Node2
 Node1 -.->|ESP-NOW| Node3
 end

 %% Technical Manual Links
 click BAT href "../maintenance/battery-runtime-guide.md" "Battery Guide"
 click LVC href "../hardware/mgcstem-lvp-r15-manual.md" "LVP Manual"
 click ESC1 href "../hardware/flipsky-fsesc-67-pro-manual.md" "ESC Manual"
 click ESC2 href "../hardware/flipsky-fsesc-67-pro-manual.md" "ESC Manual"
 click AUDIO href "../hardware/dfplayer-mini-spec.md" "Audio Hub Spec"
 click SLIP1 href "node-pinout-guide.md" "Slip Ring Pinouts"
 click DOME_BUCK href "../bill-of-materials.md" "BOM"
 click RC1 href "../hardware/hotrc-f06a-manual.md" "Receiver Manual"
 click RC2 href "../hardware/hotrc-f06a-manual.md" "Receiver Manual"
 click Node1 href "node-1-dome-motion-spec.md" "Node 1 Spec"
 click Node2 href "node-2-sound-hub-spec.md" "Node 2 Spec"
 click Node3 href "node-3-led-distribution-spec.md" "Node 3 Spec"
 click DOME_ESC href "../hardware/gobilda-motor-manual.md" "Motor Manual"

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