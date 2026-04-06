# <i data-lucide="settings"></i> Node 1: Dome Motion

> **TECHNICAL SPECIFICATIONS** | **ESPHome v3** | **ESP32-S3 Super Mini** | **Behavioral Master**

| Component | Detail |
| :--- | :--- |
| **Node ID** | **1** |
| **Role** | Behavioral Master & Dome Motion Controller |
| **Source Code** | [`node-1-dome-motion.yaml`](../../firmware/production/node-1-dome-motion.yaml) |
| **Visual ID** | ![Node 1 Master](../../assets/esp32-s3-super-mini.jpg) |

## Core Features

- **Behavioral Orchestration**: Reads raw RC steering. Captures ESP-NOW dashboard triggers (`0xA0`, `0xA1`, `0xA2`) relayed from Node 2.
- **ESP-NOW Heartbeat**: Broadcasts a 5-second `0xB0` continuous heartbeat back to the Dashboard to maintain mesh health validation.
- **Dynamic Scripts**: Includes built-in behaviors for "Scan Patrol", "Animation Logic", and "WLED Sync Heartbeats" (via UART).
- **Safety Interlocks**:
 - **Boot/Shutdown Stop**: Forces speed to 0% on controller power cycles.
 - **Auto-Detach**: Motor controller signal detaches after 5s of inactivity to prevent hum.

## Pinout Configuration

| Connection | ESP32 Pin | Wire Color | Logic |
| :--- | :---: | :--- | :--- |
| **RC CH1 (Steer)** | GPIO 4 | Yellow | PWM Input (Pull-Down) |
| **Wireless Link** | Ch. 11 | ESP-NOW | Mesh Heartbeat / Automation Rx |
| **ESC PWM Out** | GPIO 7 | / White/Blue | PWM Output to goBILDA |
| **WLED Sync** | GPIO 5 | Blue | Single Wire UART TX (JSON) |

## ESP32-S3 Engineering Implementation

The following hardware-specific constraints are unique to the S3 Super Mini platform and were identified during the domehub integration audit:

### 1. S3-Specific Constraints (Critical)

- **RMT Memory Allocation**: The ESP32-S3 has exactly 192 RMT symbols for timing. When driving dual WS2812 strips, `rmt_symbols: 96` must be explicitly set for each strip to split hardware memory equally and prevent CPU timeout crashes.
- **GPIO 9 Flash Conflict**: GPIO 9 is internally tied to the board's flash memory data bus. Do not use this pin for high-speed PWM or data signals as it will interfere with the bootloader.
- **Wi-Fi Antenna Saturation**: To prevent disconnects on the compact Super Mini board, transmit power is limited to `8.5dB`.

### 2. General ESPHome & Electrical Standards

- **Update Intervals**: ESPHome's default 60-second update interval is overridden to `50ms` for the `pulse_width` sensor to ensure real-time RC responsiveness.
- **Log Noise Suppression**: A `delta: 20.0` filter is applied to the RC stick sensor to ignore micro-fluctuations in the analog signal.
- **Common Grounds**: All components in the dome MUST share a common ground reference with the ESP32 for reliable data transmission.
- **Signal Stabilization**: `mode: INPUT_PULLDOWN` is used on the RC stick's GPIO pin to prevent floating signals and jitter.