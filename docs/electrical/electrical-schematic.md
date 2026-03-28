# ⚡ Droid Electrical Schematic

This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system. 


---

## 🧠 Interactive System Architecture (Mermaid)
> [!TIP]
> **INTERACTIVE INTERFACE**: Click on any component node to instantly decrypt its technical manual in the databank.

```mermaid
graph TD
    subgraph TRANSMITTERS [2x HOTRC DS-600]
        TX1["TX #1: Body Drive"]:::signal
        TX2["TX #2: Dome Motion"]:::signal
    end

    subgraph POWER_SOURCE [20V DC POWER CORE]
        BAT["DeWalt 20V Battery"]:::power --> LVC["MgcSTEM LVP-R1.5 (40A)"]:::power
        LVC --> FUSE["Main Fuse Bus Bar"]:::power
    end

    subgraph HIGH_POWER_RAIL [20V DRIVE SYSTEM]
        FUSE --> ESC1["Flipsky FSESC 6.7 (Left Drive)"]:::drive
        FUSE --> ESC2["Flipsky FSESC 6.7 (Right Drive)"]:::drive
        FUSE --> SLIP["Slip Ring (Through-Hole)"]:::power
        SLIP --> ESC3["goBILDA 15A ESC (Dome Motor)"]:::drive
    end

    subgraph LOGIC_RAIL [5V LOGIC & AUDIO]
        FUSE --> BUCK1["Mini560 Buck #1 (5.1V)"]:::logic
        BUCK1 --> ESP1["Node 1: Body (ESP32D)"]:::brain
        BUCK1 --> ESP3["Node 3: Dome (ESP32-S3 Mini)"]:::brain
        BUCK1 --> AUDIO["PEMENOL 60W Soundboard"]:::audio
        BUCK1 --> RC1["RC Receiver #1 (Body)"]:::signal
        BUCK1 --> RC2["RC Receiver #2 (Dome)"]:::signal
    end

    subgraph LIGHT_RAIL [5V LIGHTING SYSTEM]
        SLIP --> BUCK2["Mini560 Buck #2 (5.0V)"]:::logic
        BUCK2 --> WLED["Node 2: Lights (ESP32-S3 Mini)"]:::lights
        WLED --> LOGICS["Front/Rear Logics"]:::lights
        WLED --> PSIS["GrnWave PSI Disks"]:::lights
    end

    subgraph SIGNAL_INTERCONNECTS [UNIFIED DROID NERVOUS SYSTEM (UDNS)]
        TX1 -. "2.4GHz" .-> RC1
        TX2 -. "2.4GHz" .-> RC2
        RC1 -- "CH3/4/5 PWM" --> ESP1
        ESP1 -- "9-Wire Trigger" --> AUDIO
        RC2 -- "CH1 PWM" --> ESP3
        ESP3 -- "PWM" --> ESC3
        ESP1 <== "Nervous System UART" ==> WLED
        ESP1 <== "Nervous System UART" ==> ESP3
    end

    subgraph HUD_INTERFACES [MOBILE COMMAND]
        PHONE["Mobile/Tablet"] -- "Web Server / HA" --> ESP1
        PHONE -- "Web Server / HA" --> WLED
        PHONE -- "Web Server / HA" --> ESP3
    end

    %% Direct Markdown-Relative Links for Interactivity
    click BAT "docs/electrical/lvp-r15-manual.md" "Power Core Manual"
    click LVC "docs/electrical/lvp-r15-manual.md" "LVC Manual"
    click ESC1 "docs/electrical/flipsky-fsesc-67-pro-manual.md" "Left Drive ESC Manual"
    click ESC2 "docs/electrical/flipsky-fsesc-67-pro-manual.md" "Right Drive ESC Manual"
    click SLIP "docs/electrical/cnbtr-slip-ring-manual.md" "Slip Ring Manual"
    click AUDIO "docs/electrical/pemenol-60w-voice-manual.md" "Soundboard Specs"
    click PSIS "docs/electrical/grnwave-psi-manual.md" "PSI Logic Manual"
    click ESP1 "firmware/node1-body-brain/body-brain.yaml" "Node 1 Configuration"
    click ESP3 "firmware/node3-dome-motion/dome-motion.yaml" "Node 3 Configuration"
    click WLED "firmware/node2-dome-lights/README.md" "Node 2 Configuration"
    click ESC3 "docs/components/bill-of-materials.md" "Dome ESC Specs"
    click TX1 "docs/electrical/hotrc-ds600-manual.md" "Body Transmitter Manual"
    click TX2 "docs/electrical/hotrc-ds600-manual.md" "Dome Transmitter Manual"

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

### **Node 1: Body Brain (ESP32D Dev Board)**
Master controller for sounds and UDNS coordination.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Status LED** | GPIO2 | Output | Heartbeat Blinker |
| **RC Inputs** | 25, 32, 33 | Input | CH3, CH4, CH5 (PWM) |
| **Sound S1-S9** | 4,5,16,17,18,19,21,22,23 | Output | **Active LOW** (Trigger) |
| **UDNS TX** | GPIO17 | Output | Serial to Dome (Slip Ring Point 3) |
| **UDNS RX** | GPIO16 | Input | Serial from Dome (Slip Ring Point 4) |
| **Web UI** | N/A | WiFi | Port 80 (ESPHome Dashboard) |

### **Node 3: Dome Motion (ESP32-S3 Super Mini)**
Dedicated controller for 360° dome rotation.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **RC CH1 Input** | GPIO1 | Input | From Receiver #2 (Dome Rotation) |
| **Dome ESC** | GPIO2 | Output | PWM Signal (50Hz) to goBILDA ESC |
| **UDNS TX** | GPIO44 | Output | Serial to Body (via Slip Ring) |
| **UDNS RX** | GPIO43 | Input | Serial from Body (via Slip Ring) |

### **Node 2: Dome Lights (ESP32-S3 Super Mini - ESPHome)**
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
