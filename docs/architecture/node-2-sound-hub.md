![manual-hero](../../assets/esp32-s3-super-mini.jpg)


# <i data-lucide="cpu"></i> Node 2: Sound Hub

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: SOUND HUB / DASHBOARD** | **MODEL: ESP32-S3 SUPER MINI** | **FIRMWARE: ESPHome v2.12.1**


Node 2 is the audio controller, web dashboard host, BLE bridge endpoint, and ESP-NOW relay TX for the Wee2-D2 project. It drives the [DY-HV20T audio module](../hardware/dy-hv20t-manual.md) over UART, runs the Neural Command Center dashboard, monitors Node 1 heartbeats, and relays operator commands from the dashboard or the BLE bridge back to Node 1.


---


## Hardware Specifications

- **Processor**: Dual-core ESP32-S3 (Super Mini board)
- **Voltage**: 5V logic rail (Mini560 Pro 5A)
- **Framework**: ESPHome `esp-idf`
- **Production MAC**: `1C:DB:D4:84:73:6C`
- **Physical location**: body / lower chassis (near DY-HV20T + TPA3118)


---


## GPIO Pinout

| Assignment | GPIO | Direction | Function |
| :--- | :---: | :--- | :--- |
| **DY-HV20T TX** | 12 | OUTPUT (UART TX) | Serial commands out @ 9600 baud |
| **DY-HV20T RX** | 13 | INPUT (UART RX) | Status / busy line in @ 9600 baud |
| **RC CH3 (Volume Up)** | 5 | INPUT (RC pulse) | Pulse-from-radio bank A |
| **RC CH4 (E-Stop)** | 4 | INPUT (RC pulse) | Hard-stop relay |
| **RC CH5 (Volume Down)** | 6 | INPUT (RC pulse) | Pulse-from-radio bank C |
| **Slip UART TX (reserved)** | 10 | OUTPUT (TX2) | To Node 1 GPIO 11 — pending wiring |
| **Slip UART RX (reserved)** | 11 | INPUT (RX2) | From Node 1 GPIO 10 — pending wiring |
| **Status LED** | 47 | OUTPUT | Internal NeoPixel |


---


## Communication Model

- **ESP-NOW peer**: Node 1 (`1C:DB:D4:84:61:8C`).
- **Receives from Node 1**:
  - `0x01` — idle chirp request (random `/HAP/`)
  - `0x08 <path>` — Specified Path Playback (v2.9.0 standard)
  - `0xB0` — 5-second heartbeat (drives the dashboard `node1_last_seen_ms` + status card)
  - `0x99` — stop audio
- **Transmits to Node 1** (dashboard relay):
  - `0xA0 <anim_id>` — performance trigger (`0x01`–`0x05`, `0x10`, `0xFF` = e-stop)
  - `0xA1 <preset_id>` — lighting preset override (0–15)
  - `0xA2 <speed_x100>` — dome speed tuning (10–100 = 0.10–1.00)
  - `0xA3 <react_id>` — reaction trigger (`0x06` = wolf whistle, `0x07` = razz, `0x08` = annoyed, `0x09` = thinking, `0x0A` = excited). Codes are **folder-aligned**, not sequential.
- **BLE bridge** (Node 4): Slice 1B commands relayed to Node 2 over BLE for app control: `0x14 Volume`, `0x15 Sound`, `0x16 Display Mode`.


---


## Web Endpoints

- `/dash` — Neural Command Center dashboard (HTML served from flash PROGMEM)
- `/status` — JSON: Node 2 Wi-Fi info + Node 1 heartbeat freshness
- `/events` — Server-Sent Events state stream (ESPHome default)
- `/button/{slug}/press`, `/number/{id}/set?value=N`, `/select/{id}/set?option=X` — entity control


---


## Audio Stack

- **Module**: [DY-HV20T](../hardware/dy-hv20t-manual.md) (UART, 9600 baud, plays MP3 by uppercase SD path)
- **Amplifier**: [TPA3118 60W mono](../hardware/tpa3118-amp-manual.md) in PBTL mode
- **Speaker**: Pyle 3.5" full-range
- **Volume cap**: 26 / 30 (hard safety constraint at the slider, ESP-NOW relay, AND BLE bridge)
- **Boot priority**: 900 — Device Select (SD) frame + saved volume restore before any sound trigger can fire
- **Path discipline**: uppercase enforced by `g_force_uppercase` global; DY-HV20T silently rejects lowercase paths


---


## Maintenance & Debug

- **Wireless logs**: `wee2d2-sound-hub.local` over Wi-Fi
- **Wired logs**: USB-C @ 115200 baud
- **OTA password**: required for wireless updates
- **Audio silent but commands succeed**: verify the boot-priority-900 init sequence ran (Device Select + volume) — most common failure mode after a power blip
- **Mesh bridge lost**: dashboard heartbeat card goes stale after 15 s; Node 1 keeps running autonomously


---


[View DY-HV20T Manual](../hardware/dy-hv20t-manual.md) | [View Audio System](../capabilities/audio-system.md) | [View Master Schematic](electrical-schematic.md)
