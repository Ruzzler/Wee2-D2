![manual-hero](../../assets/dy-hv20t-module.svg)


# <i data-lucide="volume-2"></i> DY-HV20T Audio Module

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: AUDIO MODULE** | **MODEL: DY-HV20T (20W STEREO MP3)**

The **DY-HV20T** is the audio playback module deployed in the body of Wee2-D2. It plays MP3 files from a microSD card, controlled by Node 2 over a small serial connection, and sends its line-level output into the [TPA3118 60W amplifier](tpa3118-amp-manual.md) which drives the speaker.

The DY-HV20T replaced the earlier DFPlayer Mini once the droid grew past about a hundred sound files — see "Why DY-HV20T over DFPlayer" below.

> The pinout diagram above is an SVG placeholder until a hardware photo is taken. Pin labels match the actual module silkscreen.

---

## At a Glance

| Spec | Value |
| :--- | :--- |
| **Output** | 20W stereo (also feeds the TPA3118 in mono via SPK_1 / SPK_2) |
| **Storage** | microSD card (FAT32) |
| **Audio formats** | MP3, WAV |
| **Control interface** | Serial (UART) from Node 2 |
| **Volume range** | 0 – 30 (firmware caps at **26** for speaker safety) |
| **Supply** | 5V VCC, common ground with Node 2 |
| **Footprint** | Drop-in replacement for DFPlayer Mini PCB cutout |

---

## Wiring

| DY-HV20T Pin | Connects To | Notes |
| :--- | :--- | :--- |
| **VCC** | 5V logic rail (Mini560 Pro) | Shared with Node 2 |
| **GND** | Star ground | Shared with Node 2 + TPA3118 |
| **RX** | Node 2 GPIO 12 | Serial commands inbound |
| **TX** | Node 2 GPIO 13 | Status / busy line back to Node 2 |
| **SPK_1** | TPA3118 input (+) | Line-level analog audio |
| **SPK_2** | TPA3118 input (-) | Line-level analog audio |

---

## SD Card Layout

The card uses 15 named folders — one per emotional category — with files inside each folder following a 4-digit naming scheme. The full sound inventory is curated in `sdcard/SD_CARD_LEDGER.md` in the firmware repository.

| Folder | Contents | Approx count |
| :--- | :--- | :---: |
| `/ALR/` | Alarms | 11 |
| `/CHA/` | Character voices (Johnny 5, RoboCop) | 10 |
| `/CRI/` | Critical events | 3 |
| `/HAP/` | Happy chirps, excited | 20 |
| `/HUM/` | Ambient hums | 25 |
| `/MSC/` | Misc SFX, droid voice, jingles, holiday | 59 |
| `/MUS/` | Music (SW, party-pop, TV themes, R2-custom) | 23 |
| `/NAR/` | Scene quotes, hologram messages | 2 |
| `/PRO/` | Processing sounds | 15 |
| `/QUO/` | Movie quotes | 47 |
| `/RAZ/` | Mockery / razz | 23 |
| `/SAD/` | Sad tones | 20 |
| `/SCR/` | Screams / panic | 4 |
| `/SNT/` | Sentences | 20 |
| `/WHS/` | Whistles | 25 |

Roughly **307 sound files** total as of the current production loadout.

The droid uses these folder names directly — the firmware looks up files by their full filesystem path rather than by an index number, which is why adding a new sound only requires dropping the file in the right folder + adding it to the ledger.

---

## Safety Limits

| Constraint | Why |
| :--- | :--- |
| **Volume capped at 26 / 30** | Protects the 3.5" Pyle speaker from over-driving through the TPA3118 amplifier. The cap is enforced everywhere a volume command can come from — dashboard slider, app, BLE bridge, RC volume-up button. |
| **5V VCC required** | The module is not 3.3V-tolerant on its power pin (though its logic-level lines are 3.3V-compatible). |
| **Uppercase filenames** | The module expects uppercase paths on the SD card. The firmware enforces this automatically when calling files. |

---

## Why DY-HV20T over DFPlayer Mini

| | DFPlayer Mini | DY-HV20T |
| :--- | :--- | :--- |
| **Addressing** | "Play folder 3, file 7" — indexed | "Play /HAP/HAP0001.MP3" — named |
| **Adding new sounds** | Inserting a file in folder 3 re-shuffles every index, breaks references | Path is stable — drop the file in, done |
| **Output** | Mono 3W | 20W stereo |
| **UART stability** | Intermittent under load | Reliable |
| **Footprint** | — | Drop-in compatible |

The path-based model is what made the droid's sound library scale past ~100 files without becoming a maintenance burden.

---

**Relevant docs:**
- [Audio System Guide](../capabilities/audio-system.md) — how audio fits in the droid's behaviour
- [TPA3118 Amplifier Manual](tpa3118-amp-manual.md) — the amp downstream of the module
- [Node 2: Sound Hub](../architecture/node-2-sound-hub.md) — the board that drives this module
