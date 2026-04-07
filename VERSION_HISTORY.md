# <i data-lucide="history"></i> Firmware Version History: Wee2-D2

> **REPOSITORY OF RECORD** | **SYSTEM: ESPHOME & WLED**

This document tracks all production-verified firmware releases for the Wee2-D2. To ensure stability, only versions listed as **"VERIFIED"** should be deployed to the physical droid.

---

> [!NOTE]
> **NODE RENUMBERING**: Please note that in `v2.2.0`, the system nodes were physically renumbered. In `v1.x` and `v2.0` logs below, **Node 1** refers to the Body Hub and **Node 3** refers to the Dome Master. In `v2.2.0` and beyond, Node 1 officially became the Dome Master.

## [v2.1.3] - 2026-04-07

### Hardened Reflow & Normal Language Standard
- **Aesthetic**: Implemented 1.5rem Baseline Grid and restored industrial list indentation.
- **Structural**: Enforced H1-Lucide-Icon and Line-3-Tech-Tag hierarchy across all 20+ docs.
- **Tone**: Stripped thematic jargon (Neural, Cyber, Pulse) in favor of Normal/Casual technical standard.
- **Citations**: Integrated 150+ evidence-based firmware citations (`file:line`) linking docs to v2.6.0 source.
- **Status**: **VERIFIED (Hardened)**


## [v2.1.2] - 2026-04-01

### Aesthetic Graduation & IA Stabilization

- **Technical Docs**: Finalized the v2.1.2 Aesthetic Standard.
- **Terminology**: Globally harmonized "Automations" and "Cinematic Logic Display".
- **IA Strategy**: Standardized the dual-tier Wiki (Site Folder + Technical Manuals).
- **Status**: **VERIFIED**

## [v1.8.4] - 2026-03-31

### Wireless Bridge Harmonization

- **Node 1 (Body Hub)**: Standardized on ESP32-S3 Super Mini. Integrated DFPlayer Mini UART triggers.
- **Node 3 (Dome Master)**: Established as the Behavioral Master. Implemented ESP-NOW broadcasting for Mood Banks 1-4.
- **Sync Protocol**: Switched to **ESP-NOW** for all inter-node communication, decommissioning the physical UDNS bus.
- **Status**: **VERIFIED**

## v2.0.0-Hybrid | 2026-03-31 | **The Automated Pipeline** | Stable | [Node 1, 3] | [v1.8.4-Legacy] |

| v1.8.5 | 2026-03-31 | **Factual Language Audit** | Stable-Legacy | [All] | [v1.7.0] |
Upgrade**: Transitioned from standard ESP32 Dev Boards to ESP32-S3 across the motion and audio tiers.
- **LED Interface**: Implemented RMT memory splits (`rmt_symbols: 96`) for dual-strip driving on S3 pins.
- **Status**: **ARCHIVED**

## [v1.7.5] - 2026-03-25

### Final UART Serial Standard

- **Protocol**: 115200 Baud UDNS (Legacy Physical Bus).
- **Status**: **LEGACY - DO NOT DEPLOY**

---

## Release Standard Operating Procedure (SOP)

To prevent droid downtime, follow the [v2.1.2 Production Lock](../../AGENTS.md):
1. **Develop** in `firmware/development/`.
1. **Verify** via bench test on a spare ESP32.
1. **Graduate** to `firmware/production/` ONLY after explicit user approval and bench verification.
1. **Archive** a copy to `firmware/archive/` with the version suffix (e.g., `FW-v1.8.4-body.yaml`).