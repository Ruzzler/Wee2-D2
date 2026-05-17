# <i data-lucide="cable"></i> Master Node Pinout & Wiring Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: NODE MESH WIRING** | **VERIFIED AGAINST FIRMWARE v2.12.1**

Master wiring reference for the Wee2-D2 distributed node mesh. Integrates verified wire colors, pin assignments, and physical orientation for the ESP32-S3 platform.

---

## 1. Node 2 Pinout (Sound Hub)

Node 2 manages audio triggering, the web dashboard, and ESP-NOW relay. Pins follow the standard S3 Super Mini layout.

| Pin | Wire Color | Role | Function |
| :---: | :--- | :--- | :--- |
| **5V** | Red | Power In | 5V Mini560 Pro buck |
| **GND** | Black | Ground | Common Logic Ground |
| **GPIO 4** | — | RC CH4 | E-Stop relay |
| **GPIO 5** | — | RC CH3 | Volume Up |
| **GPIO 6** | — | RC CH5 | Volume Down |
| **GPIO 12** | Yellow | DY-HV20T TX | Serial command out @ 9600 baud |
| **GPIO 13** | Green | DY-HV20T RX | Serial status in @ 9600 baud |
| **GPIO 47** | — | Status LED | S3 internal NeoPixel |

---

## 2. Audio Stack (DY-HV20T + TPA3118)

Audio triggers are processed locally on Node 2 over UART. The analog signal is amplified via the TPA3118.

### DY-HV20T Audio Module

- **VCC/GND**: 5V logic rail (Mini560 Pro).
- **TX/RX**: crossed to Node 2 GPIO 13/12 (DY-HV20T TX → S3 RX, DY-HV20T RX ← S3 TX).
- **SPK_1/SPK_2**: routed to **TPA3118 input**.

### TPA3118 Amplifier

- **POWER**: 20V positive fuse box (+).
- **GND**: star ground (-).
- **INPUT**: DY-HV20T SPK_1/SPK_2 (or DAC pads).
- **OUTPUT**: Pyle 3.5" full-range speaker.

---

## 3. Receiver Interface (F-06A)

The receiver is powered via the **Slot 5** bridge.

| Wire Color | Rec Slot | ESP Pin | Role |
| :--- | :---: | :---: | :--- |
| **Red (5V)** | Slot 5 (+) | `VIN` | Logic Power |
| **Black (GND)** | Slot 5 (-) | `GND` | Logic Ground |
| **Grey/Black** | Slot 3 (S) | `GPIO 4` | CH3 pulse |
| **Blue/Black** | Slot 4 (S) | `GPIO 5` | CH4 pulse |
| **Purple/Black**| Slot 5 (S) | `GPIO 6` | CH5 pulse |

---

## 4. Drive System: Parallel ESC Wiring (no CAN)

Because the HOTRC DS-600 runs Mode 1 (Mixed), each ESC needs its own PWM. The "high-fidelity signal" method ensures smooth steering at high currents.

| Source | Connection | ESC 1 (Left) | ESC 2 (Right) |
| :--- | :--- | :---: | :---: |
| **Receiver CH1** | Signal (white) | **CONNECT** | — |
| **Receiver CH2** | Signal (white) | — | **CONNECT** |
| **BEC Power** | Red (5V) | **CONNECT** | **ISOLATE** |
| **Signal Reference** | Black (GND) | **CONNECT** | **CONNECT** |

> [!IMPORTANT]
> **Signal Jitter Prevention**: the small black ground wire on ESC 2 provides a clean PWM reference, preventing twitches from motor noise. Main power ground goes to the bus bar.

---

## 5. Dome Distribution: Ganged Wago Hub

To handle 15A+ peak loads (dome motor + LED matrices), slip ring circuits gang at the entry Wagos.

### Positive 20V Hub (Wago A, 5 Port)

1. **IN**: Slip Ring Circuit 1 (20V)
2. **IN**: Slip Ring Circuit 2 (20V) — **GANGED**
3. **OUT**: goBILDA 15A ESC (+)
4. **OUT**: Mini560 Pro Buck 1 (LED power)
5. **OUT**: Mini560 Pro Buck 2 (logic power)

### Ground Star Hub (Wago B, 5 Port)

1. **IN**: Slip Ring Circuit 3 (GND)
2. **IN**: Slip Ring Circuit 4 (GND) — **GANGED**
3. **OUT**: goBILDA 15A ESC (-)
4. **OUT**: Mini560 Pro Buck 1 (GND)
5. **OUT**: Mini560 Pro Buck 2 (GND)

---

## 6. Wireless Interconnect (ESP-NOW)

Node 2 has no physical signal wires through the slip ring — all inter-node communication is wireless.

| Circuit | Role | Logic | Notes |
| :---: | :--- | :--- | :--- |
| **Wireless** | ESP-NOW | 2.4GHz | Behavioural sync from Node 1 |
| **C5/C6** | RESERVED | N/A | Available for future telemetry |

---

## 7. Dome ESC Pulse Calibration (goBILDA 15A)

- **Signal (white)**: connect to **Node 1 GPIO 7**.
- **Ground (black)**: connect to dome logic GND (reference).
- **Voltage (red)**: **isolate** — do not connect if using slip ring 5V logic bus.

---

## 8. Summary Check

- [x] Audio module migrated from DFPlayer Mini to **DY-HV20T** (firmware v2.12.x).
- [x] Body MCU on **ESP32-S3 Super Mini** (Node 2).
- [x] **TPA3118** amplifier powered directly from 20V rail.
- [x] **ESP-NOW** established as the wireless behavioural link.
- [x] **Node 3** standardized on **ESP32-S3 Super Mini** running **WLED 0.15.4**.
- [x] Slip Ring C5/C6 isolated and reserved.
