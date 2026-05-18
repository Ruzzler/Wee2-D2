# <i data-lucide="film"></i> Behaviour & Personality

> **TECHNICAL SPECIFICATIONS** | **WHAT THE DROID DOES, WHY, AND WHEN**

This page describes how Wee2-D2 behaves day to day — what idle looks like, what reactions and performances are, how moods influence the next action, and how the droid recovers from being interrupted. The internal engineering reference lives in the firmware repository (separate, not yet public).

---

## The Three Behaviour Tiers

Every motion the droid makes belongs to one of three tiers. Think of them like sentences (short / medium / long) — each tier serves a different purpose.

| Tier | Length | Purpose | Example |
| :--- | :--- | :--- | :--- |
| **Life / micro** | Under 3 seconds | Idle chatter, breathing twitches, ambient sweeps | A small head turn while waiting |
| **Reaction** | 2 – 6 seconds | One-shot crowd response | Wolf whistle at a passerby, razz at a kid teasing the droid |
| **Performance** | 20 – 190 seconds | Choreographed routine, often music-synced | Cantina theme, Imperial March, birthday song |

Reactions and performances are "loud" — they take over the dome for their duration. Life micros are "quiet" — they happen in the gaps between bigger events to keep the droid feeling alive instead of frozen.

---

## What Ships Today

| Performances (long-form) |
| :--- |
| Idle, Angry, Dance, Cantina, Birthday, Imperial March |

| Reactions (short bursts) |
| :--- |
| Wolf whistle, Razz, Annoyed, Thinking, Excited |

| Life animations (background loop) |
| :--- |
| Auto-chirp, self-scan, attention-seek, self-amusement, mood-keyed micro-moves |

More are planned. The MarcDuino industry-standard astromech vocabulary (`:SE00`–`:SE15`) is the long-term reference target; the droid currently ships roughly half of it.

---

## Moods

The droid carries a mood after every reaction and performance. Mood decides what ambient sounds and life animations it favours next. Each mood lasts roughly 30 s – 2 min depending on what triggered it (a Cantina performance leaves a longer happy afterglow; a quick razz fades fast).

| Mood | Vibe | Ambient flavour |
| :--- | :--- | :--- |
| **Neutral** | Default at boot | Mixed chirps |
| **Happy** | Excited, bright | Chirps, sentences, whistles |
| **Grumpy** | Annoyed, dismissive | Razzes, sad tones |
| **Focused** | Thinking, calculating | Processing sounds, hums |
| **Scared** | Alarmed, jumpy | Cries, alarms, screams |
| **Majestic** | Proud, regal | Long hums, sentences |
| **Sleepy** | Winding down | Mostly hums, sad tones |

When a mood ends naturally, the droid drifts back to Neutral.

---

## Idle Escalation Ladder

The longer the droid is left alone, the more it starts seeking attention. A timer in the background quietly raises an "idle level" the longer nothing happens:

| Time alone | Level | What changes |
| :--- | :--- | :--- |
| 0 s | **Fresh** | Just finished an interaction — calm life animations, longer pauses between |
| > 30 s | **Settled** | Same character, slightly tighter pauses |
| > 90 s | **Bored** | ~40% chance of a deliberate attention-seek move (look around, soft whistle) |
| > 180 s | **Restless** | More frequent interrupts, shorter delays between life animations |
| > 300 s | **Self-amusement** | ~25% chance of an extended "playing alone" routine |

Any reaction or performance — RC button, app tap, dashboard click — resets the timer back to **Fresh**. The droid is rewarding you for interacting with it.

---

## Music Performances

Music-synced performances follow the beat of the actual song. Sections of the song have a characteristic "intensity" and the droid picks a movement style to match:

- **Low-intensity sections** (verse intros, calm bridges): subtle head turns
- **Mid sections** (groove, verse body): rhythmic shimmies
- **High sections** (chorus, drops): wider grooves with full sweep range

The droid also pushes a matching colour preset to the lighting at each section boundary. This is how, for example, the Cantina performance feels timed to the song instead of generic dome wiggling.

The library of beat-mapped songs lives in the firmware repository. Adding a new music performance is currently a developer task — eventually this will be configurable from the app.

---

## Reaction Afterglow

After a reaction, the droid has a 30% chance of chaining a mood-appropriate follow-up move (a "shimmy" after Happy, "suspicious look" after Grumpy, etc). This is what stops reactions from feeling like one-and-done button presses — the droid feels like it's reacting to its own reaction.

---

## Safety: Watchdog & Stuck-State Recovery

If something causes a performance or reaction to get stuck mid-run (rare), an internal safety net automatically releases the droid back to idle within 2 seconds past its expected end time. You will never have to power-cycle to get the droid moving again after a glitched animation.

Hard stops (E-Stop button on the RC, E-Stop on the app or dashboard) cut the current behaviour immediately and put the droid into a "recovering" state for a few seconds, where it picks a calm life animation as it settles. This is on purpose — slamming back to idle would feel mechanical.

---

## How This Connects To What You'll Use

| You touch this | And this is what's running underneath |
| :--- | :--- |
| RC stick (dome left/right) | Direct override — interrupts whatever T0/T1/T2 was playing |
| RC button: Perf Cycle | Steps through performances one at a time |
| RC button: Random Reaction | Fires a random reaction from the list above |
| RC button: E-Stop | Hard stops everything immediately |
| Dashboard / App: Animation button | Triggers a specific performance by name |
| Dashboard / App: Reaction button | Triggers a specific reaction by name |
| Dashboard / App: Sound button | Direct sound playback (independent of behaviour layer) |
| Just leave the droid alone | Idle escalation ladder kicks in — droid starts asking for attention |

---

**See also:**
- [Autonomous Automations](automations.md)
- [Audio System](audio-system.md)
- [LED System](led-system.md)
- [Dashboard & App](dashboard-and-app.md)
