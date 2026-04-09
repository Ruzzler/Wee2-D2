![manual-hero](../../assets/chassis-electronics-layout.png)


# <i data-lucide="zap"></i> Interactive Electrical Schematic

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: FULL INTERCONNECT** | **VERSION: v2.6.0-STABLE**


This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system. 


---


## 🧠 Interactive System Architecture (Mermaid)
> [!TIP]
> **INTERACTIVE INTERFACE**: Click on any component node to instantly decrypt its technical manual in the databank.


```mermaid
flowchart TD
  subgraph BODY_HUB["BODY COMPARTMENT"]
    subgraph BODY_POWER["PRIMARY POWER GRID"]
      BAT["DeWalt 20V Battery"]:::power ==>|20V| LVC["LVP-R1.5 (40A)"]:::power
      LVC ==>|20V| POS_FUSE["Positive Fuse Box"]:::power
      LVC ==>|GND| NEG_BUS["Negative Bus Bar"]:::power
      BODY_BUCK["Body Logic Buck: Mini560 Pro (5A)"]:::logic
    end

    subgraph BODY_DRIVE["DRIVE & RC STACK"]
      ESC1["FSESC (Left)"]:::drive
      ESC2["FSESC (Right)"]:::drive
      RC1["Body Receiver"]:::signal
    end

    subgraph BODY_SOUND["SOUND HUB"]
      NODE_2["Node 2 (Sound Hub)"]:::brain
      AUDIO["DFPlayer Mini"]:::audio
      AMP["TPA3118 Amp"]:::audio
      SPK2["Pyle 3.5-inch Car Speaker"]:::audio
    end

    POS_FUSE ==>|20V| ESC1
    POS_FUSE ==>|20V| ESC2
    POS_FUSE ==>|20V| AMP
    POS_FUSE ==>|20V| BODY_BUCK
    
    NEG_BUS -.->|GND| ESC1
    NEG_BUS -.->|GND| ESC2
    NEG_BUS -.->|GND| AMP
    NEG_BUS -.->|GND| BODY_BUCK

    BODY_BUCK -->|5V| NODE_2
    BODY_BUCK -->|5V| AUDIO
    ESC1 -->|5V BEC| RC1
    
    RC1 -->|PWM| ESC1
    RC1 -->|PWM| ESC2
  end

  subgraph SLIP_RING_BRIDGE["BRIDGE"]
    POS_FUSE ==>|20V Trunk| SLIP["Slip Ring C1/C2/C3/C4"]:::power
  end

  subgraph DOME_HUB["DOME COMPARTMENT"]
    subgraph DOME_POWER_GRID["DOME POWER GRID"]
      SLIP ==>|20V| DOME_WAGO_20V["20V Wago Hub (2x5)"]:::power
      DOME_WAGO_20V ==>|20V| BUCK_LOGIC["Dome Logic Buck (5A)"]:::logic
      DOME_WAGO_20V ==>|20V| BUCK_LEDS["Dome LED Buck (5A)"]:::logic
      BUCK_LOGIC -->|5V| DOME_WAGO_5V["5V Wago Hub (2x5)"]:::power
    end

    subgraph DOME_LOGIC_HUB["DOME LOGIC HUB"]
      NODE_1["Node 1 (Dome S3)"]:::brain
      NODE_3["Node 3 (Lights WLED)"]:::brain
      RC2["Dome Receiver"]:::signal
    end

    subgraph DOME_MOTION["DOME MOTION STACK"]
      DOME_ESC["goBILDA 1x15A ESC"]:::drive
      DOME_MOTOR["Yellow Jacket Motor (5203 Series)"]:::drive
    end

    subgraph DOME_LIGHTS["CINEMATIC LED ARRAYS"]
      F_PSI["Front PSI LED"]:::lights
      B_PSI["Back PSI LED"]:::lights
      F_LOGIC["Front Logic LED"]:::lights
      B_LOGIC["Rear Logic LED"]:::lights
    end

    DOME_WAGO_20V ==>|20V| DOME_ESC
    DOME_WAGO_5V -->|5V| NODE_1
    DOME_WAGO_5V -->|5V| NODE_3
    DOME_WAGO_5V -->|5V| RC2

    NODE_1 -->|PWM| DOME_ESC
    DOME_ESC ==>|Bullet Connectors| DOME_MOTOR

    BUCK_LEDS -.->|5V Rail| F_PSI
    BUCK_LEDS -.->|5V Rail| B_PSI
    BUCK_LEDS -.->|5V Rail| F_LOGIC
    BUCK_LEDS -.->|5V Rail| B_LOGIC

    NODE_3 -->|GPIO 21| F_PSI
    NODE_3 -->|GPIO 22| B_PSI
    NODE_3 -->|GPIO 18| F_LOGIC
    NODE_3 -->|GPIO 19| B_LOGIC
  end

  subgraph COMM_SIGNAL_MESH["COMMUNICATION & SIGNAL MESH"]
    TX1["TX 1: Body Drive"]:::signal
    TX2["TX 2: Dome Motion"]:::signal
    
    TX1 -.->|2.4GHz| RC1
    TX2 -.->|2.4GHz| RC2
    RC2 -->|PWM| NODE_1
    NODE_1 <-.->|ESP-NOW Mesh| NODE_2
    NODE_1 -->|UART| NODE_3
    
    NODE_2 -->|UART| AUDIO
    AUDIO -->|Analog| AMP
    AMP -->|Audio Out| SPK2
  end

  %% --- ABSOLUTE TERMINATION: Styling & Interaction ---
  
  click BAT href "../maintenance/battery-runtime-guide.md" "Ganged DeWalt 20V Series (4-5Ah Typical)"
  click LVC href "../hardware/mgcstem-lvp-r15-manual.md" "17.5V Cutting Protection Floor"
  click ESC1 href "../hardware/flipsky-fsesc-67-pro-manual.md" "60V/100A Peak ESC"
  click ESC2 href "../hardware/flipsky-fsesc-67-pro-manual.md" "60V/100A Peak ESC"
  click AUDIO href "../capabilities/lights-and-sounds/audio-system.md" "Serial MP3 Module"
  click SLIP href "node-pinout-guide.md" "10A/Circuit Industrial Slip Ring"
  click BODY_BUCK href "../bill-of-materials.md" "Mini560 Pro (5A) Logic"
  click RC1 href "../hardware/hotrc-f06a-manual.md" "Body RC Receiver"
  click RC2 href "../hardware/hotrc-f06a-manual.md" "Dome RC Receiver"
  click NODE_1 href "node-1-dome-motion.md" "ESP32-S3 | Dome Master Movement Controller"
  click NODE_2 href "node-2-sound-hub.md" "ESP32-S3 | Web Control Dashboard & Sound Hub"
  click NODE_3 href "node-3-led-distribution.md" "ESP32D | WLED Lighting Distribution Hub"
  click DOME_ESC href "../hardware/gobilda-motor-manual.md" "15A PWM Peak (30V Capable)"
  click BUCK_LOGIC href "../bill-of-materials.md" "Mini560 Pro (5A) Logic"
  click BUCK_LEDS href "../bill-of-materials.md" "Dedicated High-Current LED Supply (Mini560 Pro)"
  click DOME_MOTOR href "../hardware/gobilda-motor-manual.md" "117 RPM / 12V High-Torque Gearmotor"
  click SPK2 href "../capabilities/lights-and-sounds/audio-system.md" "Pyle 60W RMS / 4 Ohm Driver"

  classDef power fill:#ff9900,stroke:#333,stroke-width:2px,color:#000
  classDef drive fill:#cc3300,stroke:#fff,color:#fff
  classDef logic fill:#00cccc,stroke:#333,color:#000
  classDef brain fill:#0066cc,stroke:#fff,color:#fff
  classDef audio fill:#99cc00,stroke:#000,color:#000
  classDef signal fill:#ffcc00,stroke:#333,color:#000
  classDef lights fill:#6600cc,stroke:#fff,color:#fff
```


