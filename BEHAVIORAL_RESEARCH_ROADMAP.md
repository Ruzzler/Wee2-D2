# <i data-lucide="book-open"></i> Behavioral Research Roadmap

> **TECHNICAL SPECIFICATIONS** | **BABY ASTROMECH ADAPTATION** | **VERIFIED AGAINST FIRMWARE v2.12.1**

Long-term personality + behaviour research roadmap for **Wee2-D2**. Synthesises full-size R2 Builders Club industry standards with the constraints of the project's distributed three-node mesh (ESP-NOW + UART JSON, no Wi-Fi dependency, no cloud).

The droid is built for 100% offline, router-independent operation. A dead Wi-Fi router cannot turn the droid into a static prop.

---

## 1. MarcDuino Cinematic Archive (reference baseline)

The MarcDuino system is the industry-standard cinematic astromech behaviour vocabulary. We adopt the full **:SE00 – :SE15** sequence set as our functional reference. Each sequence is described as a Node 1 → Node 2 → Node 3 chain (motion → audio → lighting).

| Sequence | Category | Technical Logic (N1 → N2 → N3) | Movie Reference |
| :--- | :--- | :--- | :--- |
| **:SE00** | Stop / Reset | Center Dome → Stop Audio → Default Blue/White Logic | System default |
| **:SE01** | Scream | Open Panels → High-pitch scream → Red Logic pulse | ESB: Hoth Attack |
| **:SE02** | Wave | Panel oscillation → Whistle → Teal Logic scan | ANH: Sandcrawler |
| **:SE03** | Smirk | Back-and-forth dome sway → Double whistle → Teal pulse | ANH: Restraining Bolt |
| **:SE04** | Fidget | Quick minor twitches → Annoyed bleeps → Fast erratic logic | ESB: Dagobah |
| **:SE05** | Cantina | Rhythmic march → Music playback → Marching-ants LEDs | ANH: Cantina Scene |
| **:SE06** | Faint | Immediate brake → Groan SFX → Random logic flicker | ANH: Jawas Capture |
| **:SE07** | Sad / Ooh | Slow droop → Low mournful tone → Slow dimming logic | RotJ: Ewok Trap |
| **:SE08** | Leia | Stationary dome → "Message" audio → Dim blue holo pattern | ANH: Help me Obi-Wan |
| **:SE09** | Disco | Continuous dome scan → Orchestral bleeps → Rainbow logic | Community flavor |
| **:SE10** | Razz / Fart | Quick shake → Raspberry → Single red flash | Community flavor |
| **:SE11** | Angry | Aggressive shaking → Loud rapid bleeps → Red/Yellow logic | ESB: Swamp Monster |
| **:SE12** | System Failure | Micro-jitter → Sparking SFX → All lights flash then power down | ESB: Spit out of swamp |
| **:SE13** | Excited | Fast L/R sweeps → High-tempo chirps → Rapid rainbow logic | TPM: Space Battle |
| **:SE14** | Scan | Slow sweeping motion → Radar pings → Sequential logic wipe | ESB: Hoth Ice Plains |
| **:SE15** | Stealth | SE01 motion + light only, **no audio** | Night ops |

Mapping to what's shipping today: **6 performances** (Idle, Angry, Dance, Cantina, Birthday, Imperial March) and **5 reactions** (Wolf Whistle, Razz, Annoyed, Thinking, Excited). The MarcDuino set above is the **target vocabulary** — we currently ship roughly half.

---

## 2. "Baby Astromech" Adaptation Protocol

Wee2-D2 is a Mr. Baddeley "Big Baby" 3D-printed astromech. Full-size R2 conventions need adaptation to the smaller chassis + offline mesh.

| Hardware | Constraint | Adaptation Profile |
| :--- | :--- | :--- |
| **Dome motor** | ~160° rotational limit (gearing + slip ring bind) | Full-size 360° sweeps scaled to ±80° from center using cubic ease-in-out to simulate mass/inertia. |
| **LED matrices** | 4 WLED segments (196 LEDs total) | Standard 24x2 patterns re-mapped to: `0 = Front PSI (76)`, `1 = Rear PSI (76)`, `2 = Front Logic (20)`, `3 = Rear Logic (24)`. |
| **Communication** | Offline mesh only | Single serial commands fragmented across ESP-NOW (motion + reactions) + UART JSON (lighting) + BLE bridge (operator app). All MAC-to-MAC; no router required. |

### Priority Sequence: "Nervous Shake"

To simulate distress on a 160° dome without stripping gears, Node 1 implements a variable **Micro-Jitter Protocol**:

- **Logic**: oscillate dome servo with randomised variance (12–20 Hz, ±2° to ±5°) for 800 ms to mimic organic mechanical panic.
- **Audio sync**: Node 2 plays from `/SCR/` (scream/panic folder) — current ledger has 4 entries.

---

## 3. Audio Sound Bank (DY-HV20T + SD Card Ledger)

