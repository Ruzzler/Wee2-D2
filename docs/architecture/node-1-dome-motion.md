![manual-hero](../../assets/esp32-s3-super-mini.jpg)


# <i data-lucide="cpu"></i> Node 1: Dome Brain

> **TECHNICAL SPECIFICATIONS** | **ROLE: AUTONOMY + DOME MOTION** | **BOARD: ESP32-S3 DEVKITC-1 (N4R2)**


Node 1 is the "brain" of Wee2-D2. It originates every animation the droid plays, drives the dome motor, reads the RC stick + buttons, talks to the LED hub, and coordinates with the sound hub. If the droid is doing anything autonomous, Node 1 is what's driving it.


---


## At a Glance

- **Board**: ESP32-S3 DevKitC-1 (N4R2 — 4 MB flash, 2 MB PSRAM)
- **Powered from**: 5V BEC on the dome motor controller
- **Communicates with**: Node 2 (wireless, bidirectional) + Node 3 (wired, one-way)
- **Physical location**: inside the dome, on the dome motor platform


---


## What's Wired to Which Pin

| GPIO | What's connected | Role |
| :---: | :--- | :--- |
| **GPIO 7** | Dome motor PWM signal | Drives the goBILDA 15A speed controller |
| **GPIO 4** | RC stick (CH1) | Dome left / right from the radio |
| **GPIO 1** | RC button (CH3) | Cycle to next performance |
| **GPIO 6** | RC button (CH4) | Random reaction |
| **GPIO 2** | RC button (CH5) | E-Stop |
| **GPIO 5** | LED hub command line | One-way wired link to Node 3 |
| **GPIO 47** | On-board status LED | Heartbeat / state indicator |


---


## What It Does

- **Picks the next behaviour.** Reads idle level, current mood, what just happened, and chooses between a calm life animation, a more intense attention-seek, or holds for the next operator input.
- **Drives the dome motor.** All dome motion routes through Node 1, whether it's an RC stick override, a performance choreography step, or a small idle wiggle.
- **Pushes lighting presets to Node 3.** Whenever the active animation changes its lighting need, Node 1 pushes the preset over the wired link to Node 3.
- **Relays operator commands to Node 2.** When you tap a sound button on the dashboard or app, that command arrives via Node 2, gets relayed to Node 1, and Node 1 plays its part (motion + lighting) while Node 2 plays the sound.
- **Watches for stuck states.** A built-in watchdog automatically recovers if an animation gets stuck mid-run.


---


## Safety

- **RC transient mute on boot** — the first few RC pulses after power-on are ignored to prevent a stale "stick is moving" reading from triggering an unwanted motion.
- **Mesh dropout pause** — if Node 1 loses contact with Node 2 for more than ~100 ms, dome motion pauses until the link recovers.
- **Brightness clamp on lighting commands** — Node 1 caps any lighting brightness it sends to Node 3 at the safe ~30% maximum before sending.


---


## Maintenance & Debug

- **Wireless log access**: `wee2d2-dome-master.local` on your local Wi-Fi (current setup; eventually moving to a config-less workflow).
- **USB-C** is accessible through the dome hatch for wired log access and OTA fallback.
- **Heartbeat indicator**: Node 1 pings Node 2 every 5 s; if the dashboard's "Node 1 online" badge goes red, Node 1 lost power or crashed.


---


[View Behaviour & Personality](../capabilities/animation-framework.md) | [View Master Schematic](electrical-schematic.md) | [View Power Architecture](power-architecture.md)
