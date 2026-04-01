# Droid Electrical Schematic

This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system. 

![Chassis Electronics Layout](../../assets/chassis-electronics-layout.png)

---

## <i data-lucide="zap"></i> Interactive Schematic & Pinouts

> [!TIP]
> **INTERACTIVE INTERFACE**: Click on any component node to instantly decrypt its technical manual in the Documentation.

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
 POS_FUSE --> AMP["TPA3118 Amplifier"]:::audio
 POS_FUSE --> SLIP1["Slip Ring C1/C2: Motor Line"]:::power
 POS_FUSE --> SLIP2["Slip Ring C3/C4: Logic Line"]:::power

 NEG_BUS --> ESC1
 NEG_BUS --> ESC2
 NEG_BUS --> AMP
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
 RC1 -->|5V OUT| ESP1["MCU 1: Body Audio (S3)"]:::brain
 ESP1 -->|UART| AUDIO["DFPlayer Mini"]:::audio
 
 DOME_ESC -.->|6V BEC ISOLATED| RC2["Dome Receiver (F-06A)"]:::signal

 DOME_WAGOS --> WLED["MCU 2: Dome Lights"]:::lights
 DOME_WAGOS --> ESP3["MCU 3: Dome Motion (S3)"]:::brain
 DOME_WAGOS --> LOGICS["Logic Matrices and PSIs"]:::lights
 end

 subgraph SIGNAL_INTERCONNECTS [WIRELESS AND PWM]
 TX1 -.->|2.4GHz WiFi| RC1
 TX2 -.->|2.4GHz WiFi| RC2
 RC1 -->|PWM| ESC1
 RC1 -->|PWM| ESC2
 RC1 -->|PWM| ESP1
 RC2 -->|PWM| ESP3
 ESP3 -->|PWM| DOME_ESC
 AUDIO -->|Analog| AMP
 ESP3 -.->|ESP-NOW Wireless| ESP1
 ESP3 -.->|ESP-NOW Wireless| WLED
 end

 %% Direct Markdown-Relative Links for Interactivity
 click BAT href "docs/maintenance/battery-runtime-guide.md" "Battery Guide"
 click LVC href "docs/hardware/mgcstem-lvp-r15-manual.md" "LVC Manual"
 click ESC1 href "docs/hardware/flipsky-fsesc-67-pro-manual.md" "Flipsky Manual"
 click AUDIO href "docs/bill-of-materials.md" "DFPlayer Manual"
 click SLIP1 href "docs/architecture/unified-nervous-system.md" "Slip Ring Setup"
 click DOME_BUCK href "docs/bill-of-materials.md" "Buck Converter"
 click RC1 href "docs/hardware/hotrc-f06a-manual.md" "Receiver Manual"
 click ESP1 href "firmware/mcu1-body-controller/README.md" "MCU 1 Code"
 click WLED href "docs/capabilities/lights-and-sounds/led-system.md" "LED System"
 click ESP3 href "firmware/mcu3-motion-controller/README.md" "MCU 3 Code"
 click DOME_ESC href "docs/capabilities/movement/dome-rotation.md" "Dome Rotation"

 classDef power fill:#ff9900,stroke:#333,stroke-width:2px,color:#000
 classDef drive fill:#cc3300,stroke:#fff,color:#fff
 classDef logic fill:#00cccc,stroke:#333,color:#000
 classDef brain fill:#0066cc,stroke:#fff,color:#fff
 classDef audio fill:#99cc00,stroke:#000,color:#000
 classDef signal fill:#ffcc00,stroke:#333,color:#000
 classDef lights fill:#6600cc,stroke:#fff,color:#fff
 classDef reserved fill:#444,stroke:#333,color:#fff
```

---

## <i data-lucide="graduation-cap"></i> Pinout Lookup Tables

### **<i data-lucide="cpu"></i> MCU 1: Body Audio (ESP32-S3 Super Mini)**
Primary controller for sounds and drive system monitoring.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Status LED** | GPIO 47 | Output | S3 Internal Neopixel (Logic) |
| **RC CH3-5** | 4, 5, 6 | Input | Behavioral Triggers from RC1 |
| **DFPlayer TX** | GPIO 17 | Output | To DFPlayer RX |
| **DFPlayer RX** | GPIO 16 | Input | From DFPlayer TX (Optional) |
| **Wireless RX** | N/A | ESP-NOW | Listening for Dome triggers |

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

### **MCU 3: Motion Controller (ESP32-S3 Super Mini)**
Dedicated controller for 360° dome rotation and behavior broadcasting.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **RC CH1 Input** | GPIO 4 | Input | From Receiver #2 (Steering) |
| **Dome ESC** | GPIO 7 | Output | PWM Signal to goBILDA ESC |
| **Wireless TX** | N/A | ESP-NOW | Broadcasting to Body/WLED |
| **Slip Ring C5** | N/A | Reserved | UNUSED / FUTURE EXPANSION |
| **Slip Ring C6** | N/A | Reserved | UNUSED / FUTURE EXPANSION |

---

## Best Practices
* **Common Ground**: All ESP32 grounds, Receiver grounds, and ESC signal grounds **MUST** be tied together at a central star-ground point.
* **Dual Drive: Parallel Signal Isolation**: The drive system uses two Flipsky Mini 6.7 Pro ESCs. Because the remote is in **Mode 1 (Mixed)**, each ESC receives its own PWM/PPM signal independently. To prevent ground loops, **only ESC 1** provides power and a ground reference to the receiver; **ESC 2** is connected via the **Signal Pin only**.
* **Signal Cleanliness**: Since the dome motor is a large DC motor, ensure logic wires are positioned away from the main motor leads to prevent EMI noise.
* **BEC Isolation**: When using the goBILDA 15A ESC, isolate the Red (6V) wire if the logic bus is already powered by a 5V source. The Black (GND) must remain connected for signal reference.
