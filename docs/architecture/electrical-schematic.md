# Droid Electrical Schematic

This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system.

![Chassis Electronics Layout](../../assets/chassis-electronics-layout.png)

---

## Interactive Schematic

> [!TIP]
> **INTERACTIVE INTERFACE**: Click on any component node to instantly access its technical manual or firmware specification.

```mermaid
flowchart TD
  subgraph TRANSMITTERS["TX INTERFACE"]
    TX1["TX 1: Body Drive"]:::signal
    TX2["TX 2: Dome Motion"]:::signal
  end

  subgraph BODY_HUB["BODY COMPARTMENT"]
    BAT["DeWalt 20V Battery"]:::power ==>|20V| LVC["LVP-R1.5 (40A)"]:::power
    LVC ==>|20V| POS_FUSE["Positive Fuse Box"]:::power
    LVC ==>|GND| NEG_BUS["Negative Bus Bar"]:::power

    POS_FUSE ==>|20V| ESC1["FSESC (Left)"]:::drive
    POS_FUSE ==>|20V| ESC2["FSESC (Right)"]:::drive
    POS_FUSE ==>|20V| AMP["TPA3118 Amp"]:::audio
    POS_FUSE ==>|20V| BODY_BUCK["Body Logic Buck: Mini560 Pro (5A)"]:::logic

    NEG_BUS -.->|GND| ESC1
    NEG_BUS -.->|GND| ESC2
    NEG_BUS -.->|GND| AMP
    NEG_BUS -.->|GND| BODY_BUCK

    BODY_BUCK -->|5V| NODE_2["Node 2 (Sound Hub)"]:::brain
    BODY_BUCK -->|5V| AUDIO["DFPlayer Mini"]:::audio
    ESC1 -->|5V BEC| RC1["Body Receiver"]:::signal

    NODE_2 -->|UART| AUDIO
    AUDIO -->|I2S Analog| AMP
    AMP -->|Audio Out| SPK["Visaton 4W Speaker"]:::audio
    RC1 -->|PWM| ESC1
    RC1 -->|PWM| ESC2
  end

  subgraph SLIP_RING_BRIDGE["BRIDGE"]
    POS_FUSE ==>|20V Trunk| SLIP["Slip Ring C1/C2/C3/C4"]:::power
  end

  subgraph DOME_HUB["DOME COMPARTMENT"]
    SLIP ==>|20V| DOME_WAGO_20V["20V Wago Hub (2x5)"]:::power

    DOME_WAGO_20V ==>|20V| DOME_ESC["goBILDA 15A ESC"]:::drive
    DOME_WAGO_20V ==>|20V| BUCK_LEDS["Dome LED Buck (5A)"]:::logic
    DOME_WAGO_20V ==>|20V| BUCK_LOGIC["Dome Logic Buck (5A)"]:::logic

    BUCK_LEDS -->|5V| F_PSI["Front PSI Display"]:::lights
    BUCK_LEDS -->|5V| B_PSI["Back PSI Display"]:::lights
    BUCK_LEDS -->|5V| F_LOGIC["Front Logic Display"]:::lights
    BUCK_LEDS -->|5V| B_LOGIC["Rear Logic Display"]:::lights

    BUCK_LOGIC -->|5V| DOME_WAGO_5V["5V Wago Hub (2x5)"]:::power

    DOME_WAGO_5V -->|5V| NODE_3["Node 3 (Lights WLED)"]:::brain
    DOME_WAGO_5V -->|5V| NODE_1["Node 1 (Dome S3)"]:::brain
    DOME_WAGO_5V -->|5V| RC2["Dome Receiver"]:::signal

    NODE_1 -->|PWM| DOME_ESC
    NODE_3 -->|GPIO 18| F_LOGIC
    NODE_3 -->|GPIO 19| B_LOGIC
    NODE_3 -->|GPIO 21| F_PSI
    NODE_3 -->|GPIO 22| B_PSI
  end

  subgraph INTERCONNECTS["COMMUNICATION"]
    TX1 -.->|2.4GHz| RC1
    TX2 -.->|2.4GHz| RC2
    RC2 -->|PWM| NODE_1
    NODE_1 <-.->|ESP-NOW Mesh| NODE_2
    NODE_1 -->|UART| NODE_3
  end

  %% --- ABSOLUTE TERMINATION: Styling & Interaction ---
  
  click BAT href "../maintenance/battery-runtime-guide.md" "Ganged DeWalt 20V Series (4-5Ah Typical)"
  click LVC href "../hardware/mgcstem-lvp-r15-manual.md" "17.5V Cutting Protection Floor"
  click ESC1 href "../hardware/flipsky-fsesc-67-pro-manual.md" "60V/100A Peak ESC"
  click ESC2 href "../hardware/flipsky-fsesc-67-pro-manual.md" "60V/100A Peak ESC"
  click AUDIO href "../hardware/dfplayer-mini-spec.md" "Serial MP3 Module"
  click SLIP href "node-pinout-guide.md" "10A/Circuit Industrial Slip Ring"
  click BUCK_LOGIC href "../bill-of-materials.md" "Mini560 Pro (5A) Logic"
  click RC1 href "../hardware/hotrc-f06a-manual.md" "Body RC Receiver"
  click RC2 href "../hardware/hotrc-f06a-manual.md" "Dome RC Receiver"
  click NODE_1 href "node-1-dome-motion.md" "ESP32-S3 | Dome Master Movement Controller"
  click NODE_2 href "node-2-sound-hub.md" "ESP32-S3 | Neural Command Gateway & Sound Hub"
  click NODE_3 href "node-3-led-distribution.md" "ESP32D | WLED Lighting Distribution Hub"
  click DOME_ESC href "../hardware/gobilda-motor-manual.md" "15A PWM Peak (30V Capable)"
  click BODY_BUCK href "../bill-of-materials.md" "Mini560 Pro (5A) Logic"
  click BUCK_LEDS href "../bill-of-materials.md" "Dedicated High-Current LED Supply (Mini560 Pro)"
  click SPK href "../capabilities/lights-and-sounds/audio-system.md" "Visaton 4W Speaker"

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
- **ESC BEC Isolation**: When using multiple speed controllers, only one BEC (typically ESC 1) should provide 5V logic power to the receiver.

---

[View Power Architecture](power-architecture.md)