# 📚 Manuals and Files
> **TECHNICAL REPOSITORY** | **CORE DATA HUB**

Welcome to the centralized Manuals and Files Hub. This page provides rapid access to all documentation, firmware, and configuration assets for the Wee2-D2.

---

## 📜 1. Technical Manuals
Comprehensive guides for hardware integration and system capabilities.

### **📦 Hardware Data Sheets (PDF)**
These are the original manufacturer specifications for the core hardware.
- [HOTRC DS-600 Transmitter](../hardware/hotrc-ds600-manual.pdf)
- [HOTRC F-06A PWM Receiver](../hardware/hotrc-f06a-manual.pdf)
- [Flipsky Mini FSESC 6.7 Pro](../hardware/flipsky-fsesc-67-pro-manual.pdf)
- [MgcSTEM LVP-R1.5 Logic](../hardware/mgcstem-lvp-r15-manual.pdf)

### **📖 Imperial Guides (Markdown)**
Internal documentation optimized for the Wee2-D2 architecture.
- [DFPlayer Mini (Audio Hub)](../hardware/dfplayer-mini-manual.md)
- [GrnWave PSI Logic (LEDs)](../hardware/grnwave-psi-manual.md)
- [goBILDA Drive & Motion](../hardware/gobilda-motor-manual.md)
- [L-faster Hub Motors](../hardware/hub-motor-manual.md)
- [CNBTR Slip Ring Interface](../hardware/cnbtr-slip-ring-manual.md)

---

## 💾 2. Droid Files (Firmware & Config)
Direct links to the latest production-verified code and settings.

### **🧠 ESPHome Firmware (YAML)**
- [Body Audio Hub (Node 1)](../../firmware/mcu1-body-controller/body-brain.yaml)
- [Dome Master (Node 3)](../../firmware/mcu3-motion-controller/dome-motion.yaml)
- [Dome Nervous System Template](../../firmware/dome-nervous-system-template.yaml)

### **🛞 VESC Motor Settings (XML)**
- [Left Drive Motor](../../firmware/mcu1-body-controller/esc-settings/Left_Motor_Settings.xml)
- [Right Drive Motor](../../firmware/mcu1-body-controller/esc-settings/Right_Motor_Settings.xml)
- [Left App Settings](../../firmware/mcu1-body-controller/esc-settings/Left_App_Settings.xml)
- [Right App Settings](../../firmware/mcu1-body-controller/esc-settings/Right_App_Settings.xml)

---

## 🛰️ 3. Imperial Cloud Uplinks
Direct links to external tools and cloud-based management systems.

| Resource | Logic Path | Description |
| :--- | :--- | :--- |
| **VESC Tool** | [Download Hub](https://vesc-project.com/vesc_tool) | Desktop interface for motor tuning. |
| **ESPHome Web** | [Flasher Tool](https://web.esphome.io/) | Browser-based firmware injection. |
| **WLED Install** | [Cloud Installer](https://install.wled.me/) | One-click lighting firmware setup. |
| **WLED Project** | [Documentation](https://kno.wled.ge/) | LED pattern and preset guides. |

---

> [!TIP]
> **ACCESS NOTE**: All internal files (`.yaml`, `.xml`) can be downloaded directly from this repository for use in the ESPHome or VESC Desktop tools.