---


## 📌 Pinout Lookup Tables


### **Node 2: Sound Hub (ESP32-S3 Super Mini)**
Primary controller for sounds and animation triggers.


| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Status LED** | GPIO 47 | Output | S3 Internal Neopixel (Logic) |
| **RC CH3-5** | 4, 5, 6 | Input | Animation Triggers from RC1 |
| **DFPlayer TX** | GPIO 17 | Output | To DFPlayer RX |
| **DFPlayer RX** | GPIO 16 | Input | From DFPlayer TX (Optional) |
| **Wireless RX** | N/A | ESP-NOW | Listening for Dome triggers |


### **Node 3: Lighting Hub (ESP32-Dev Board - WLED)**
Dedicated high-density addressable LED matrix controller.


| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Front Logic (10x2)** | 18 | Output | Yellow Wire |
| **Rear Logic (12x2)** | 19 | Output | Yellow/Black Striped |
| **Front PSI** | 21 | Output | Green Wire |
| **Back PSI** | 22 | Output | White Wire |
| **UDNS RX (Bus)** | 16 | Input | Serial Command In |
| **Web UI** | N/A | WiFi | Port 80 (Pattern selection) |


### **Node 1: Dome Master (ESP32-S3 Super Mini)**
Dedicated controller for 360° dome rotation and animation broadcasting.


| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **RC CH1 Input** | GPIO 4 | Input | From Receiver #2 (Steering) |
| **Dome ESC** | GPIO 7 | Output | PWM Signal to goBILDA ESC |
| **Wireless TX** | N/A | ESP-NOW | Broadcasting to Body/WLED |
| **Slip Ring C5** | N/A | Reserved | UNUSED / FUTURE EXPANSION |
| **Slip Ring C6** | N/A | Reserved | UNUSED / FUTURE EXPANSION |


---


## 🛡️ Best Practices
*   **Common Ground**: All ESP32 grounds, Receiver grounds, and ESC signal grounds **MUST** be tied together at a central star-ground point.
*   **Dual Drive: Parallel Signal Isolation**: The drive system uses two Flipsky Mini 6.7 Pro ESCs. Because the remote is in **Mode 1 (Mixed)**, each ESC receives its own PWM/PPM signal independently. To prevent ground loops, **only ESC 1** provides power and a ground reference to the receiver; **ESC 2** is connected via the **Signal Pin only**.
*   **Signal Cleanliness**: Since the dome motor is a large DC motor, ensure logic wires are positioned away from the main motor leads to prevent EMI noise.
*   **BEC Isolation**: When using the goBILDA 15A ESC, isolate the Red (6V) wire if the logic bus is already powered by a 5V source. The Black (GND) must remain connected for signal reference.


---


[View Power Architecture](power-architecture.md) | [View Node Pinout Guide](node-pinout-guide.md)