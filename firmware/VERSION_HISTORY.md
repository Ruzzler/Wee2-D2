# 📜 Firmware Version History: Wee2-D2
> **REPOSITORY OF RECORD** | **SYSTEM: ESPHOME & WLED**

This document tracks all production-verified firmware releases for the Wee2-D2. To ensure stability, only versions listed as **"VERIFIED"** should be deployed to the physical droid. 

---

## [v1.8.4] - 2026-03-31
### 🛰️ Wireless Bridge Harmonization
- **Node 1 (Body Hub)**: Standardized on ESP32-S3 Super Mini. Integrated DFPlayer Mini UART triggers.
- **Node 3 (Dome Master)**: Established as the Behavioral Master. Implemented ESP-NOW broadcasting for Mood Banks 1-4.
- **Sync Protocol**: Switched to **ESP-NOW** for all inter-node communication, decommissioning the physical UDNS bus.
- **Status**: **VERIFIED**

## [v1.8.0] - 2026-03-31
### 🧠 S3 Architecture Shift
- **Hardware Upgrade**: Transitioned from standard ESP32 Dev Boards to ESP32-S3 across the motion and audio tiers.
- **LED Interface**: Implemented RMT memory splits (`rmt_symbols: 96`) for dual-strip driving on S3 pins.
- **Status**: **ARCHIVED**

## [v1.7.5] - 2026-03-25
### 🔊 Final UART Serial Standard
- **Protocol**: 115200 Baud UDNS (Legacy Physical Bus).
- **Status**: **LEGACY - DO NOT DEPLOY**

---

## 🏗️ Release Standard Operating Procedure (SOP)
To prevent droid downtime, follow the [v1.8.5 Firmware Workflow](../../AGENTS.md):
1. **Develop** in `firmware/development/`.
2. **Verify** via bench test on a spare ESP32.
3. **Graduate** to `firmware/production/` for deployment.
4. **Snapshot** a copy to `firmware/archive/` with the version suffix (e.g., `FW-v1.8.4-body.yaml`).
