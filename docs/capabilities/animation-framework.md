# <i data-lucide="film"></i> Animation Framework

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: T0/T1/T2 TIERED ANIMATION** | **VERIFIED AGAINST FIRMWARE v2.12.1**

This guide is a builder-facing overview of the animation framework that originates on **Node 1 (Dome Brain)**. It mirrors the engineering reference at `Firmware/wee2d2-firmware/docs/animation/ANIMATION-ENGINE.md` — read that file for the full implementation contract.

The framework was introduced in firmware v2.9.0 (tier model, wrappers, watchdog, idle escalation, mood system) and has shipped without breaking changes through v2.12.1.

---

## Three-Tier Model (T0 / T1 / T2)

Every motion the droid makes belongs to one of three tiers. Mixing them up is the most common authoring mistake.

| Tier | Name | Typical length | Holds `is_animating` lock? | Purpose |
| :---: | :--- | :--- | :--- | :--- |
| **T0** | Life / micro | 0.3 – 3 s | Never | Breathing, idle twitches, glue between higher-tier events |
| **T1** | Reaction | 2 – 6 s | Yes, 5 s cap | One-shot crowd response (whistle, razz, curious) |
| **T2** | Performance | 20 – 190 s | Yes, full run + 5 s buffer | Choreographed routines (Imperial, Cantina, music perfs) |

### Lock Contract

Only T1 and T2 set `is_animating = true`. They do this via the entry wrappers (`start_react` / `start_perf`), which also arm a watchdog deadline. T0 life animations **must never** touch `is_animating` — they run in the negative space between higher-tier events.

A 2-second watchdog interval force-releases a stuck lock. The watchdog is a safety net, not a design feature; a script that relies on it to recover is broken.

---

## Wrapper Scripts (the only correct entry/exit)

These live near the top of `script:` in `node-1-dome.yaml`. Always go through them rather than poking globals.

| Wrapper | Purpose |
| :--- | :--- |
| `start_perf(anim_id, total_phases, duration_ms)` | Sets `is_animating`, arms watchdog, fires `relay_anim_telemetry` so Node 2 + WLED know a perf started. |
| `end_perf(mood, mood_duration_ms)` | Sets `droid_mood`, stamps `last_event_type = 1`, resets idle ladder, releases lock. |
| `start_react(anim_id)` | Like `start_perf` but with a fixed 5 s watchdog — reactions are short and predictable. |
| `end_react(mood, mood_duration_ms)` | Like `end_perf` but stamps `last_event_type = 2` so the ambient loop picks a recovery behaviour. |
| `release_animation_lock` | Zeroes the lock + watchdog. Never call directly — it's the tail of the end-wrappers and the e-stop handlers. |
| `mark_event(event_type)` | Records `last_event_ms` / `last_event_type` / resets idle ladder. Used by e-stop (type 3) and RC stick takeover (type 4). |
| `reset_servo` | Writes `0.0` to `dome_motor` + 30 ms delay. Insurance against leftover PWM from a cancelled move. |
| `unit_variant(max_variants)` | Rolls `g_variant_choice` for sub-choreography branching. |
| `react_followup` | 30 % chance mood-keyed combo move — Happy → shimmy, Grumpy → suspicious, Scared → twitch, etc. |

---

## Action Unit Primitives

Action units are the verbs of the droid's vocabulary. Performances chain them, reactions pick one or two, life animations pick one and wrap it in mood-appropriate audio.

Current inventory (all in `script:` on Node 1):

- `unit_look` / `unit_micro_look` — turn L/R
- `unit_shimmy` — quick L-R-L-R dome wiggle
- `unit_groove` — wider rhythmic sweep for music
- `unit_sweep_ramp` — smooth arc sweep
- `unit_nod` — up-down (if dome tilt is wired)
- `unit_twitch` — one-frame jolt
- `unit_shiver` — multi-frame rapid micro-twitch
- `unit_suspicious` — slow head turn, hold, opposite
- `unit_strut` — cocky sweep + hold
- `unit_droop` — slow decay to centre (Sleepy)
- `unit_rubberneck` — exaggerated wide look
- `unit_victory` — twin-peak punctuation move
- `unit_chortle_body` — gentle chuckle shake
- ~6 more specialty units

Action units that might run after a cancelled move call `reset_servo` at entry as cheap insurance.

---

## Mood System

`droid_mood` is the slow-changing emotional state set by `end_perf` / `end_react`. It decays via a global interval that clears the field when `mood_expiry_ms` is reached.

