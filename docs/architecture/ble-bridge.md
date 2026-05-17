# <i data-lucide="bluetooth"></i> BLE App Control

> **TECHNICAL SPECIFICATIONS** | **HOW THE MOBILE APP TALKS TO THE DROID**

A small dedicated Bluetooth controller (the **BLE bridge**) sits inside the droid and gives the [Wee2-D2 app](app-ecosystem.md) a fast, Wi-Fi-free way to operate the droid at venues. You tap a button in the app, the bridge receives it over Bluetooth, and the droid responds within ~100 ms. No router, no DNS lookup, no cloud.

For wire-format details (UUIDs, byte layouts, validation) see the firmware-side spec at `Firmware/wee2d2-firmware/docs/BLE-PROTOCOL-SPEC.md`. This page covers what the bridge does from a builder / operator perspective.

---

## Why a Dedicated BLE Board

Earlier prototypes ran the BLE radio on the same chip as the web dashboard. The two workloads competed for the radio (BLE and Wi-Fi share the 2.4 GHz front-end) and dashboard responsiveness suffered. The dedicated BLE bridge solves that: it does Bluetooth + ESP-NOW only, never touches Wi-Fi, and stays available even when the dashboard is busy.

The trade-off is one extra small board in the build. The wiring is trivial — the bridge is powered from the 5V logic rail and has no external pins to break out.

---

## What the App Can Do (Slice 1B feature set)

| App control | Effect |
| :--- | :--- |
| **EMERGENCY STOP** | Cuts the current behaviour immediately and silences audio. Always one tap away. |
| **Performances** | Trigger any of the production performances by name (Idle, Angry, Dance, Cantina, Birthday, Imperial March). |
| **Reactions** | Trigger any reaction by name (Wolf Whistle, Razz, Annoyed, Thinking, Excited). |
| **Lighting Presets** | Pick from the 15 cinematic lighting presets (1977 Idle, Alert Red, Disco, Imperial March, etc). |
| **Dome Speed** | Live slider to tune dome motion intensity (10–100%). |
| **Sound triggers** | Play random sounds from any of the SFX pools (Happy, Sad, Alarm, Scream, Whistle, Hum, Razz, Processing, etc) or specific named tracks. |
| **Volume** | Live volume control 0–26. The app cannot push past 26 even if you try — the bridge enforces the safety cap. |
| **Display Mode** | Switch the on-droid display behaviour (operator panel, kiosk relay, dimmed). |

The app also shows live status from the droid: whether Node 1 is online, which animation is currently playing, which step it's on, and the last reaction that fired.

---

## Range and Connection

| Property | Value |
| :--- | :--- |
| **Range** | ~10 m line-of-sight |
| **Reconnect** | App auto-reconnects silently when in range (no device picker each time) |
| **Number of clients** | One at a time (the app or one nRF Connect session) |
| **Wi-Fi required** | No |
| **Internet required** | No |

The intended pattern is: operator's phone or tablet, app pinned to home screen, walk up to the droid at a convention, tap the icon, control panel appears in under 2 seconds.

---

## Safety

| Control | Behaviour |
| :--- | :--- |
| **Volume cap** | Bridge clamps any value above 26 down to 26 before relaying. The app can't damage the speaker through volume slamming. |
| **E-Stop fan-out** | E-Stop in the app stops dome motion AND silences audio in a single tap — both subsystems receive the stop. |
| **Reaction folder alignment** | The reaction codes the app sends are bound to actual sound folders. If a builder customises the firmware reaction set, the app's reaction buttons remain valid by construction. |

The bridge has no on-the-wire authentication today (any nearby Bluetooth client could in principle write commands). This is an intentional trade-off for personal / event use — an attacker within 10 m can fire commands the operator already controls via RC, and E-Stop is recoverable by power-cycling. Bonded pairing is on the roadmap once an upstream toolchain issue is resolved.

---

## Future: Pre-Compiled `.bin` Distribution

Long-term direction: ship pre-compiled firmware binaries for all four nodes so builders can flash the droid without ever touching ESPHome, YAML, or `secrets.yaml`. The BLE bridge is the simplest of the four to deliver this way — it has no per-build secrets and no GPIO customisation between builds.

---

**See also:**
- [App & Kiosk Ecosystem](app-ecosystem.md)
- [Web Control Dashboard](../capabilities/web-control-dashboard.md)
- [Behaviour & Personality](../capabilities/animation-framework.md)
