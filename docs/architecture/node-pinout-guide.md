![manual-hero](../../assets/esp32-s3-super-mini.jpg)


# <i data-lucide="cpu"></i> Master Node Pinout & Wiring Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: NODE MESH WIRING**


Master wiring reference for Wee2-D2 — what's connected to which pin on each of the three control boards. Treat this as the canonical "where does this wire go" lookup; the per-node pages have the role-by-role context.


---


## 1. Node 1 — Dome Brain (ESP32-S3 DevKitC-1 N4R2)

The autonomy + dome-motion board. See [Node 1 page](node-1-dome-motion.md).

| Pin | Wire Color | What's connected | Role |
| :---: | :--- | :--- | :--- |
| **5V** | Red | goBILDA ESC BEC | Logic power |
| **GND** | Black | Star ground | Logic ground |
| **GPIO 1** | — | RC receiver CH3 | RC button: cycle performance |
| **GPIO 2** | — | RC receiver CH5 | RC button: E-Stop |
| **GPIO 4** | White | RC receiver CH1 | Dome stick (PWM input) |
| **GPIO 5** | Blue | Node 3 GPIO 3 | One-way wired link to LED hub |
| **GPIO 6** | — | RC receiver CH4 | RC button: random reaction |
| **GPIO 7** | Yellow | goBILDA 15A ESC signal | Dome motor PWM out |
| **GPIO 47** | — | Internal | Status LED |


---


## 2. Node 2 — Sound Hub (ESP32-S3 Super Mini)

The audio + dashboard board. See [Node 2 page](node-2-sound-hub.md).

| Pin | Wire Color | What's connected | Role |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Mini560 Pro 5A buck | Logic power |
| **GND** | Black | Star ground | Logic ground |
| **GPIO 4** | — | RC receiver CH4 | RC button: E-Stop |
| **GPIO 5** | — | RC receiver CH3 | RC button: Volume Up |
| **GPIO 6** | — | RC receiver CH5 | RC button: Volume Down |
| **GPIO 12** | Yellow | DY-HV20T RX | Audio command line out |
| **GPIO 13** | Green | DY-HV20T TX | Audio status line in |
| **GPIO 47** | — | Internal | Status LED |


---


## 3. Node 3 — LED Hub (ESP32D DevKit, runs stock WLED)

The lighting board. See [Node 3 page](node-3-led-distribution.md).

| Pin | Wire Color | What's connected | Role |
| :---: | :--- | :--- | :--- |
| **VIN (5V)** | Red | Mini560 Pro LED rail | Logic power |
| **GND** | Black | Star ground | Logic ground |
| **GPIO 3 (RX0)** | Blue | Node 1 GPIO 5 | Command line in |
| **GPIO 16** | — | Front PSI strip data | 76 LEDs |
| **GPIO 17** | — | Rear PSI strip data | 76 LEDs |
| **GPIO 18** | — | Front Logic data | 20 LEDs (10x2 matrix) |
| **GPIO 19** | — | Rear Logic data | 24 LEDs (12x2 matrix) |

Total: **196 addressable LEDs** across 4 segments.


---


## 4. Audio Stack Wiring

The audio path is fully analog after the DY-HV20T module:

- Node 2 GPIO 12 → DY-HV20T RX (commands)
- Node 2 GPIO 13 ← DY-HV20T TX (status)
- DY-HV20T SPK_1 / SPK_2 → TPA3118 amplifier inputs
- TPA3118 power → 20V positive fuse box
- TPA3118 GND → star ground
- TPA3118 output → Pyle 3.5" speaker

See the [DY-HV20T Manual](../hardware/dy-hv20t-manual.md) for module-level detail.


---


## 5. RC Receiver Wiring (HOTRC F-06A)

Two receivers — one for body drive (paired to TX1), one for dome (paired to TX2). The dome receiver feeds Node 1; the body receiver feeds Node 2 + the body ESCs.

| Wire Color | Receiver slot | Where it goes |
| :--- | :---: | :--- |
| Red (5V) | Slot 5 (+) | Receiver logic power |
| Black (GND) | Slot 5 (-) | Receiver logic ground |
| Signal (Grey/Black) | Slot 3 (S) | RC CH3 — varies per receiver |
| Signal (Blue/Black) | Slot 4 (S) | RC CH4 — varies per receiver |
| Signal (Purple/Black) | Slot 5 (S) | RC CH5 — varies per receiver |


---


## 6. Dome Power Distribution (Ganged Wago Hubs)

Two ganged Wago hubs sit at the dome side of the slip ring.

### 20V High-Power Hub (5-port)
1. **IN**: Slip Ring Circuit 1 (20V)
2. **IN**: Slip Ring Circuit 2 (20V) — ganged for current capacity
3. **OUT**: goBILDA 15A speed controller
4. **OUT**: Mini560 Pro Buck — dome logic rail
5. **OUT**: Mini560 Pro Buck — dome LED rail

### 5V Logic Hub (5-port)
1. **IN**: Mini560 Pro logic buck
2. **OUT**: Node 1 (Dome Brain)
3. **OUT**: Node 3 (LED Hub) VIN
4. **OUT**: HOTRC dome receiver
5. **OUT**: reserved / expansion

### Ground Hub (5-port)
1. **IN**: Slip Ring Circuit 3 (GND)
2. **IN**: Slip Ring Circuit 4 (GND) — ganged
3. **OUT**: goBILDA 15A speed controller (-)
4. **OUT**: Mini560 Pro Buck 1 (GND)
5. **OUT**: Mini560 Pro Buck 2 (GND)


---


## 7. Wireless Links

| Link | What | Endpoints |
| :--- | :--- | :--- |
| **2.4 GHz mesh** | Direct radio link (no Wi-Fi router needed) | Node 1 ↔ Node 2 |
| **Wired serial** | Single-wire one-way | Node 1 → Node 3 |
| **Bluetooth Low Energy** | Operator app control | BLE bridge ↔ Node 2 |


---


[View Power Architecture](power-architecture.md) | [View Interactive Schematic](electrical-schematic.md) | [View Node Mesh Architecture](node-mesh.md)
