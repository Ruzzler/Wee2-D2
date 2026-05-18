![wee2d2-hero](assets/droid-actual.jpg)


# <i data-lucide="folder-git"></i> Wee2-D2

> **TECHNICAL SPECIFICATIONS** | **CUSTOM ESP32-S3 R2 ASTROMECH** | **BUILDER DOCUMENTATION**


**Wee2-D2** is a custom-built, active-duty astromech droid built in 2025 for use with the Badlands Droid Builders and the 501st Legion's Badlands Garrison. This repository is the public builder documentation — schematics, BOM, hardware manuals, wiring, and operator guides. The droid's firmware lives in a separate repository.

The chassis is built from the acclaimed 3D files by Mr. Baddeley.


---


## <i data-lucide="external-link"></i> Live Wiki

The documentation in this repo is rendered live at:

**[https://ruzzler.github.io/Wee2-D2/](https://ruzzler.github.io/Wee2-D2/)**

That is the intended way to read these docs — the sidebar, schematic, image lightbox, and search-friendly URLs work there. Reading the raw Markdown on GitHub also works but skips the rendering.


---


## What's Inside

```text
Wiki-Repository/
├── docs/
│   ├── architecture/      # System design, mesh, schematic, node pages
│   ├── capabilities/      # What the droid does — sound, lights, behaviour, dashboard
│   ├── hardware/          # Component manuals + specs
│   └── maintenance/       # Calibration, OTA updates, flashing, troubleshooting, safety
├── assets/                # Hardware photos + module diagrams (SVG / WebP / JPG / PNG)
├── system/                # SPA renderer (vanilla JS + CSS, no build step)
├── wiki/                  # Project overview
├── index.html             # SPA entry point
├── restoration_*.md       # Build journal
├── CHANGELOG.md           # Wiki release history
└── README.md              # This file
```

Companion projects (separate repositories):

- **Firmware** — ESPHome firmware that runs on the droid. Currently private; will be published when ready for community distribution.
- **Web App (PWA)** — Web Bluetooth control panel.
- **Android APK** — Capacitor wrap of the web app for at-venue use.


---


## <i data-lucide="hard-drive"></i> Hardware Ecosystem

Each link is a high-density manual with pinouts and wiring.

- **Piloting**: [HOTRC DS-600 transmitter](docs/hardware/hotrc-ds600-manual.md) + [F-06A receivers](docs/hardware/hotrc-f06a-manual.md)
- **Drive**: [Flipsky Mini FSESC 6.7 Pro](docs/hardware/flipsky-fsesc-67-pro-manual.md) driving 2x [L-faster FLD-5 hub motors](docs/hardware/hub-motor-manual.md)
- **Dome motion**: [goBILDA 5203 Yellow Jacket](docs/hardware/gobilda-motor-manual.md) on Node 1 GPIO 7
- **Audio**: [DY-HV20T audio module](docs/hardware/dy-hv20t-manual.md) → [TPA3118 60W amplifier](docs/hardware/tpa3118-amp-manual.md) → Pyle 3.5" speaker
- **Power**: [MgcSTEM LVP-R1.5 LVC](docs/hardware/mgcstem-lvp-r15-manual.md) on a 20V DeWalt trunk with a central star ground bus
- **Lighting**: [GrnWave PSI rings](docs/hardware/grnwave-psi-manual.md) + WS2812B Logic Display matrices, driven by Node 3 (classic ESP32D running stock WLED 0.15.4, 196 LEDs total)
- **Slip ring**: [CNBTR 6-circuit](docs/hardware/cnbtr-slip-ring-manual.md) ganged for high-current trunk + future telemetry headroom


---


## <i data-lucide="map"></i> Where to Start

If you're considering building one:
1. **[Interactive Electrical Schematic](docs/architecture/electrical-schematic.md)** — full system map with click-through to component manuals
2. **[Bill of Materials](docs/bill-of-materials.md)** — every part with images + links
3. **[3D Print & Assembly](docs/mechanical/3d-print-assembly.md)** — chassis build notes

If you have one built and want to know how to use it:
1. **[Dashboard & App](docs/capabilities/dashboard-and-app.md)** — operator control surfaces
2. **[Behaviour & Personality](docs/capabilities/animation-framework.md)** — what the droid does autonomously
3. **[Flashing the Firmware](docs/maintenance/flashing-firmware.md)** — installation path (today vs future)
4. **[Battery Runtime Guide](docs/maintenance/battery-runtime-guide.md)** — endurance estimates
5. **[Calibration & Safety](docs/maintenance/calibration-guide.md)** — pre-deployment checklist


---


[View Full Bill of Materials](docs/bill-of-materials.md) | [View Project Changelog](CHANGELOG.md) | [View Firmware Version History](VERSION_HISTORY.md)
