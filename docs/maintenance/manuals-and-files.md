# <i data-lucide="folder"></i> Manuals and Files

Here are all the manuals and configuration files for the Wee2-D2 project.


---


## 1. Technical Manuals

### Hardware Data Sheets (PDF)

These are the original manufacturer specifications for the core hardware.

- [DFPlayer Mini (Sound Hub)](../manuals/dfplayer-mini-manual.pdf)
- [HOTRC DS-600 Transmitter](../hardware/hotrc-ds600-manual.pdf)
- [HOTRC F-06A PWM Receiver](../hardware/hotrc-f06a-manual.pdf)
- [Flipsky Mini FSESC 6.7 Pro](../hardware/flipsky-fsesc-67-pro-manual.pdf)
- [MgcSTEM LVP-R1.5 Logic](../hardware/mgcstem-lvp-r15-manual.pdf)


### Project Documentation (Markdown)

Internal documentation optimized for the Wee2-D2 architecture.

- [DFPlayer Mini (Audio Hub)](../hardware/dfplayer-mini-spec.md)
- [GrnWave PSI Logic (LEDs)](../hardware/grnwave-psi-manual.md)
- [goBILDA Drive & Motion](../hardware/gobilda-motor-manual.md)
- [L-faster Hub Motors](../hardware/hub-motor-manual.md)
- [CNBTR Slip Ring Interface](../hardware/cnbtr-slip-ring-manual.md)


---


## 2. System Configuration Files (Firmware & Config)

The latest code and settings for your droid.


### ESPHome Firmware (YAML)

- [Node 1: Dome Master](../architecture/node-1-dome-motion.md)
- [Node 2: Sound Hub](../architecture/node-2-sound-hub.md)
- [Node 3: LED Distribution](../architecture/node-3-led-distribution.md)


### VESC Motor Settings (XML)

- [Left Drive Motor](../../firmware/esc-configs/left-motor-settings.xml)
- [Right Drive Motor](../../firmware/esc-configs/right-motor-settings.xml)
- [Left App Settings](../../firmware/esc-configs/left-app-settings.xml)
- [Right App Settings](../../firmware/esc-configs/right-app-settings.xml)


---


## 3. External Tooling & Cloud Links

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