![manual-hero](../../assets/esp32-s3-super-mini.jpg)


# <i data-lucide="cpu"></i> Master Node Pinout & Wiring Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: NODE MESH WIRING** | **VERIFIED AGAINST FIRMWARE v2.12.1**


Master wiring reference for the Wee2-D2 distributed node mesh. All pin assignments, wire colors, and hardware interfaces verified against `Firmware/wee2d2-firmware/docs/hardware/HARDWARE-PINOUTS.md` at firmware v2.12.1.


---


## 1. Node 1 — Dome Brain (ESP32-S3 DevKitC-1 N4R2)

Drives the dome motor, reads HOTRC stick + buttons, originates every animation, bridges to Node 3 over UART JSON, and is the ESP-NOW peer of Node 2.

| Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | goBILDA ESC BEC (5.1V) |
| **GND** | Black | Ground | Common logic ground (star) |
| **GPIO 1** | — | RC CH3 | Performance Cycle (RC button A) |
| **GPIO 2** | — | RC CH5 | E-Stop (RC button C) |
| **GPIO 4** | White | RC CH1 | Dome stick PWM input |
| **GPIO 5** | Blue | WLED TX | One-way UART JSON to Node 3 GPIO 3 @ 115200 baud |
| **GPIO 6** | — | RC CH4 | Random Reaction (RC button B) |
| **GPIO 7** | Yellow | Dome PWM | To goBILDA 15A ESC signal wire (50 Hz) |
| **GPIO 10** | — | SLIP UART TX | To Node 2 GPIO 11 — *pending wiring* |
| **GPIO 11** | — | SLIP UART RX | From Node 2 GPIO 10 — *pending wiring* |
| **GPIO 47** | — | Status LED | Internal NeoPixel |


---


## 2. Node 2 — Sound Hub (ESP32-S3 Super Mini)

Drives the DY-HV20T audio module, hosts the web dashboard, monitors Node 1 heartbeats, relays dashboard + BLE commands.

| Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5.0V Mini560 Pro buck |
| **GND** | Black | Ground | Common logic ground (star) |
| **GPIO 4** | — | RC CH4 | E-Stop |
| **GPIO 5** | — | RC CH3 | Volume Up |
| **GPIO 6** | — | RC CH5 | Volume Down |
| **GPIO 12** | Yellow | DY-HV20T TX | UART command out @ 9600 baud |
| **GPIO 13** | Green | DY-HV20T RX | UART status in @ 9600 baud |
| **GPIO 10** | — | SLIP UART TX | To Node 1 GPIO 11 — *pending wiring* |
| **GPIO 11** | — | SLIP UART RX | From Node 1 GPIO 10 — *pending wiring* |
| **GPIO 47** | — | Status LED | Internal NeoPixel |


---


## 3. Node 3 — LED Hub (ESP32D DevKit, classic ESP32 running WLED 0.15.4)

Stock WLED 0.15.4 on a classic single-core ESP32D. No custom firmware — only `cfg.json` / `presets.json` / `ledmap.json`. Receives JSON preset commands from Node 1.

| Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **VIN (5V)** | Red | Power In | Mini560 Pro 5A buck (dedicated LED rail also feeds VIN) |
| **GND** | Black | Ground | Common logic ground (star) |
| **GPIO 3** (RX0) | — | UART JSON RX | From Node 1 GPIO 5 @ 115200 baud |
| **GPIO 16** | — | Data Out | Front PSI — 76x WS2812B |
| **GPIO 17** | — | Data Out | Rear PSI — 76x WS2812B |
| **GPIO 18** | — | Data Out | Front Logic Display — 20x WS2812B (10x2 matrix) |
| **GPIO 19** | — | Data Out | Rear Logic Display — 24x WS2812B (12x2 matrix) |

Total: **196 addressable LEDs** across 4 segments. Max power 3500 mA. Brightness capped at 77/255 (~30%).


---


## 4. Audio Stack (DY-HV20T + TPA3118)

- **Node 2 GPIO 12** → **DY-HV20T RX** (commands out)
- **Node 2 GPIO 13** ← **DY-HV20T TX** (status in)
- **DY-HV20T SPK_1 / SPK_2** → **TPA3118 input (+/-)** (line-level analog)
- **TPA3118 power** → 20V positive fuse box
- **TPA3118 GND** → star ground (-)

See the [DY-HV20T Manual](../hardware/dy-hv20t-manual.md) for protocol detail, SD card layout, and boot priority requirements.


---


## 5. Receiver Interface (HOTRC F-06A)

Two receivers: RX1 for body drive (paired to TX1), RX2 for dome (paired to TX2). The wiring below is one slot pattern per receiver.

| Wire Color | Receiver Slot | Connects To | Role |
| :--- | :---: | :---: | :--- |
| Red (5V) | Slot 5 (+) | `5V / VIN` | Logic power |
| Black (GND) | Slot 5 (-) | `GND` | Logic ground |
| Grey/Black | Slot 3 (S) | Node 1 GPIO 4 (RX2 dome stick) | CH1 PWM |
| Blue/Black | Slot 4 (S) | Node 2 GPIO 5 (RX1 buttons) | CH3 pulse |
| Purple/Black | Slot 5 (S) | Node 1 GPIO 2 (RX2 E-Stop) | CH5 pulse |


---


## 6. Dome Power Distribution (Ganged Wago Hubs)

Two ganged Wago hubs at the dome side of the slip ring.

### 20V High-Power Hub (5-port)

1. **IN**: Slip Ring Circuit 1 (20V)
2. **IN**: Slip Ring Circuit 2 (20V) — ganged for current capacity
3. **OUT**: goBILDA 15A Speed Controller
4. **OUT**: Mini560 Pro Buck — Dome Logic rail
5. **OUT**: Mini560 Pro Buck — Dome LED rail

### 5V Logic Hub (5-port)

1. **IN**: Mini560 Pro (Logic rail)
2. **OUT**: Node 1 (Dome Brain)
3. **OUT**: Node 3 (LED Hub) VIN
4. **OUT**: HOTRC F-06A receiver
5. **OUT**: reserved / expansion

### Ground Hub (5-port)

1. **IN**: Slip Ring Circuit 3 (GND)
2. **IN**: Slip Ring Circuit 4 (GND) — ganged
3. **OUT**: goBILDA 15A Speed Controller (-)
4. **OUT**: Mini560 Pro Buck 1 (GND)
5. **OUT**: Mini560 Pro Buck 2 (GND)


---


## 7. Wireless Interconnects

| Link | Protocol | Endpoints |
| :--- | :--- | :--- |
| **ESP-NOW** | 2.4 GHz unicast mesh | Node 1 ↔ Node 2 (bidirectional) |
| **UART JSON** | 115200 baud, wired | Node 1 GPIO 5 → Node 3 GPIO 3 (one-way) |
| **BLE** | Slice 1B bridge | Node 4 ↔ Node 2 (app commands relayed in) |

The legacy UDNS UART bus through the slip ring (GPIO 16/17 prior to v1.8.0) is **decommissioned**. Slip ring circuits C5 / C6 are reserved for future telemetry.


---


[View Power Architecture](power-architecture.md) | [View Interactive Schematic](electrical-schematic.md) | [View Node Mesh Architecture](node-mesh.md)
