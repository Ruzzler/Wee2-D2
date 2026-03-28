# ⚡ Droid Electrical Schematic

This document provides a high-fidelity map of the Wee2-D2 electrical system, including power distribution and signal routing.

## 🧠 System Architecture (Mermaid)

```mermaid
graph TD
    subgraph POWER_SOURCE [20V DC POWER]
        BAT["DeWalt 20V Battery"] --> LVC["MgcSTEM LVP-R1.5 (40A)"]
        LVC --> FUSE["Main Fuse Bus Bar"]
    end

    subgraph HIGH_POWER_RAIL [20V DRIVE RAIL]
        FUSE --> ESC1["Flipsky FSESC 6.7 (Left Drive)"]
        FUSE --> ESC2["Flipsky FSESC 6.7 (Right Drive)"]
        FUSE --> SLIP["Slip Ring (Through-Hole)"]
        SLIP --> ESC3["goBILDA 15A ESC (Dome Motor)"]
    end

    subgraph LOGIC_RAIL [5V LOGIC RAIL]
        FUSE --> BUCK1["Mini560 Buck #1 (5.1V)"]
        BUCK1 --> ESP1["Node 1: Body Brain"]
        BUCK1 --> ESP3["Node 3: Dome Motion"]
        BUCK1 --> AUDIO["DY-HL50T Soundboard"]
        BUCK1 --> RC1["RC Receiver (Body)"]
        BUCK1 --> RC2["RC Receiver (Dome)"]
    end

    subgraph LIGHT_RAIL [5V LIGHTING RAIL]
        SLIP --> BUCK2["Mini560 Buck #2 (5.0V)"]
        BUCK2 --> WLED["Node 2: Dome Lights (WLED)"]
        WLED --> LOGICS["Front/Rear Logics"]
        WLED --> PSIS["GrnWave PSI Disks"]
    end

    subgraph SIGNAL_INTERCONNECTS [SIGNAL & TRIGGERS]
        RC1 -- "CH3/4/5 PWM" --> ESP1
        ESP1 -- "9-Wire Trigger" --> AUDIO
        RC2 -- "CH1 PWM" --> ESP3
        ESP3 -- "PWM" --> ESC3
        ESP1 -- "Angry/Red Link" --> WLED
    end

    style BAT fill:#ff9900,stroke:#333,stroke-width:2px
    style LVC fill:#ffcc00,stroke:#333
    style FUSE fill:#cc3300,stroke:#fff
    style BUCK1 fill:#00cccc,stroke:#333
    style BUCK2 fill:#00cccc,stroke:#333
    style WLED fill:#6600cc,stroke:#fff
    style ESP1 fill:#0066cc,stroke:#fff
    style ESP3 fill:#0066cc,stroke:#fff
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
| **Angry Link**| GPIO4 | Input | From Node 1 Trigger |

---

## 🛡️ Best Practices
*   **Common Ground**: All ESP32 grounds and Buck Converter grounds **MUST** be tied together at a central star-ground point.
*   **Signal Cleanliness**: Since the dome motor is a large DC motor, ensure logic wires are positioned away from the main motor leads to prevent EMI noise.
