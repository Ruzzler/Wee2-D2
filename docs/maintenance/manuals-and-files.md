# 📚 Manuals and Files
> **TECHNICAL REPOSITORY** | **CORE DATA HUB**

Welcome to the centralized Manuals and Files Hub. This page provides rapid access to all documentation, firmware, and configuration assets for the Wee2-D2 project.

---

## 📜 1. Technical Manuals
Comprehensive guides for hardware integration and system capabilities.

### **📦 Hardware Data Sheets (PDF)**
These are the original manufacturer specifications for the core hardware.
- [HOTRC DS-600 Transmitter](../manuals/hotrc-ds600-manual.pdf)
- [HOTRC F-06A PWM Receiver](../manuals/hotrc-f06a-manual.pdf)
- [Flipsky Mini FSESC 6.7 Pro](../manuals/vesc-esc-manual.pdf)
- [MgcSTEM LVP-R1.5 Logic](../manuals/low-voltage-protector-manual.pdf)

### **📖 Project Documentation (Markdown)**
Internal documentation optimized for the Wee2-D2 architecture.
- [DFPlayer Mini (Audio Hub)](../hardware/dfplayer-mini-manual.md)
- [GrnWave PSI Logic (LEDs)](../hardware/grnwave-psi-manual.md)
- [goBILDA Drive & Motion](../hardware/gobilda-motor-manual.md)
- [L-faster Hub Motors](../hardware/hub-motor-manual.md)
- [CNBTR Slip Ring Interface](../hardware/cnbtr-slip-ring-manual.md)

---

## 💾 2. System Configuration Files (Firmware & Config)
Direct links to the latest production-verified code and settings.

### **🧠 ESPHome Firmware (YAML)**
- [Sound Hub (Node 1)](../../firmware/production/node-1-sound-hub.yaml)
- [LED Distribution (Node 2)](../../firmware/production/node-2-led-distribution.yaml)
- [Dome Motion (Node 3)](../../firmware/production/node-3-dome-motion.yaml)

### **🛞 VESC Motor Settings (XML)**
- [Left Drive Motor](../../firmware/esc-configs/left-motor-settings.xml)
- [Right Drive Motor](../../firmware/esc-configs/right-motor-settings.xml)
- [Left App Settings](../../firmware/esc-configs/left-app-settings.xml)
- [Right App Settings](../../firmware/esc-configs/right-app-settings.xml)

---

## 🛰️ 3. External Tooling & Cloud Links
Direct links to external tools and cloud-based management systems.

| Resource | URL / Source | Description |
| :--- | :--- | :--- |
| **VESC Tool** | [Download Hub](https://vesc-project.com/vesc_tool) | Desktop interface for motor tuning. |
| **ESPHome Web** | [Flasher Tool](https://web.esphome.io/) | Browser-based firmware injection. |
| **WLED Install** | [Cloud Installer](https://install.wled.me/) | One-click lighting firmware setup. |
| **WLED Project** | [Documentation](https://kno.wled.ge/) | LED pattern and preset guides. |

---

> [!TIP]
> **ACCESS NOTE**: All internal files (`.yaml`, `.xml`) can be downloaded directly from this repository for use in the ESPHome or VESC Desktop tools.
