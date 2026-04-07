![manual-hero](../../assets/chassis-electronics-layout.png)


# <i data-lucide="zap"></i> Interactive Electrical Schematic

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: FULL INTERCONNECT** | **VERSION: v2.6.0-STABLE**


The Wee2-D2 project uses a distributed power and logic architecture. This schematic visualizes the high-density interconnect between all nodes, power-rails, and hardware components.


---


## Full System Schematic (v2.6.0)

*The diagram below tracks both the 20V High-Power Trunk and the 5V Logic Rails.*


```mermaid
flowchart TD
    classDef power fill:#ff9900,stroke:#333,stroke-width:2px,color:#000
    classDef logic fill:#00f2ff,stroke:#333,stroke-width:2px,color:#000
    classDef drive fill:#ff003c,stroke:#333,stroke-width:2px,color:#000
    classDef audio fill:#8a2be2,stroke:#333,stroke-width:2px,color:#fff
    classDef control fill:#32cd32,stroke:#333,stroke-width:2px,color:#000
    classDef signal fill:#ffffff,stroke:#333,stroke-width:1px,color:#000

    subgraph NODE_MESH [CONTROL HUB & NODES]
        S3_1["Node 1 (Dome Master)"]:::logic
        S3_2["Node 2 (Sound Hub)"]:::logic
        ESP3["Node 3 (Lighting)"]:::logic
        
        S3_2 -.->|ESP-NOW Bridge| S3_1
        S3_1 -->|UART Sync| ESP3
    end

    subgraph AUDIO_SYSTEM [DOME AUDIO STACK]
        DFP["DFPlayer Mini"]:::audio
        AMP["TPA3118 Amplifier"]:::audio
        SPK["3.5\" Speaker"]:::audio

        S3_1 -->|UART| DFP
        DFP -->|Analog| AMP
        AMP -->|High Current| SPK
    end

    subgraph POWER_SOURCE [20V DC POWER CORE]
        BAT["DeWalt 20V Battery"]:::power --> LVC["MgcSTEM LVP-R1.5 (40A)"]:::power
        LVC --> POS_FUSE["Positive Blade Fuse Box"]:::power
        LVC --> NEG_BUS["Negative Bus Bar (Star Ground)"]:::power
    end

    subgraph HIGH_POWER_RAIL [20V DISTRIBUTION]
        POS_FUSE --> ESC1["Flipsky FSESC (Left)"]:::drive
        POS_FUSE --> ESC2["Flipsky FSESC (Right)"]:::drive
        POS_FUSE --> AMP["TPA3118 Amplifier"]:::audio
        POS_FUSE --> DOME_ESC["goBILDA 15A ESC"]:::drive
    end

    subgraph LOGIC_RAIL [5V REGULATION LAYER]
        POS_FUSE --> BUCK1["Mini560 Pro (Body)"]:::power
        POS_FUSE --> BUCK2["Mini560 Pro (Dome)"]:::power
        POS_FUSE --> BUCK3["Mini560 Pro (LEDs)"]:::power

        BUCK1 -->|5V Logic| S3_2
        BUCK2 -->|5V Logic| S3_1
        BUCK2 -->|5V Logic| DFP
        BUCK3 -->|5V Power| ESP3
    end

    subgraph MOTORS [PHYSICAL ACTUATORS]
        ESC1 -->|UVW Phase| L_HUB["Left Hub Motor"]:::drive
        ESC2 -->|UVW Phase| R_HUB["Right Hub Motor"]:::drive
        DOME_ESC -->|DC Output| DOME_MOT["goBILDA Yellow Jacket"]:::drive
    end

    %% Documentation Links
    click BAT href "../maintenance/battery-runtime-guide.md" "Battery Specs"
    click LVC href "../hardware/mgcstem-lvp-r15-manual.md" "LVP Manual"
    click ESC1 href "../hardware/hub-motor-manual.md" "Flipsky Manual"
    click DOME_MOT href "../hardware/gobilda-motor-manual.md" "goBILDA Motor"
    click DFP href "../hardware/dfplayer-mini-spec.md" "DFPlayer Specs"
    click S3_1 href "../architecture/node-1-dome-motion.md" "Node 1 Guide"
```


---


## Physical Wiring Standards

The project follows a clinical color-coding and routing standard to ensure serviceability.


### 1. The Ganged Trunk (Slip Ring)
To prevent grounding loops and resistive heating, we use the **C1-C4 Dual Trunk Strategy**:
- **Circuits 1 & 2**: Paired 20V Positive (Orange/Red).
- **Circuits 3 & 4**: Paired common Ground (Black).
- **Circuits 5 & 6**: Reserved for UART/PWM logic expansion.


### 2. Isolation & Signal Integrity
- **ESC Grounding**: To prevent ground loops, **only ESC 1** provides power and a ground reference to the receiver; **ESC 2** is connected via the **Signal Pin only**.
- **Signal Position**: Since the dome motor is a large DC motor, ensure logic wires are positioned away from the main motor leads to prevent EMI noise.


---


## Dome ESC Calibration (goBILDA 15A)

The Dome ESC calibration is handled via the Node 1 firmware profile.

- **Signal (White)**: Connect to **GPIO 7 (Node 1)**.
- **Ground (Black)**: Must be common to the Dome Logic 5V rail.
- **Voltage (Red)**: Isolate if using the Slip Ring 5V Logic Bus.


---


[View Power Architecture](power-architecture.md) | [View Node Pinout Guide](node-pinout-guide.md)