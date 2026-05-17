![manual-hero](../../assets/esp32-s3-super-mini.jpg)


# <i data-lucide="cpu"></i> Node 1: Dome Brain

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: DOME MOTION + ANIMATION FRAMEWORK** | **MODEL: ESP32-S3 DEVKITC-1 (N4R2)** | **FIRMWARE: ESPHome v2.12.1**


Node 1 is the autonomy and motion master for the Wee2-D2 project. It hosts the [Animation Framework](../capabilities/animation-framework.md), drives the dome motor over PWM, reads the HOTRC stick + button channels, bridges to Node 3 over UART JSON for lighting presets, and is the ESP-NOW relay receiver for dashboard commands from Node 2.


---


## Hardware Specifications

- **Board**: ESP32-S3 **DevKitC-1 N4R2** (4 MB flash, 2 MB PSRAM)
- **MAC**: `1C:DB:D4:84:61:8C`
- **Voltage**: 5V from goBILDA ESC BEC (5.1V)
- **Framework**: ESPHome `esp-idf`
- **Physical location**: dome (on the dome motor platform)
- **USB**: USB-C with serial console (accessible through dome hatch for OTA fallback)


---


## GPIO Pinout

| Assignment | GPIO | Direction | Function |
| :--- | :---: | :--- | :--- |
| **Dome Servo/ESC** | 7 | OUTPUT (PWM, 50 Hz) | To goBILDA 15A ESC signal wire |
| **RC Stick (Dome L/R)** | 4 | INPUT (PWM) | HOTRC Receiver CH1 |
| **RC CH3 (Performance Cycle)** | 1 | INPUT (RC pulse) | Cycle through perfs |
| **RC CH4 (Random Reaction)** | 6 | INPUT (RC pulse) | Trigger random reaction |
| **RC CH5 (E-Stop)** | 2 | INPUT (RC pulse) | Hard-stop relay |
| **WLED Command Bus (TX)** | 5 | OUTPUT (UART TX) | To Node 3 GPIO 3 @ 115200 baud |
| **Slip UART TX (reserved)** | 10 | OUTPUT (TX2) | To Node 2 GPIO 11 — pending wiring |
| **Slip UART RX (reserved)** | 11 | INPUT (RX2) | From Node 2 GPIO 10 — pending wiring |
| **Status LED** | 47 | OUTPUT | Internal NeoPixel |


---


## Communication Model

- **ESP-NOW peer**: Node 2 (`1C:DB:D4:84:73:6C` production; `1C:DB:D4:84:77:70` test board)
- **Transmits to Node 2**:
  - `0x01` — idle chirp request
  - `0x08 <path>` — Specified Path Playback (v2.9.0 standard)
  - `0xB0` — 5-second heartbeat (drives dashboard status card)
  - `0x99` — stop audio
- **Receives from Node 2** (dashboard relay):
  - `0xA0 <anim_id>` — performance trigger (`0x01`–`0x05`, `0x10`, `0xFF` = e-stop)
  - `0xA1 <preset_id>` — lighting preset override (0–15)
  - `0xA2 <speed_x100>` — dome speed tuning (10–100 = 0.10–1.00)
  - `0xA3 <react_id>` — reaction trigger (folder-aligned, see [Animation Framework](../capabilities/animation-framework.md))
- **UART out to Node 3**: one-way JSON @ 115200 baud (lighting preset push + 60 s heartbeat)


---


## Animation Framework

Node 1 originates every animation. Tier model:

- **T0** — life / micro (idle twitches, ambient sweeps, never locks)
- **T1** — reactions (5 s cap, locks `is_animating`)
- **T2** — performances (20–190 s, locks with watchdog buffer)

See [Animation Framework](../capabilities/animation-framework.md) for the full tier contract, wrapper scripts, mood system, idle escalation ladder, and music cue auto-choreography.

Production performances (as of v2.12.1): `perf_idle`, `perf_angry`, `perf_dance`, `perf_cantina`, `perf_birthday`, `perf_imperial`. Production reactions: `react_wolf_whistle`, `react_razz`, `react_annoyed`, `react_thinking`, `react_excited`.


---


## Safety Limits

| Constraint | Value | Source |
| :--- | :--- | :--- |
| **RC transient mute on boot** | 10-pulse window | Boot priority 900 in firmware |
| **Mesh bridge timeout** | > 100 ms loss → motion pause | `safety` ESPHome block |
| **WLED `bri` clamp** | ≤ 76 (≤ 30%) | `set_dome_color` / `set_light_color` helpers (v2.12.1) |
| **Animation watchdog** | 2 s ticker force-releases stuck `is_animating` | `release_animation_lock` |


---


## Maintenance & Debug

- **Wireless logs**: `wee2d2-dome-master.local` over Wi-Fi
- **Wired logs**: USB-C @ 115200 baud
- **OTA password**: required for wireless updates
- **Heartbeat**: 5 s ping to Node 2 — dashboard `Node 1 online` flag goes red if missed > 15 s
- **Logger level**: `DEBUG` in production (visible verbose state for field troubleshooting)


---


[View Animation Framework](../capabilities/animation-framework.md) | [View Master Schematic](electrical-schematic.md) | [View Power Architecture](power-architecture.md)
