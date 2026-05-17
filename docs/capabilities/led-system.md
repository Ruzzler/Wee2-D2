# <i data-lucide="lightbulb"></i> LED System

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: CINEMATIC LIGHTING** | **MODEL: WLED + GRNWAVE PSI + WS2812B**

This page covers how the droid's lighting works: what LEDs are where, what the cinematic presets look like, and how lighting stays in sync with the rest of the droid's behaviour.

---

## What's Lit Up

The droid has four addressable LED strips:

| Display | What it is | LEDs |
| :--- | :--- | :---: |
| **Front PSI** | Round indicator dot on the front of the dome (the "Process State Indicator") | 76 |
| **Rear PSI** | Round indicator dot on the rear of the dome | 76 |
| **Front Logic Display** | Rectangular scrolling matrix on the front of the dome | 20 |
| **Rear Logic Display** | Rectangular scrolling matrix on the rear of the dome | 24 |

All four are driven by [Node 3](../architecture/node-3-led-distribution.md), the dedicated LED hub.

---

## The 15 Cinematic Presets

The droid ships with 15 pre-built lighting "scenes" — each one a coordinated visual across all four displays. You can trigger any of them from the dashboard, the app, or as part of a performance.

| Preset | Vibe | When you'd use it |
| :---: | :--- | :--- |
| **0** | All Off | Power save, stealth |
| **1** | 1977 Idle | Classic Blue/Teal scroll | Standard operation |
| **2** | Neural Processing | Cyan logic pulse | Thinking, calculating |
| **3** | Alert Red | Synchronized red flash | Combat, alarm |
| **4** | Legacy Mode | Static 1977 colours | Low-power glow |
| **5** | Front Only | Front displays only | Component test |
| **6** | Rear Only | Rear displays only | Component test |
| **7** | PSI Scan | Dual-PSI alternating pulse | Sensor sweep |
| **8** | Data Transfer | High-speed white jitter | "Linked" feel |
| **9** | Leia Message | Dim blue flicker | Holo-projection bit |
| **10** | Disco Mode | RGB rainbow cycle | Dance / party |
| **11** | Stealth | Dimmed single pixel | Night ops |
| **12** | Startup | Cascading wipe | Boot sequence |
| **13** | Malfunction | Random red/orange static | "I'm broken" gag |
| **14** | Celebration | Gold/white shimmer | Victory, taunt |
| **15** | Imperial March | Slow red fade | Bad-guy theme |

A 16th open slot is available for builders who want to add their own.

---

## How Lighting Syncs With Behaviour

Lighting is coordinated by Node 1 (the dome brain), not Node 3 directly. When a performance fires, Node 1 picks the right preset and tells Node 3 to apply it immediately. This keeps lighting locked to the sound + motion timing.

For music performances (Cantina, Imperial March, Dance, Birthday), the lighting changes preset between song sections — verse goes to one colour, chorus to another, drop to a third. The droid is not just looping a single preset for the full song.

---

## Power Safety

The LED rails will damage the GrnWave PSI matrices if they ever exceed 5.2V. The droid uses a dedicated buck converter for the dome LED rail (separate from logic) so a heavy LED draw can't sag the ESP32 supply, and overall brightness is capped at approximately 30% in two places (the lighting hub itself + every command Node 1 sends). The cap is a hard safety limit, not a preference.

---

## Practical Tips

- **Flickering** — usually means the LED rail buck converter is sagging under load. Verify the 5V stays steady when all 196 LEDs are at full bright.
- **One strip dark while the others animate** — check the data wire and ground tie on that strip. The strips share +5V and ground at the dome Wago hub.
- **Adding new presets** — done through the WLED web UI on Node 3, then saved in the firmware preset file.

---

**Relevant hardware:**
- [Node 3: LED Hub](../architecture/node-3-led-distribution.md)
- [GrnWave PSI Hub](../hardware/grnwave-psi-manual.md)
- [WLED Configuration Guide](../maintenance/wled-configuration-guide.md)

[View Master Schematic](../architecture/electrical-schematic.md) | [View Power Architecture](../architecture/power-architecture.md) | [View Behaviour & Personality](animation-framework.md)
