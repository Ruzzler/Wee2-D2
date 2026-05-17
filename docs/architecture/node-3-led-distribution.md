![manual-hero](../../assets/esp32d-dev-board.png)


# <i data-lucide="lightbulb"></i> Node 3: LED Hub

> **TECHNICAL SPECIFICATIONS** | **ROLE: ADDRESSABLE LED DRIVER** | **BOARD: ESP32D DEVKIT (CLASSIC ESP32)** | **RUNS: STOCK WLED**


Node 3 is the dedicated lighting controller. It runs **stock WLED** (the popular open-source LED firmware) on a classic single-core ESP32D board and drives all four addressable LED strips on the dome. Node 3 takes simple lighting instructions over a single wire from Node 1; it does not run any custom Wee2-D2 code itself — only WLED plus a curated set of cinematic presets.


---


## At a Glance

- **Board**: ESP32D DevKit (classic ESP32 — not the same chip family as Nodes 1 + 2)
- **Firmware**: stock WLED 0.15.4
- **Powered from**: 5V from the dedicated dome LED buck converter
- **Communicates with**: Node 1 (wired, one-way)
- **Physical location**: dome, above the slip ring


---


## What's Wired to Which Pin

| GPIO | What's connected | Role |
| :---: | :--- | :--- |
| **GPIO 16** | Front PSI strip | 76 LEDs |
| **GPIO 17** | Rear PSI strip | 76 LEDs |
| **GPIO 18** | Front Logic Display | 20 LEDs (10x2 matrix) |
| **GPIO 19** | Rear Logic Display | 24 LEDs (12x2 matrix) |
| **GPIO 3 (RX0)** | Command line from Node 1 | Wired one-way input |

Total **196 addressable LEDs** across 4 strips.


---


## What It Does

- **Holds 15 cinematic presets** (Idle, Alert Red, Disco, Imperial March, etc.). See the [LED System](../capabilities/led-system.md) page for the full catalog.
- **Responds to preset changes from Node 1** within ~10 ms — fast enough to feel synchronized with sound + motion.
- **Provides a standalone web UI** for tuning presets, palettes, and segment maps without needing to redeploy firmware.


---


## Safety

- **Global brightness cap (~30%)** — enforced inside WLED itself AND on every command Node 1 sends. Protects the GrnWave PSI matrices from over-voltage.
- **Dedicated LED power rail** — separate buck converter from the logic rail. A heavy LED draw cannot sag the ESP32 supply.
- **All grounds tied** at the dome distribution point — required for clean LED data signals.


---


## Maintenance & Debug

- **Web UI**: browse to Node 3's IP address (look it up in your router's DHCP list, or use `wled-dome.local` if mDNS works on your network). All preset tuning happens here.
- **micro-USB** on the ESP32D DevKit for serial monitor access. Note: the USB-Serial chip shares a pin with the command line from Node 1, so keep USB unplugged during normal operation.
- **Flickering** — usually a sag on the LED 5V rail under full brightness. Verify the rail holds steady.
- **One strip dark** — check that strip's data wire and ground at the dome distribution hub.


---


[View LED System Guide](../capabilities/led-system.md) | [View WLED Configuration Guide](../maintenance/wled-configuration-guide.md) | [View Master Schematic](electrical-schematic.md)
