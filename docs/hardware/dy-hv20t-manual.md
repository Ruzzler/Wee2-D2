# <i data-lucide="volume-2"></i> DY-HV20T Audio Module

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: AUDIO MODULE** | **MODEL: DY-HV20T (20W STEREO MP3)** | **VERIFIED AGAINST FIRMWARE v2.12.1**

The **DY-HV20T** is the audio playback module deployed on Node 2 from firmware v2.12.x onward. It replaces the legacy DFPlayer Mini, which was retired due to UART reliability issues and limited path control. The DY-HV20T plays MP3 files directly from a microSD card by filesystem path (uppercase only) over a 9600-baud UART link.

> [!NOTE]
> A dedicated DY-HV20T hardware photo is pending. The BOM currently uses the DFPlayer Mini placeholder image — same form-factor footprint, different chipset.

---

## At a Glance

| Spec | Value |
| :--- | :--- |
| **Output** | 20W stereo (also runs in mono via SPK_1/SPK_2 to TPA3118 input) |
| **Storage** | microSD card (FAT32, uppercase paths) |
| **Audio Format** | MP3 / WAV |
| **Control** | UART (9600 baud, 8N1) |
| **Protocol** | DY-series serial frame: `0xAA` sync + command byte + payload + 8-bit checksum |
| **SD Trigger** | "Play by filesystem path" (`0xAA 0x08 <length> <path>`) — superior to DFPlayer's folder/track index model |
| **Volume Range** | 0–30 (firmware caps at **26** per CLAUDE.md hard safety constraint) |
| **Power** | 5V VCC, common ground with Node 2 |
| **Footprint** | Drop-in for DFPlayer Mini PCB cutout |

---

## Wiring

| DY-HV20T Pin | Connects To | Notes |
| :--- | :--- | :--- |
| **VCC** | 5V logic rail (Mini560 Pro) | Shared with Node 2 |
| **GND** | Star ground | Shared with Node 2 + TPA3118 |
| **RX** | **Node 2 GPIO 12** (`sfx_tx_pin`) | Serial commands inbound, 9600 baud |
| **TX** | **Node 2 GPIO 13** (`sfx_rx_pin`) | Status / busy line inbound to Node 2 |
| **SPK_1** | TPA3118 input (+) | Line-level analog audio |
| **SPK_2** | TPA3118 input (-) | Line-level analog audio |

```
         ESP32-S3 Super Mini (Node 2)
         ┌──────────────────┐
         │ GPIO 12 (UART TX)│──────> DY-HV20T RX
         │ GPIO 13 (UART RX)│<────── DY-HV20T TX
         │ 5V               │──────> DY-HV20T VCC
         │ GND              │──────> DY-HV20T GND
         └──────────────────┘

         DY-HV20T
         ┌──────────────────┐
         │ VCC ──── 5V       │
         │ GND ──── GND      │
         │ RX  <─── GPIO 12  │  (commands)
         │ TX  ───> GPIO 13  │  (status)
         │ SPK+ ────────────>│──> TPA3118 Input (+)
         │ SPK- ────────────>│──> TPA3118 Input (-)
         └──────────────────┘
```

---

## Protocol Quick Reference

The firmware uses a "Specified Path Playback" frame to call MP3s directly by their uppercase SD path.

| Frame | Bytes | Purpose |
| :--- | :--- | :--- |
| Device Select (SD) | `0xAA 0x0B 0x01 <ck>` | Select SD card as source (boot priority 900) |
| Set Volume | `0xAA 0x13 <vol> <ck>` | Volume 0–30 (firmware clamps to ≤26) |
| Play by Path | `0xAA 0x08 <len> "/FOLDER/FILE.MP3" <ck>` | Direct filesystem playback |
| Stop | `0xAA 0x10 <ck>` | Stop current track |

Path frames are constructed by `firmware/include/dy_path_helper.h`. The `g_force_uppercase` global (default ON) enforces uppercase filenames before transmission — the DY-HV20T silently fails on lowercase paths.

---

## SD Card Layout (Canonical)

The card has **15 named folders** + a Master Asset Ledger maintained at `Firmware/wee2d2-firmware/sdcard/SD_CARD_LEDGER.md`. Total ~307 files as of v2.12.1.

