# ⚡ Droid Electrical Schematic

This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system. 

![Chassis Electronics Layout](../../assets/chassis-electronics-layout.png)

---

## 🧠 Interactive System Architecture (Mermaid)
> [!TIP]
> **INTERACTIVE INTERFACE**: Click on any component node to instantly decrypt its technical manual in the databank.

```mermaid
flowchart TD
    subgraph TRANSMITTERS [HOTRC DS-600]
        TX1["TX 1: Body Drive"]:::signal
        TX2["TX 2: Motion Controller"]:::signal
    end

    subgraph POWER_SOURCE [20V DC POWER CORE]
        BAT["DeWalt 20V Battery"]:::power --> LVC["MgcSTEM LVP-R1.5 (40A)"]:::power
        LVC --> POS_FUSE["Positive Blade Fuse Box"]:::power
        LVC --> NEG_BUS["Negative Bus Bar (Star Ground)"]:::power
    end

    subgraph HIGH_POWER_RAIL [20V DISTRIBUTION]
        POS_FUSE --> ESC1["Flipsky FSESC (Left)"]:::drive
        POS_FUSE --> ESC2["Flipsky FSESC (Right)"]:::drive
        POS_FUSE --> AUDIO["PEMENOL 60W Soundboard"]:::audio
        POS_FUSE --> SLIP1["Slip Ring C1/C2: Motor Line"]:::power
        POS_FUSE --> SLIP2["Slip Ring C3/C4: Logic Line"]:::power

        NEG_BUS --> ESC1
        NEG_BUS --> ESC2
        NEG_BUS --> AUDIO
        NEG_BUS --> SLIP1
        NEG_BUS --> SLIP2
    end

    subgraph DOME_POWER [DOME POWER Via Slip Ring]
        SLIP1 --> DOME_ESC["goBILDA 15A ESC"]:::drive
        SLIP2 --> DOME_BUCK["Mini560 Pro Buck (5V)"]:::logic
        DOME_BUCK --> DOME_WAGOS["2x 5-Port Wagos"]:::power
    end

    subgraph RECEIVER_MCU_RAIL [5V BEC LOGIC AND SIGNAL]
        ESC1 -->|5V BEC| RC1["Body Receiver (F-06A)"]:::signal
        RC1 -->|5V OUT| ESP1["MCU 1: Body Brain"]:::brain
        
        DOME_ESC -.->|6V BEC ISOLATED| RC2["Dome Receiver (F-06A)"]:::signal

        DOME_WAGOS --> WLED["MCU 2: Dome Lights"]:::lights
        DOME_WAGOS --> ESP3["MCU 3: Dome Motion"]:::brain
        DOME_WAGOS --> LOGICS["Logic Matrices and PSIs"]:::lights
    end

    subgraph SIGNAL_INTERCONNECTS [UART AND PWM CONTROL]
        TX1 -.->|2.4GHz WiFi| RC1
        TX2 -.->|2.4GHz WiFi| RC2
        RC1 -->|PWM| ESC1
        RC1 -->|PWM| ESC2
        RC1 -->|PWM| ESP1
        ESP1 -->|S1-S9 Triggers| AUDIO
        RC2 -->|PWM| ESP3
        ESP3 -->|PWM| DOME_ESC
        ESP1 ---|UDNS UART Bus| ESP3
        ESP1 ---|UDNS UART Bus| WLED
    end

    %% Direct Markdown-Relative Links for Interactivity
    click BAT href "docs/maintenance/battery-runtime-guide.md" "Battery Guide"
    click LVC href "docs/hardware/mgcstem-lvp-r15-manual.md" "LVC Manual"
    click ESC1 href "docs/hardware/flipsky-fsesc-67-pro-manual.md" "Flipsky Manual"
    click AUDIO href "docs/capabilities/lights-and-sounds/audio-system.md" "Audio System"
    click SLIP1 href "docs/architecture/unified-nervous-system.md" "Slip Ring Setup"
    click DOME_BUCK href "docs/bill-of-materials.md" "Buck Converter"
    click RC1 href "docs/hardware/hotrc-f06a-manual.md" "Receiver Manual"
    click ESP1 href "firmware/mcu1-body-controller/body-brain.yaml" "MCU 1 Code"
    click WLED href "docs/capabilities/lights-and-sounds/led-system.md" "LED System"
    click ESP3 href "firmware/mcu3-motion-controller/dome-motion.yaml" "MCU 3 Code"
    click DOME_ESC href "docs/capabilities/movement/dome-rotation.md" "Dome Rotation"

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

### **MCU 1: Body Controller (ESP32D 38-pin Board)**
Master controller for sounds and UDNS coordination.

| Component | Physical Label | Pin (GPIO) | Notes |
| :--- | :---: | :---: | :--- |
| **Status LED** | D2 | GPIO2 | Heartbeat Blinker |
| **RC CH3 Input** | D25 | GPIO25 | Trigger A (Grey/Blk) |
| **RC CH4 Input** | D33 | GPIO33 | Trigger B (Blue/Blk) |
| **RC CH5 Input** | D32 | GPIO32 | Bank Switch (Purple/Blk) |
| **Sound S1-S9** | D4, D5... | 4,5,26,27,18,19,21,22,23 | **Active LOW** Trigger Pins |
| **UDNS TX** | TX2 | GPIO17 | To Dome (Yellow/Black) |
| **UDNS RX** | RX2 | GPIO16 | From Dome (Green/Black) |

### **MCU 2: Lighting Controller (ESP32-Dev Board - WLED)**
Dedicated high-density addressable LED matrix controller.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Front Logic (10x2)** | 18 | Output | Yellow Wire |
| **Rear Logic (12x2)** | 19 | Output | Yellow/Black Striped |
| **Front PSI** | 21 | Output | Green Wire |
| **Back PSI** | 22 | Output | White Wire |
| **UDNS RX (Bus)** | 16 | Input | Serial Command In |
| **Web UI** | N/A | WiFi | Port 80 (Pattern selection) |

### **MCU 3: Motion Controller (ESP32-Dev Board)**
Dedicated controller for 360° dome rotation and UDNS dispatch.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **RC CH1 Input** | GPIO 4 | Input | From Receiver #2 (Steering) |
| **Dome ESC** | GPIO 7 | Output | PWM Signal to goBILDA ESC |
| **UDNS TX** | GPIO 17 | Output | Serial to Body (Yellow/Black) |
| **UDNS RX** | GPIO 16 | Input | Serial from Body (Green/Black) |

---

## 🛡️ Best Practices
*   **Common Ground**: All ESP32 grounds, Receiver grounds, and ESC signal grounds **MUST** be tied together at a central star-ground point.
*   **Dual Drive: Parallel Signal Isolation**: The drive system uses two Flipsky Mini 6.7 Pro ESCs. Because the remote is in **Mode 1 (Mixed)**, each ESC receives its own PWM/PPM signal independently. To prevent ground loops, **only ESC 1** provides power and a ground reference to the receiver; **ESC 2** is connected via the **Signal Pin only**.
*   **Signal Cleanliness**: Since the dome motor is a large DC motor, ensure logic wires are positioned away from the main motor leads to prevent EMI noise.
*   **BEC Isolation**: When using the goBILDA 15A ESC, isolate the Red (6V) wire if the logic bus is already powered by a 5V source. The Black (GND) must remain connected for signal reference.
