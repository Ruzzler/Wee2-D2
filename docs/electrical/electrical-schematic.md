# ⚡ Droid Electrical Schematic

This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system. 

## 🗺️ Visual HUD Block Diagram
![Imperial HUD Schematic](assets/schematic_hero.png)

---

## 🧠 System Architecture (Mermaid)

```mermaid
graph TD
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
        BUCK1 --> ESP1["Node 1: Body Brain"]:::brain
        BUCK1 --> ESP3["Node 3: Dome Motion"]:::brain
        BUCK1 --> AUDIO["DY-HL50T Soundboard"]:::audio
        BUCK1 --> RC1["RC Receiver (Body)"]:::signal
        BUCK1 --> RC2["RC Receiver (Dome)"]:::signal
    end

    subgraph LIGHT_RAIL [5V LIGHTING SYSTEM]
        SLIP --> BUCK2["Mini560 Buck #2 (5.0V)"]:::logic
        BUCK2 --> WLED["Node 2: Dome Lights (WLED)"]:::lights
        WLED --> LOGICS["Front/Rear Logics"]:::lights
        WLED --> PSIS["GrnWave PSI Disks"]:::lights
    end

    subgraph SIGNAL_INTERCONNECTS [SIGNAL & TRIGGERS]
        RC1 -- "CH3/4/5 PWM" --> ESP1
        ESP1 -- "9-Wire Trigger" --> AUDIO
        RC2 -- "CH1 PWM" --> ESP3
        ESP3 -- "PWM" --> ESC3
        ESP1 -- "Angry/Red Link" --> WLED
    end

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

### **Node 1: Body Brain (ESP32)**
Used for RC input interpretation and soundboard triggering.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Status LED** | GPIO2 | Output | Heartbeat Blinker |
| **RC CH3 Input** | GPIO25 | Input | PWM Pulse Width |
| **RC CH4 Input** | GPIO32 | Input | PWM Pulse Width |
| **RC CH5 Input** | GPIO33 | Input | Bank Cycle Switch |
| **Sound S1-S9** | 4,5,16,17,18,19,21,22,23 | Output | **Active LOW** (Trigger) |
| **Angry Link** | GPIO13 | Output | To Node 2 Button Input |

### **Node 3: Dome Motion (ESP32)**
Controls the 360° dome rotation motor.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **RC Steering** | GPIO4 | Input | From Receiver #2 |
| **Dome ESC** | GPIO18 | Output | PWM Signal (50Hz) |

### **Node 2: Dome Lights (WLED)**
Addressable LEDs for logics and PSIs.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Front Logic** | GPIO16 | Output | Data Pin A |
| **Rear Logic** | GPIO2 | Output | Data Pin B |
| **Angry Link** | GPIO4 | Input | From Node 1 Trigger |

---

## 🛡️ Best Practices
*   **Common Ground**: All ESP32 grounds and Buck Converter grounds **MUST** be tied together at a central star-ground point.
*   **Signal Cleanliness**: Since the dome motor is a large DC motor, ensure logic wires are positioned away from the main motor leads to prevent EMI noise.
