# <i data-lucide="zap"></i> Interactive Electrical Schematic

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: INTERACTIVE INTERCONNECT** | **DOME: NODE 1 MASTER**


The Wee2-D2 project uses a distributed power and logic architecture. This schematic visualizes the "Golden State" of the current build, including the high-current ganged trunk and the wireless ESP-NOW bridge.


---


## Interactive Schematic HUD

*Click on any component (Node, ESC, or Battery) to navigate to its specific technical documentation.*


```mermaid
flowchart TD
    %% Component Definitions
    BATT["20V DeWalt Battery"]:::power
    LVP["MgcSTEM LVP-R1.5"]:::power
    WAGO_BODY["Body Wago Hub"]:::power
    WAGO_DOME["Dome Wago Hub"]:::power
    SLIP_RING["CNBTR Slip Ring"]:::power

    subgraph BODY_DRIVE["BODY DRIVE STACK"]
      L_ESC["Flipsky FSESC 6.7"]:::drive
      R_ESC["Flipsky FSESC 6.7"]:::drive
      L_MOTOR["Left Hub Motor"]:::drive
      R_MOTOR["Right Hub Motor"]:::drive
    end

    subgraph DOME_MOTION["DOME MOTION STACK"]
      DOME_ESC["goBILDA 1x15A ESC"]:::drive
      DOME_MOTOR["Yellow Jacket Motor (5203 Series)"]:::drive
    end

    subgraph DOME_LIGHTS["CINEMATIC LED ARRAYS"]
      F_PSI["Front PSI"]:::lights
      B_PSI["Rear PSI"]:::lights
      LOGIC_DISP["Logic Display"]:::lights
    end

    subgraph MICRO_NODES["DISTRIBUTED NODES"]
      NODE_1["Node 1: Dome Master"]:::logic
      NODE_2["Node 2: Sound Hub"]:::logic
      NODE_3["Node 3: LED Distro"]:::logic
    end

    subgraph POWER_RAILS["BUCK CONVERTERS"]
      BUCK_BODY["Body Logic 5V"]:::power
      BUCK_DOME["Dome Logic 5V"]:::power
      BUCK_LEDS["Dome LED 5V"]:::power
    end

    %% Connections - Power Path
    BATT ==>|20V| LVP
    LVP ==>|20V| WAGO_BODY
    WAGO_BODY ==>|20V| L_ESC
    WAGO_BODY ==>|20V| R_ESC
    WAGO_BODY ==>|20V| BUCK_BODY
    WAGO_BODY ==>|20V| SLIP_RING

    SLIP_RING ==>|20V| WAGO_DOME
    WAGO_DOME ==>|20V| DOME_ESC
    WAGO_DOME ==>|20V| BUCK_DOME
    WAGO_DOME ==>|20V| BUCK_LEDS

    BUCK_BODY -->|5V| NODE_2
    BUCK_DOME -->|5V| NODE_1
    BUCK_LEDS -->|5V| NODE_3

    %% Connections - Logic Path
    NODE_2 -.->|ESP-NOW Mesh| NODE_1
    NODE_1 -->|UART| NODE_3

    L_ESC ==>|UVW| L_MOTOR
    R_ESC ==>|UVW| R_MOTOR
    
    NODE_1 -->|PWM| DOME_ESC
    DOME_ESC ==>|Bullet Connectors| DOME_MOTOR

    BUCK_LEDS -.->|5V Rail| F_PSI
    BUCK_LEDS -.->|5V Rail| B_PSI
    BUCK_LEDS -.->|5V Rail| LOGIC_DISP

    %% Interaction Links
    click BATT href "../maintenance/battery-runtime-guide.md" "DeWalt 20V (4Ah/6Ah/9Ah) Standard"
    click LVP href "../hardware/mgcstem-lvp-r15-manual.md" "Active 17.5V Cutoff Protection"
    click NODE_1 href "../architecture/node-1-dome-motion.md" "Dome Motion Master (ESP32-S3)"
    click NODE_2 href "../architecture/node-2-sound-hub.md" "Sound Hub & Dashboard Gateway"
    click NODE_3 href "../architecture/node-3-led-distribution.md" "WLED Lighting Distribution"
    click SLIP_RING href "../hardware/cnbtr-slip-ring-manual.md" "6-Circuit 20A Ganged Trunk"
    click DOME_ESC href "../hardware/gobilda-motor-manual.md" "15A PWM Peak (30V Capable)"
    click BUCK_LOGIC href "../bill-of-materials.md" "Mini560 Pro (5A) Logic"
    click BUCK_LEDS href "../bill-of-materials.md" "Dedicated High-Current LED Supply (Mini560 Pro)"
    click DOME_MOTOR href "../hardware/gobilda-motor-manual.md" "117 RPM / 12V High-Torque Gearmotor"
    click SPK2 href "../capabilities/lights-and-sounds/audio-system.md" "Pyle 60W RMS / 4 Ohm Driver"

  classDef power fill:#ff9900,stroke:#333,stroke-width:2px,color:#000
  classDef logic fill:#00f2ff,stroke:#333,stroke-width:2px,color:#000
  classDef drive fill:#ff003c,stroke:#333,stroke-width:2px,color:#fff
  classDef lights fill:#a371f7,stroke:#333,stroke-width:2px,color:#fff
```


---


## Technical Interconnect Summary

These pins are verified in the `v2.6.0-Dashboard` firmware sequence.


| Hardware Connection | Node Assignment | GPIO Pin | Protocol |
| :--- | :--- | :---: | :--- |
| **Dome Motor (PWM)** | Node 1: Dome Master | **GPIO 7** | PWM (1050-1950μs) |
| **RC Stick (X-Axis)** | Node 1: Dome Master | **GPIO 4** | Pulse Width |
| **WLED Lighting Bus**| Node 1 (TX Only) | **GPIO 5** | UART (115200) |
| **DFPlayer (Sound)** | Node 2: Sound Hub | **GPIO 43/44** | UART (9600) |
| **Logic LEDs** | Node 3: LED Distro | **GPIO 13** | WS2812B RMT |


> [!IMPORTANT]
> **MESH RECOVERY**: The physical GPIO connections (firmware/production/node-1-dome-motion.yaml:11) are decoupled from the behavior mesh. Even if the ESP-NOW bridge fails, Node 1 remains responsive to raw RC manual override on GPIO 4.


---


[View Master Node Pinout & Wiring Guide](node-pinout-guide.md)