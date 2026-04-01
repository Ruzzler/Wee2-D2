# <i data-lucide="shield-check"></i> Wee2-D2 Firmware Repository

This directory contains all microcontroller firmware and configuration files for the Wee2-D2 droid.

## <i data-lucide="lock"></i> Deployment SOP (v2.1.2 Production Lock)

To ensure droid stability and prevent accidental outages, all development **MUST** follow the tiered graduation process:

1.  **[TESTING] `development/`**: All new features, experimental logic, and configuration tweaks **SHALL** be performed here first.
2.  **[VERIFICATION]**: The builder **MUST** bench-test the development firmware on a spare ESP32 before graduation.
3.  **[STABLE] `production/`**: Once verified and approved, code is "Graduated" to this directory for final deployment to the droid hardware.

## Directory Structure

| Directory | Purpose | Access Rule |
| :--- | :--- | :--- |
| **`production/`** | Stable, deployed firmware. | **READ-ONLY** during research. NO direct edits. |
| **`development/`** | Active testing and sandboxing. | Open for iterative development. |
| **`archive/`** | Legacy versions and backups. | Historical reference only. |
| **`common/`** | Shared ESPHome packages. | Source of truth for base configs. |
| **`esc-configs/`** | Specialized ESC XML/Settings. | Hardware-specific tuning. |

---
Refer to the main [**`AGENTS.md`**](../AGENTS.md) for full Operational Procedures.
