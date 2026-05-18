# <i data-lucide="volume-2"></i> Audio System

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: AUDIO HUB** | **MODEL: DY-HV20T → TPA3118**

This page covers how sound works on Wee2-D2: the audio module, the amplifier, the speaker, the sound library on the SD card, and how the droid picks what to play.

![TPA3118 Amplifier Module](../../assets/tpa3118-amplifier-module.jpg)

---

## The Audio Chain

```
microSD card  ──>  DY-HV20T module  ──analog──>  TPA3118 60W amp  ──>  Pyle 3.5" speaker
                         ▲
                         │ serial commands
                         │
                      Node 2
                  (Sound Hub)
```

The droid stores its entire sound library on a microSD card inside the [DY-HV20T audio module](../hardware/dy-hv20t-manual.md). Node 2 tells the module which sound to play. The module sends a low-level analog signal to the [TPA3118 amplifier](../hardware/tpa3118-amp-manual.md), which drives the Pyle 3.5" speaker at convention-friendly volume.

---

## What Triggers Audio

| Source | Behaviour |
| :--- | :--- |
| **RC button (random reaction)** | Picks a reaction and plays its sound. |
| **RC volume up / down** | Adjusts playback volume live. Capped at 26/30 for speaker safety. |
| **Dashboard buttons** | Direct named sound playback by category. |
| **App buttons (BLE)** | Same as the dashboard, just over Bluetooth instead of Wi-Fi. |
| **Performance scripts** | A performance (e.g. Cantina) plays its music track + intersperses chirps. |
| **Idle ambient** | The droid picks a mood-appropriate sound from the relevant folder every 15–45 seconds. |
| **E-Stop** | Silences audio immediately. |

---

## The Sound Library

Sounds live on a microSD card in 15 named folders. Each folder represents an emotional category. Approximate counts in the current loadout:

| Folder | Category | Count |
| :--- | :--- | :---: |
| `/ALR/` | Alarms | 11 |
| `/CHA/` | Character voices | 10 |
| `/CRI/` | Critical events | 3 |
| `/HAP/` | Happy / chirps | 20 |
| `/HUM/` | Ambient hums | 25 |
| `/MSC/` | Misc SFX, droid voice | 59 |
| `/MUS/` | Music tracks | 23 |
| `/NAR/` | Hologram / Leia messages | 2 |
| `/PRO/` | Processing sounds | 15 |
| `/QUO/` | Movie quotes | 47 |
| `/RAZ/` | Razz / mockery | 23 |
| `/SAD/` | Sad tones | 20 |
| `/SCR/` | Screams / panic | 4 |
| `/SNT/` | Sentences | 20 |
| `/WHS/` | Whistles | 25 |

Roughly **307 sound files** total. The canonical inventory + attribution is maintained alongside the firmware.

---

## Mood Drives the Picks

When the droid is idling, it pulls ambient sounds based on its current mood. A happy droid will reach for `/HAP/` and `/WHS/`; a grumpy droid will favour `/RAZ/` and `/SAD/`; a sleepy droid will mostly drone on `/HUM/`. See [Behaviour & Personality](animation-framework.md) for the full mood model.

---

## Volume

| Source | Cap |
| :--- | :--- |
| Anywhere (RC, dashboard, app, BLE) | **26 / 30** — hard maximum |

The cap protects the 3.5" speaker driver from being over-driven through the TPA3118. Every input that can change volume enforces the same cap.

---

## Practical Tips

- **Audio popping during movement** — usually a ground-loop issue at the central negative bus bar. Verify the star-ground tie-down on the body chassis.
- **Long Cantina runs warming the amp** — the TPA3118 can get warm during continuous playback. Keep airflow in the body cavity.
- **New sound not playing** — check it's in the right folder, filename is uppercase, and the firmware sound ledger has been updated.

---

**Relevant hardware:**
- [DY-HV20T Audio Module](../hardware/dy-hv20t-manual.md)
- [TPA3118 60W Amplifier](../hardware/tpa3118-amp-manual.md)
- [Node 2: Sound Hub](../architecture/node-2-sound-hub.md)

[View Master Schematic](../architecture/electrical-schematic.md) | [View Battery Runtime Guide](../maintenance/battery-runtime-guide.md)
