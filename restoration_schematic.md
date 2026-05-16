# <i data-lucide="zap"></i> Droid Electrical Schematic

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: WEE2-D2 ELECTRICAL** | **VERIFIED AGAINST FIRMWARE v2.12.1**

This document provides a high-fidelity visual and technical map of the Wee2-D2 electrical system.

![Chassis Electronics Layout](assets/chassis-electronics-layout.png)

---

## <i data-lucide="circuit-board"></i> Interactive System Architecture

> [!TIP]
> **INTERACTIVE INTERFACE**: Click any component node to open its technical manual.

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
        POS_FUSE -->|20V| ESC1["Flipsky FSESC (Left)"]:::drive
        POS_FUSE -->|20V| ESC2["Flipsky FSESC (Right)"]:::drive
        POS_FUSE -->|20V| AMP["TPA3118 Amplifier"]:::audio
        POS_FUSE -->|20V| SLIP1["Slip Ring C1/C2: Motor Line"]:::power
        POS_FUSE -->|20V| SLIP2["Slip Ring C3/C4: Logic Line"]:::power

        NEG_BUS --> ESC1
        NEG_BUS --> ESC2
        NEG_BUS --> AMP
        NEG_BUS --> SLIP1
        NEG_BUS --> SLIP2
    end

    subgraph DOME_POWER [DOME POWER via Slip Ring]
        SLIP1 -->|20V| DOME_ESC["goBILDA 15A ESC"]:::drive
        SLIP2 -->|20V| DOME_BUCK["Mini560 Pro Buck (5V)"]:::logic
        DOME_BUCK -->|5V| DOME_WAGOS["2x 5-Port Wagos"]:::power
    end

    subgraph LOGIC_RAIL [5V LOGIC AND SIGNAL]
        ESC1 -->|5V BEC| RC1["Body Receiver (F-06A)"]:::signal
        RC1 -->|5V| NODE2["Node 2: Sound Hub (S3 Mini)"]:::brain
        NODE2 -->|UART| AUDIO["DY-HV20T Audio"]:::audio

        DOME_ESC -.->|6V BEC ISOLATED| RC2["Dome Receiver (F-06A)"]:::signal

        DOME_WAGOS -->|5V| NODE3["Node 3: LED Hub (S3 Mini, WLED-MM)"]:::lights
        DOME_WAGOS -->|5V| NODE1["Node 1: Dome Brain (S3 DevKitC-1)"]:::brain
        DOME_WAGOS -->|5V| LOGICS["Logic Display + PSI Matrices"]:::lights
    end

    subgraph SIGNAL_INTERCONNECTS [WIRELESS + PWM + UART]
        TX1 -.->|2.4GHz| RC1
        TX2 -.->|2.4GHz| RC2
        RC1 -->|PWM| ESC1
        RC1 -->|PWM| ESC2
        RC1 -->|PWM| NODE2
        RC2 -->|PWM| NODE1
        NODE1 -->|PWM| DOME_ESC
        AUDIO -->|Analog| AMP
        NODE1 -.->|ESP-NOW| NODE2
        NODE1 -->|UART JSON| NODE3
    end

    click BAT href "docs/maintenance/battery-runtime-guide.md" "Battery Guide"
    click LVC href "docs/hardware/mgcstem-lvp-r15-manual.md" "LVC Manual"
    click ESC1 href "docs/hardware/flipsky-fsesc-67-pro-manual.md" "Flipsky Manual"
    click AUDIO href "docs/hardware/dfplayer-mini-spec.md" "Audio Module Manual"
    click SLIP1 href "docs/hardware/cnbtr-slip-ring-manual.md" "Slip Ring Manual"
    click DOME_BUCK href "docs/bill-of-materials.md" "Buck Converter"
    click RC1 href "docs/hardware/hotrc-f06a-manual.md" "Receiver Manual"
    click NODE1 href "docs/architecture/node-1-dome-motion.md" "Node 1: Dome Brain"
    click NODE2 href "docs/architecture/node-2-sound-hub.md" "Node 2: Sound Hub"
    click NODE3 href "docs/architecture/node-3-led-distribution.md" "Node 3: LED Hub"
    click DOME_ESC href "docs/capabilities/dome-rotation.md" "Dome Rotation"

    classDef power fill:#ff9900,stroke:#333,stroke-width:2px,color:#000
    classDef drive fill:#cc3300,stroke:#fff,color:#fff
    classDef logic fill:#00cccc,stroke:#333,color:#000
    classDef brain fill:#0066cc,stroke:#fff,color:#fff
    classDef audio fill:#99cc00,stroke:#000,color:#000
    classDef signal fill:#ffcc00,stroke:#333,color:#000
    classDef lights fill:#6600cc,stroke:#fff,color:#fff
```

---

## <i data-lucide="pin"></i> Pinout Lookup Tables

### Node 1: Dome Brain (ESP32-S3 DevKitC-1, N4R2)

Primary autonomy controller. Drives the dome motor and originates every animation. Bridges to WLED over UART and relays ESP-NOW to Node 2.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Dome Motor** | GPIO 7 | PWM Output | To goBILDA 15A ESC |
| **RC CH1 (Steering)** | GPIO 4 | Input | From Receiver 2 |
| **UART to WLED** | GPIO 5 | Output | JSON preset push (115200 baud) |
| **ESP-NOW** | N/A | Wireless | Bidirectional relay with Node 2 |
| **Status LED** | GPIO 48 | Output | S3 internal NeoPixel |

### Node 2: Sound Hub (ESP32-S3 Super Mini)

DY-HV20T audio driver, web dashboard host, BLE bridge endpoint, ESP-NOW relay TX, heartbeat monitor.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **DY-HV20T TX** | GPIO 12 | Output | Audio module RX |
| **DY-HV20T RX** | GPIO 13 | Input | Audio module TX |
| **RC CH3-5** | 4, 5, 6 | Input | Behavioural triggers |
| **ESP-NOW** | N/A | Wireless | Bidirectional relay with Node 1 |
| **BLE** | N/A | Wireless | Slice 1B command bridge from app |
| **Status LED** | GPIO 48 | Output | S3 internal NeoPixel |

### Node 3: LED Hub (ESP32-S3 Super Mini, WLED-MM 14.7.1)

Dedicated 4-strip LED controller. No firmware authored here — runs upstream WLED with project-specific `cfg.json` + `presets.json` + `ledmap.json`.

| Component | Pin (GPIO) | Mode | Notes |
| :--- | :---: | :---: | :--- |
| **Front Logic Display** | 18 | Output | WS2812B, 10x2 matrix |
| **Rear Logic Display** | 19 | Output | WS2812B, 12x2 matrix |
| **Front PSI** | 21 | Output | GrnWave addressable ring |
| **Rear PSI** | 22 | Output | GrnWave addressable ring |
| **UART RX** | 16 | Input | JSON presets from Node 1 |
| **Web UI** | N/A | Wi-Fi | Port 80 (preset selection) |

---

## <i data-lucide="shield-check"></i> Best Practices

- **Common Ground**: every ESP, receiver, and ESC ground ties to a central star-ground point on the negative bus bar.
- **Dual Drive Signal Isolation**: the HOTRC DS-600 runs in Mode 1 (Mixed) — each ESC receives its own PWM. To avoid ground loops, **only ESC 1** powers the receiver; **ESC 2** connects via signal pin only.
- **Signal Cleanliness**: route logic wires away from motor leads to suppress EMI.
- **BEC Isolation**: when using the goBILDA 15A ESC, isolate its 6V red wire if the logic bus is already on 5V. Keep the black ground for signal reference.