| Value | Name | Ambient sound byte | Notes |
| :---: | :--- | :---: | :--- |
| 0 | Neutral | `0x1A` (pool mix) | Default at boot |
| 1 | Happy | `0x1B` (HAP/SNT/WHS) | Bright chirps, excited |
| 2 | Grumpy | `0x1C` (RAZ/SAD) | Razz-dominant |
| 3 | Focused | `0x1D` (PRO/HUM) | Processing sounds |
| 4 | Scared | `0x1E` (CRI/ALR/SCR) | Alarm + scream |
| 5 | Majestic | `0x1F` (HUM/SNT) | Long tones |
| 6 | Sleepy | `0x20` (HUM/SAD) | Added v2.9.0 — mostly HUM drones |

`main_ambient_loop` reads `droid_mood` + `idle_escalation_level` + `last_event_type` and picks a mood-keyed ambient sound, a mood-appropriate life animation, and a delay between 12 s (restless) and 60 s (sleepy).

---

## Idle Escalation Ladder

A 10-second ticker raises `idle_escalation_level` as the droid is left alone.

| Level | Age threshold | Name | Behaviour |
| :---: | :--- | :--- | :--- |
| 0 | 0 s | fresh | Mood-keyed life anim, longer pauses |
| 1 | > 30 s | settled | Same as fresh, slightly shorter pauses |
| 2 | > 90 s | bored | 40 % chance of `life_long_idle_attention_seek` |
| 3 | > 180 s | restless | More frequent interrupts, shorter delays |
| 4 | > 300 s | self-amusement | 25 % chance of `life_long_idle_self_amusement` |

Any T1/T2 event resets the ladder to 0 via the wrappers.

Event types recorded in `last_event_type`:

| Value | Event | Recovery hook |
| :---: | :--- | :--- |
| 0 | boot / fresh | — |
| 1 | performance ended | `life_post_perf_catch_breath` |
| 2 | reaction ended | mood-keyed recovery |
| 3 | e-stop | `life_post_estop_uncertain` |
| 4 | RC stick takeover | — |

---

## Music Cue Auto-Choreography

The firmware ships per-song cue sheets at `Firmware/wee2d2-firmware/docs/animation/ANIMATION-CUES/` (23 files at v2.12.1). Each file lists beat-aligned sections with amplitude, color, and WLED preset. The `play_cued_section(duration_ms, r, g, b, preset_id, amplitude, step_num)` script on Node 1 translates each section into:

1. A WLED preset push.
2. A movement unit chosen by amplitude:
   - `amplitude < 0.25` → `unit_micro_look`
   - `amplitude < 0.55` → `unit_shimmy`
   - `amplitude >= 0.55` → `unit_groove`
3. A hold for `duration_ms`.

Building a new music perf is a five-step recipe — see the master engineering reference for the canonical YAML template.

---

## Building a Reaction (T1) — Builder Recap

1. Pick an `anim_id` in the 6–31 range (reserve `0x20+` for new ambient bytes).
2. Pick a sound byte. Named bytes live in `0x06–0x13`. New v2.9.0 bytes: `0x0E/0x0F/0x11/0x12/0x13` (curious / dismissive / proud / confused / sleepy).
3. **Add the Node 2 ESP-NOW switch case** so the sound byte actually plays. Forgetting this is the most common failure — the reaction looks fine on Node 1 but is silent at the speaker.
4. Write `react_<name>` on Node 1, wrapping body in `start_react` / `end_react` and chaining `react_followup` at the tail.
5. Wire dashboards on both nodes (local + relay).
6. Optionally add to the RC CH3 cycle list for stick-triggered access.

### Mood Duration Guide

- Happy (1) — 45–90 s
- Grumpy (2) — 30–45 s
- Focused (3) — 45–60 s
- Scared (4) — 15–30 s (fear fades fast)
- Majestic (5) — 90 s + (pride lingers)
- Sleepy (6) — 120 s + (takes a while to wake up)

---

## Why This Framework Exists

The tier model prevents two classes of bug that plagued earlier firmware:

1. **Concurrent moves stomping each other.** Pre-framework, a music perf could be interrupted mid-phrase by an idle twitch. The `is_animating` lock + tier rules guarantee that only one T1/T2 owns the dome at a time.
2. **Silent stalls.** Pre-framework, a script that errored mid-phase left the lock set forever. The watchdog deadline guarantees the droid always recovers within 2 s of a script's stated `duration_ms + 5 s` buffer.

The mood + idle ladder layer was added so the droid feels alive between events without authoring per-mood per-tier behaviour matrices by hand.

---

**See also:**
- [Autonomous Automations](automations.md) — high-level cue table
- [Audio System](audio-system.md) — ESP-NOW byte → sound mapping
- [LED System](led-system.md) — WLED preset ledger
- Engineering reference (firmware repo): `Firmware/wee2d2-firmware/docs/animation/ANIMATION-ENGINE.md`
- Music cue files (firmware repo): `Firmware/wee2d2-firmware/docs/animation/ANIMATION-CUES/`