Personality is defined by the emotional sound bank. Wee2-D2 uses the **DY-HV20T** audio module (replaced legacy DFPlayer Mini in firmware v2.12.x) reading directly from microSD by uppercase filesystem path. No folder/track index brittleness; the ledger is the source of truth.

Canonical ledger: `Firmware/wee2d2-firmware/sdcard/SD_CARD_LEDGER.md`. As of v2.12.1, **15 named folders, ~307 files**.

| Folder | Subcategory | Count |
| :--- | :--- | :---: |
| `/ALR/` | Alarm | 11 |
| `/CHA/` | Character Voice (Johnny 5, RoboCop) | 10 |
| `/CRI/` | Critical Event | 3 |
| `/HAP/` | Happy / Chirp / Excited | 20 |
| `/HUM/` | Ambient Hum | 25 |
| `/MSC/` | SFX, Misc Chatter, Jingle, Holiday, Droid Voice | 59 |
| `/MUS/` | Music (SW, Party-Pop, TV Theme, R2-Custom) | 23 |
| `/NAR/` | Scene Quote, Hologram | 2 |
| `/PRO/` | Processing | 15 |
| `/QUO/` | Movie Quote | 47 |
| `/RAZ/` | Mockery | 23 |
| `/SAD/` | Sad Tone | 20 |
| `/SCR/` | Scream / Panic | 4 |
| `/SNT/` | Sentence | 20 |
| `/WHS/` | Whistle | 25 |

### Community-Aligned Source Targets

| Bank | Category | Source SFX Library | Status |
| :--- | :--- | :--- | :--- |
| HAP / WHS | Classic chatty | Michael Baddeley (Printed Droid) | shipped |
| WHS | Whistles | CuriousMarc V3 Pack | partial |
| MUS | Singing / Music | R2-D2 Vocalizer + John Williams score | partial |
| NAR | Leia / hologram | Ben Burtt Movie Archive | minimal (2 files) — gap |

---

## 4. Current Gaps & Resolution Paths

| Gap | Status | Resolution Path |
| :--- | :---: | :--- |
| **Organic chat coverage** | partial | Batch-normalise additional `/HAP/` + `/CHA/` files to -3 dB to prevent power clipping on the TPA3118. |
| **`/NAR/` Leia content** | minimal | Source curated Ben Burtt clips, add ledger rows first, then drop in. |
| **Scream loop length** | verified | `/SCR/` files present; needs 3000 ms sustain variants for `react_excited` chain. |
| **Cantina sync** | hardened | `/MUS/` cantina track linked to perf id `0xA0 0x04`. |
| **MarcDuino vocabulary parity** | partial | Currently ship 6 of 16 :SE sequences as production perfs; target full coverage. |

The DY-HV20T's path-based playback removed the legacy "DFPlayer indexing" risk class entirely — no more FAT-sort scripts, no more reshuffle on insert. Adding a new sound is: add file, add ledger row, optionally add to a random pool variable.

---

## 5. Ongoing Research Plan: Autonomous Offline Automations

To make Wee2-D2 feel like a living companion rather than a static puppet, integrate hardware-level sensors that process environmental data entirely on the ESP32 nodes — no cloud, no router.

- [ ] **Capacitive dome interactions.** Line interior of the 3D-printed dome with copper foil tape wired to an ESP32-S3 capacitive touch pin. Light "pet" → happy chirp; harder tap on head → interrupt current action or trigger `:SE11 Angry`.
- [ ] **Bray Sentry Protocol.** LD2410 mmWave radar (or PIR) on Node 1. Localised patrol/sentry mode: stand guard, sound alarm or trigger `:SE01 Scream` on detected entry into an armed room.
- [ ] **Offline face tracking.** Standalone vision module (e.g. HuskyLens) over UART → Node 1. Dome auto-turns to track people walking by, no cloud.
- [ ] **Ambient light adaptation.** LDR sensor. As ambient drops, dim Logic Displays into night mode or roll into `:SE15 Stealth` automatically.
- [ ] **Ultrasonic object avoidance.** HC-SR04 inside the foot shells once motorised foot drives land. Prevents collisions during room roam.
- [ ] **Local voice recognition.** `microWakeWord` on ESP32-S3 for "Hey Wee2" wake — sub-500 ms latency, zero cloud dependency.

All five are explicitly offline by design. Anything requiring a network round-trip is rejected from this roadmap.

---

## 6. Behaviour Framework Tie-In

All of the above sits on top of the droid's three-tier behaviour model: short **life micros** (idle twitches), medium **reactions** (one-shot crowd responses), and long **performances** (choreographed routines). Mood (Neutral / Happy / Grumpy / Focused / Scared / Majestic / Sleepy) shapes what the droid favours in idle moments; the idle escalation ladder (fresh → settled → bored → restless → self-amusement) makes the droid increasingly seek attention the longer it is left alone.

See [Behaviour & Personality](docs/capabilities/animation-framework.md) for the full operator-facing description. Engineering detail on how to add new behaviours lives in the firmware repo, not here — the wiki documents what the droid does, not how the firmware is structured internally.
