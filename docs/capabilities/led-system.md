# <i data-lucide="lightbulb"></i> Cinematic LED System

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: CINEMATIC LIGHTING** | **MODEL: WLED 0.15.4 / GRNWAVE PSI**

This guide covers the LED architecture: WS2812B / GrnWave hardware, WLED preset ledger, UART JSON bridge from Node 1, and physical pin mapping. All references verified against firmware v2.12.1.

---

## Hardware Components (LED Hub)

The lighting system is decentralized across the dome using addressable LEDs. Powered by a dedicated Mini560 Pro 5A buck to prevent voltage drops during bright patterns.

- **Controller**: Node 3 — LED Hub (ESP32D DevKit, classic ESP32)
- **Framework**: WLED 0.15.4 (vid `2508020`, stock — not WLED-MM, not WLED-AC)
- **Primary Arrays**: GrnWave PSI logics + WS2812B Logic Display matrices
- **Total LEDs**: 196 across 4 segments (76 + 76 + 20 + 24)
- **Data Protocol**: UART JSON bridge from Node 1 (115200 baud) on Node 3 GPIO 3 (RX0)
- **Global brightness cap**: 77/255 (~30%) — enforced by WLED config AND per-frame in Node 1 helpers

---

## Power Constraints

> [!CAUTION]
> The GrnWave PSI matrices will fail if exposed to more than 5.2V. The dual-buck strategy isolates high-current LED sweeps from ESP32 logic pins.

A dedicated Mini560 Pro 5A buck on the 20V ganged Wago hub serves only the dome LED rail.

**Firmware-level guard:** all `set_dome_color` / `set_light_color` calls clamp `bri` to ≤ 76 (≤30%) before sending to WLED, enforcing the CLAUDE.md hard safety constraint at the per-frame ceiling (WLED ABL remains the secondary current guard).

---

## Cinematic Lighting Presets

Wee2-D2 ships **15 hard-coded cinematic logic states** stored as WLED presets on Node 3. These can be triggered manually via the [Web Control Dashboard](web-control-dashboard.md) or automatically during animations.

| ID | Preset Name | Visual Profile | Operational Context |
| :---: | :--- | :--- | :--- |
| **0** | All Off | Total blackout | Power save / stealth |
| **1** | 1977 Idle | Classic blue/teal scroll | Standard operation |
| **2** | Neural Proc | Rapid cyan logic pulse | Thinking / calculating |
| **3** | Alert Red | Synchronized red logic flash | Emergency / combat |
| **4** | Legacy Mode | Static 1977 colors | Low power |
| **5** | Front Only | Front logic only (20 px) | Component test |
| **6** | Rear Only | Rear logic only (24 px) | Component test |
| **7** | PSI Scan | Dual-PSI alternating pulse | Sensor sweep |
| **8** | Data Transfer | High-speed white logic jitter | Link established |
| **9** | Leia Message | Dim blue logic flicker | Holo-projection playback |
| **10** | Disco Mode | RGB rainbow cycle | Dance / celebration |
| **11** | Stealth | Dimmed single-pixel logic | Night ops |
| **12** | Startup Seq | Cascading logic wipe | System boot |
| **13** | Malfunction | Random red/orange static | System error |
| **14** | Celebration | Gold/white shimmer | Victory / taunt |
| **15** | Imperial March | Slow red logic fade | Opposing force detected |

Canonical preset definitions live in `Firmware/wee2d2-firmware/firmware/wled/presets.json`.

---

## Physical LED Mapping

LEDs split across four data lines off Node 3:

| Display | Type | Configuration | GPIO | Segment (indices) |
| :--- | :--- | :--- | :---: | :--- |
| **Front PSI** | GrnWave | Circular (76 px) | 16 | Seg 0 (0–75) |
| **Rear PSI** | GrnWave | Circular (76 px) | 17 | Seg 1 (76–151) |
| **Front Logic** | WS2812B | 10x2 matrix (20 px) | 18 | Seg 2 (152–171) |
| **Rear Logic** | WS2812B | 12x2 matrix (24 px) | 19 | Seg 3 (172–195) |

---

## WLED 2D Setup

To get cinematic animations, the WLED interface uses 2D matrix segments.

1. Even though the Rear Logic is physically split into two square windows, treating it as one consecutive 10x2 strip in WLED lets scanning animations flow across both.
2. The GrnWave PSIs are mapped by concentric rings (Outer, Inner, Core) to allow layered breathing and strobing.

---

## Trigger Flow (UART JSON Bridge)

1. **Trigger Origin**: Node 1 detects an animation event (e.g. "Cantina Band").
2. **JSON Push**: Node 1 sends a JSON string (e.g. `{"on":true,"ps":10}`) down the UART wire to Node 3 (115200 baud).
3. **Execution**: Node 3 (WLED) receives the command and instantly applies the preset.

This keeps lighting in sync with the audio track playing on Node 2.

---

## Troubleshooting

- **Flickering**: check the Node 3 buck output. Under-voltage causes addressable LEDs to reset.
- **Lag**: the 115200 baud bus is fast — lag usually means WLED entered a power-save state or Node 1's JSON serializer stalled.
- **Heartbeat**: Node 1 sends a diagnostic ping every 60 s to keep the line active.
- **Ground**: ensure Node 1 and Node 3 grounds tie at the central Wago hub. Without a shared reference, the UART line becomes unreliable.

---

**Relevant Hardware & Code:**
- [Node 3: LED Distribution](../architecture/node-3-led-distribution.md)
- [Node Pinout Guide](../architecture/node-pinout-guide.md)
- [GrnWave PSI Hub](../hardware/grnwave-psi-manual.md)
- [WLED Configuration Guide](../maintenance/wled-configuration-guide.md)

[View Master Schematic](../architecture/electrical-schematic.md) | [View Power Architecture](../architecture/power-architecture.md)
