# <i data-lucide="history"></i> Firmware Version History

> **REPOSITORY OF RECORD** | **SYSTEM: ESPHOME + WLED-MM**

This document tracks production-verified firmware releases for the Wee2-D2 droid. Only versions listed as **VERIFIED** should be deployed.

The canonical firmware repository is at `Firmware/wee2d2-firmware/`. This file mirrors the firmware `CHANGELOG.md` at a builder-friendly level of detail.

---

> [!NOTE]
> **Node Renumbering**: In firmware `v2.2.0` the system nodes were physically renumbered. In `v1.x` and `v2.0` log entries below, **Node 1** refers to the Body Hub and **Node 3** refers to the Dome Master. From `v2.2.0` onward, Node 1 is the Dome Brain, Node 2 is the Sound Hub, Node 3 is the LED Hub.

## [v2.12.1] - 2026-05-16

### Audit & Hardening

- **WLED Brightness Clamp**: `set_dome_color` + `set_light_color` now clamp `bri` to ≤ 76 (≤30%) before sending JSON to WLED — enforces the hard safety constraint at the per-frame ceiling. WLED ABL remains the secondary current guard.
- **Kiosk Loop Retry**: when a reaction is in progress at kiosk timer fire-time, the cycle now gives one 10 s retry before skipping (was: silent drop, up to 2x interval gap).
- **Underflow Guard**: `play_cued_section` guards against negative `duration_ms - 200` wrapping to ~4.29 billion ms (would hang the script indefinitely).
- **Doc Sync**: corrected stale `DFPlayer GPIO43/44` references to `DY-HV20T GPIO12/13` across firmware-side AGENTS.md and README.
- **Status**: **VERIFIED**

## [v2.12.0] - 2026-05-10

### Slice 1B BLE Bridge Feature Parity

- **3 new BLE command types** on the Node 4 BLE bridge for Slice 1B feature parity with Node 2 dashboard:
  - `0x14 Volume` — set `audio_volume` (0–26, bridge-clamped to the CLAUDE.md hard safety constraint)
  - `0x15 Sound` — trigger named sound bytes
  - `0x16 Display Mode` — switch Node 2 between operator dashboard, kiosk relay, and dimmed presets
- BLE bridge version track bumped to `v0.2.0`.
- App (`wee2d2-app`) protocol mirror updated to match.
- **Status**: **VERIFIED**

## [v2.11.2] - 2026-04-30

### Repo Reorg & Audit Cleanup

- Flattened firmware repo to remove `dev/`, `stable/`, and `archive/` tiers — versioning is now via Git tags only.
- Migrated docs to a single `docs/` tree.
- **Status**: **VERIFIED**

## [v2.9.0] - 2026-04-15

### Animation Framework (T0/T1/T2)

- **Three-tier model**: T0 (life / micro), T1 (reaction), T2 (performance) with explicit `is_animating` lock contract.
- **Wrapper scripts**: `start_react` / `end_react` / `start_perf` / `end_perf` / `release_animation_lock` / `mark_event`.
- **Watchdog**: 2 s ticker force-releases stuck locks (safety net, not a design feature).
- **Mood system**: 7 moods (Neutral / Happy / Grumpy / Focused / Scared / Majestic / Sleepy) drive `main_ambient_loop` choices.
- **Idle escalation ladder**: 5 levels (fresh → settled → bored → restless → self-amusement) with mood-keyed life animations.
- **Music cue auto-choreography**: `play_cued_section` consumes per-song JSON cue sheets and routes to movement units by amplitude band.
- **Sleepy mood added** with `0x20` (HUM/SAD) ambient byte.
- **Status**: **VERIFIED** — see `Firmware/wee2d2-firmware/docs/animation/ANIMATION-ENGINE.md` for the canonical engineering reference, or the builder-facing summary at [Animation Framework](docs/capabilities/animation-framework.md).

## [v2.7.10] - 2026-04-10

### DashboardSync Stabilization

- **Dashboard relay hardening**: Node 2 web dashboard commands consistently propagate to Node 1 via ESP-NOW with delivery confirmation.
- **Heartbeat monitoring**: Node 2 tracks Node 1 + Node 3 liveness; dashboard reflects status badges.
- **Status**: **VERIFIED (pre-Animation-Framework stable)**

## [v2.6.0] - 2026-04-06

### Neural Command Center & Dashboard Integration

- **Architectural shift**: decoupled physical RC audio triggers. Node 2 formally established as the dashboard-hosting hub.
- **ESP-NOW relay gateway**: Node 2 captures dashboard commands and relays hex triggers (`0xA0`–`0xA2`) bidirectionally to Node 1.
- **WLED Config JSONs**: migrated manual WLED mapping into standard GUI restores (`cfg.json`, `presets.json`, `ledmap.json`).
- **Secrets Protocol**: abstracted Wi-Fi and ESP-NOW MAC addresses out of YAML into `secrets.yaml`.
- **UDNS Decommissioning Sweep**: completed purge of all legacy UDNS / Mode bindings across diagrams and schematics.
- **Status**: **VERIFIED**

## [v2.2.0] - 2026-04-01

### Node Mesh 2.0 — Logical Renumbering

- **Architectural refactor**: renumbered the node mesh to follow functional hierarchy:
  - Node 1 → Dome Motion Master ("Brain")
  - Node 2 → Sound Hub ("Mouth")
  - Node 3 → LED Distribution ("Visuals")
- **Terminology sweep**: globally replaced legacy `MCU` references with `Node`, enforced `Node 1` (with space) formatting.
- **Wiki Navigation**: synchronized the sidebar and interactive schematic to the new IDs.
- **Status**: **VERIFIED**

## [v1.8.0] - 2026-03-31

### Wireless Bridge Pivot (ESP-NOW)

- **Architectural shift**: decommissioned the physical UDNS UART bus (GPIO 16/17) through the slip ring in favour of distributed ESP-NOW.
- **Node consolidation**: standardized Node 1 (Body) and Node 3 (Dome) on ESP32-S3 Super Mini with the `esp-idf` framework.
- **Audio overhaul**: replaced PEMENOL 60W soundboard with modular DFPlayer Mini + TPA3118 60W amplifier.
- **EMI isolation**: repurposed slip ring circuits C5/C6 to RESERVED, moving all high-speed signal logic to 2.4 GHz wireless.
- **Status**: **VERIFIED**

## [v1.7.x] - 2026-03-25 → 2026-03-31

### Pre-Wireless Stabilization

Pre-ESP-NOW versions running the legacy UDNS UART serial bus (115200 baud). Includes:
- v1.7.5: final UART serial standard
- v1.7.2: dome control refinement & bench testing
- v1.7.0: S3 behavioural update + RMT peripheral integration for LED arrays

- **Status**: **LEGACY — DO NOT DEPLOY**

---

## Release Standard Operating Procedure

To prevent droid downtime, follow the procedure documented in the firmware repo's `AGENTS.md` release protocol:

1. Update `Firmware/wee2d2-firmware/CHANGELOG.md` with the new section.
2. Bump `fw_version` in both entry YAMLs (lockstep).
3. Update `AGENTS.md` header baseline + `README.md` + `docs/AGENT-INDEX.md` footer.
4. Tag the commit: `git tag -a vX.Y.Z -m "..."`.
5. If `presets.json` changed, upload to Node 3 WLED via web UI.
6. After release, update this Wiki file (`VERSION_HISTORY.md`) + the Wiki `AGENTS.md` §3 firmware baseline.
