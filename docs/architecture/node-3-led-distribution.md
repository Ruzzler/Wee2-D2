![manual-hero](../../assets/esp32d-dev-board.png)


# <i data-lucide="lightbulb"></i> Node 3: LED Hub

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: LIGHTING HUB** | **MODEL: ESP32D DEVKIT (CLASSIC ESP32)** | **FIRMWARE: WLED 0.15.4 (vid 2508020)**


Node 3 is the dedicated lighting controller for the Wee2-D2 project. It runs **stock WLED 0.15.4** (not WLED-MM, not WLED-AC) on a classic single-core **ESP32D** DevKit board. Node 3 receives JSON preset commands from Node 1 over a one-way UART JSON bridge — no firmware is authored here. All behaviour comes from upstream WLED plus the project's curated `cfg.json` / `presets.json` / `ledmap.json`.


---


## Hardware Specifications

- **Board**: ESP32D DevKit (classic ESP32 WROOM, single-core)
- **Firmware**: WLED 0.15.4 (build id `2508020`)
- **IP**: `192.168.0.39` (DHCP; may change)
- **Voltage**: 5V VIN (dedicated Mini560 Pro 5A buck)
- **Physical location**: dome (above slip ring)


---


## GPIO Pinout

| Assignment | GPIO | Direction | Function |
| :--- | :---: | :--- | :--- |
| **Front PSI** | 16 | OUTPUT (DATA) | 76x WS2812B — Segment 0 (indices 0–75) |
| **Rear PSI** | 17 | OUTPUT (DATA) | 76x WS2812B — Segment 1 (indices 76–151) |
| **Front Logic Display** | 18 | OUTPUT (DATA) | 20x WS2812B — Segment 2 (indices 152–171) |
| **Rear Logic Display** | 19 | OUTPUT (DATA) | 24x WS2812B — Segment 3 (indices 172–195) |
| **UART RX (JSON in)** | 3 (RX0) | INPUT (UART RX) | From Node 1 GPIO 5 @ 115200 baud |

Total: **196 addressable LEDs** across 4 segments.


---


## WLED Configuration Snapshot

| Setting | Value |
| :--- | :--- |
| **Max power** | 3500 mA |
| **LED type** | WS2812B (type 22 in WLED) |
| **Global brightness cap** | 77 / 255 (~30%) — matches CLAUDE.md hard safety constraint |
| **FPS** | 42 |
| **Presets** | 15 (see `Firmware/wee2d2-firmware/firmware/wled/presets.json`) |
| **AudioReactive** | Disabled (prevents GPIO conflicts with the UART RX pin) |
| **UART baud** | 115200 (`"baud": 1152` in WLED config = 115200 / 100) |
| **Handler** | Default WLED Serial0 JSON parser on RX0 (GPIO 3) |

The brightness cap is enforced at two layers: WLED's `bri` ceiling (77/255) AND a per-frame clamp inside Node 1's `set_dome_color` / `set_light_color` helpers (`bri ≤ 76` before the JSON push goes out — added in firmware v2.12.1).


---


## LED Segment Map

```
Index:  0 ─────── 75 │ 76 ────── 151 │ 152 ── 171 │ 172 ── 195
Strip:  Front PSI    │ Rear PSI      │ Front Logic│ Rear Logic
GPIO:   16           │ 17            │ 18         │ 19
Count:  76           │ 76            │ 20         │ 24
```


---


## Trigger Flow

1. Node 1 detects an animation event (e.g. "Cantina Band").
2. Node 1 pushes a JSON frame down the UART wire to Node 3 GPIO 3: `{"on":true,"ps":10}\r\n`.
3. WLED's default Serial0 parser applies the preset instantly.
4. Node 1 sends a `{"v":true}\r\n` heartbeat every 60 s as a keep-alive (WLED's reply is ignored).

Beat-sync color strobes use a richer frame: `{"on":true,"bri":128,"seg":[{"id":0,"col":[[R,G,B]],"fx":0}]}\r\n`.


---


## Wiring

```
          ESP32D DevKit
          ┌────────────────┐
          │ GPIO 16 (DATA) │──────> Front PSI (76 LEDs)
          │ GPIO 17 (DATA) │──────> Rear PSI (76 LEDs)
          │ GPIO 18 (DATA) │──────> Front Logic Display (20 LEDs)
          │ GPIO 19 (DATA) │──────> Rear Logic Display (24 LEDs)
          │                │
Node 1 ──>│ GPIO 3 (RX0)   │  UART RX @ 115200 baud
          │                │
   5V ──> │ VIN            │
  GND ──> │ GND            │
          └────────────────┘

LED Power (separate from logic):
  20V Battery ──> Mini560 Buck ──> 5V @ 5A ──> LED strip VCC rails
  All LED GND tied to common ground bus
```


---


## Maintenance & Debug

- **Web UI**: browse to `192.168.0.39` (or the current DHCP lease) for segment tuning, preset editing, palette work.
- **Serial monitor**: micro-USB on the ESP32D DevKit. UART RX (GPIO 3) is shared with USB-Serial so a connected USB cable may interfere with Node 1's JSON commands — keep USB unplugged during operation.
- **Flickering**: under-voltage on the LED rail (Mini560 sag). Verify 5V holds steady under full-brightness load.
- **Lag**: usually means the JSON frame from Node 1 was dropped — check Node 1's TX heartbeat is firing every 60 s.


---


[View LED System Guide](../capabilities/led-system.md) | [View WLED Configuration Guide](../maintenance/wled-configuration-guide.md) | [View Master Schematic](electrical-schematic.md)
