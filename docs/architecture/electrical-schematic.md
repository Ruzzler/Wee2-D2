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
        
        DOME_ESC -->|5V BEC| RC2["Dome Receiver (F-06A)"]:::signal

        DOME_WAGOS --> ESP3["MCU 3: Dome Motion"]:::brain
        DOME_WAGOS --> WLED["MCU 2: Dome Lights"]:::lights
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
        ESP1 ---|UDNS UART| WLED
        ESP1 ---|UDNS UART| ESP3
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
    click ESP3 href "firmware/mcu3-motion-controller/dome-motion.yaml" "MCU 3 Code"
    click WLED href "docs/capabilities/lights-and-sounds/led-system.md" "LED System"
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

### **MCU 1: Body Controller (ESP32D Dev Board)**
Master controller for sounds and UDNS coordination.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Status LED** | GPIO2 | Output | Heartbeat Blinker |
| **RC Inputs** | 25, 32, 33 | Input | CH3, CH4, CH5 (PWM) |
| **Sound S1-S9** | 4,5,16,17,18,19,21,22,23 | Output | **Active LOW** (Trigger) |
| **UDNS TX** | GPIO17 | Output | Serial to Dome (Slip Ring Point 3) |
| **UDNS RX** | GPIO16 | Input | Serial from Dome (Slip Ring Point 4) |
| **Web UI** | N/A | WiFi | Port 80 (ESPHome Dashboard) |

### **MCU 3: Motion Controller (ESP32-S3 Super Mini)**
Dedicated controller for 360° dome rotation.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **RC CH1 Input** | GPIO1 | Input | From Receiver #2 (Dome Rotation) |
| **Dome ESC** | GPIO2 | Output | PWM Signal (50Hz) to goBILDA ESC |
| **UDNS TX** | GPIO44 | Output | Serial to Body (via Slip Ring) |
| **UDNS RX** | GPIO43 | Input | Serial from Body (via Slip Ring) |

### **MCU 2: Lighting Controller (ESP32-S3 Super Mini - ESPHome)**
Addressable LEDs using the **UDNS Light Interface**.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Logics / PSI** | 1, 2, 3 | Output | Neopixel Data Lines |
| **UDNS TX** | GPIO44 | Output | Shared Serial Bus |
| **UDNS RX** | GPIO43 | Input | Shared Serial Bus |
| **Web UI** | N/A | WiFi | Port 80 (Pattern selection) |

---

## 🛡️ Best Practices
*   **Common Ground**: All ESP32 grounds and Buck Converter grounds **MUST** be tied together at a central star-ground point.
*   **Dual-TX Binding**: Ensure the Body Transmitter and Dome Transmitter (HOTRC DS-600 #1 and #2) are bound to their respective receivers on separate IDs.
*   **Signal Cleanliness**: Since the dome motor is a large DC motor, ensure logic wires are positioned away from the main motor leads to prevent EMI noise.