| Folder | Subcategory | Count |
| :--- | :--- | :---: |
| `/ALR/` | Alarm | 11 |
| `/CHA/` | Character Voice (Johnny 5, RoboCop) | 10 |
| `/CRI/` | Critical Event | 3 |
| `/HAP/` | Happy / Chirp / Excited | 20 |
| `/HUM/` | Ambient Hum | 25 |
| `/MSC/` | SFX-Short, Misc-Chatter, Jingle, Holiday, Droid-Voice | 59 |
| `/MUS/` | Music (SW, Party-Pop, TV-Theme, R2-Custom) | 23 |
| `/NAR/` | Scene Quote, Hologram | 2 |
| `/PRO/` | Processing | 15 |
| `/QUO/` | Movie Quote | 47 |
| `/RAZ/` | Mockery | 23 |
| `/SAD/` | Sad Tone | 20 |
| `/SCR/` | Scream / Panic | 4 |
| `/SNT/` | Sentence | 20 |
| `/WHS/` | Whistle | 25 |

**Naming convention**: `/FOLDER/PFX0001.MP3` — 3-letter folder prefix + 4-digit sequence. Source-of-truth for additions is the ledger; firmware references files via the same uppercase paths.

---

## Boot Sequence

The Node 2 ESPHome boot handler runs at **priority 900** to ensure the DY-HV20T is initialized before any sound trigger can fire:

1. `on_boot:` priority 900 fires.
2. Frame: `0xAA 0x0B 0x01 <ck>` — Device Select (SD).
3. Short delay.
4. Frame: `0xAA 0x13 <audio_volume> <ck>` — apply saved volume (clamped to ≤ 26).
5. Module is now ready for `play_by_path` triggers via ESP-NOW relay or local script.

If the module misses this sequence (power dropout, late SD insert), the dashboard will show audio commands succeeding at the protocol layer but silent at the speaker — the first thing to check is that boot priority 900 ran cleanly.

---

## Safety Limits

| Constraint | Value | Why |
| :--- | :--- | :--- |
| **Max volume** | 26 / 30 | Protects the 3.5" Pyle driver via TPA3118 gain headroom. Clamped at the Volume slider, on every ESP-NOW relay, and at the BLE bridge. |
| **Uppercase paths** | Required | DY-HV20T silently rejects lowercase filenames. `g_force_uppercase` enforces. |
| **5V supply only** | — | Module is not 3.3V-tolerant on VCC; logic lines are 3.3V-compatible. |
| **Boot priority 900** | — | Must initialize before any caller can request playback. |

---

## Why DY-HV20T over DFPlayer Mini

| | DFPlayer Mini | DY-HV20T |
| :--- | :--- | :--- |
| **Path control** | Folder/track index (e.g., "play folder 3 file 7") | Filesystem path ("play /HAP/HAP0001.MP3") |
| **Re-numbering risk** | Adding a file to folder 3 reshuffles every index | Path is stable forever |
| **UART reliability** | Intermittent at 9600 baud under load | Stable at 9600 baud |
| **Output** | Mono 3W (needs external amp anyway) | 20W stereo (still feeds TPA3118 for the 60W path) |
| **SD path discipline** | Tolerant of mixed case | Strict uppercase |

The path-based model is what made the firmware's per-folder reaction routing (`0xA3` codes folder-aligned, not sequential) practical to maintain. Adding a new "happy" sound in the legacy DFPlayer era required updating index tables on the firmware side; with the DY-HV20T the ledger is the only source of truth.

---

**Relevant Code:**
- `Firmware/wee2d2-firmware/firmware/node-2-sound.yaml` (UART config, boot priority, volume clamp)
- `Firmware/wee2d2-firmware/firmware/include/dy_path_helper.h` (frame builder + uppercase enforcement)
- `Firmware/wee2d2-firmware/sdcard/SD_CARD_LEDGER.md` (canonical sound inventory)

[View Audio System Guide](../capabilities/audio-system.md) | [View TPA3118 Amplifier Manual](tpa3118-amp-manual.md) | [View Node 2: Sound Hub](../architecture/node-2-sound-hub.md)
