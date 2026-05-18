# <i data-lucide="download"></i> Flashing the Firmware

> **TECHNICAL SPECIFICATIONS** | **STATUS: TODAY = DEVELOPER WORKFLOW, FUTURE = ONE-TAP**

This page describes how to get the droid's firmware onto its boards. The long-term goal is for builders to install firmware by downloading a pre-compiled binary and clicking "flash" — never touching code, YAML, or `secrets.yaml`. We're not there yet; today the process is a developer workflow.

---

## Where We're Going (Future)

The plan is to distribute pre-compiled `.bin` files for every board on the droid:

- Node 1 — Dome Brain
- Node 2 — Sound Hub
- Node 3 — LED Hub (stock WLED — already easy to flash via the WLED installer)
- BLE bridge (the small dedicated controller behind the [Dashboard & App](../capabilities/dashboard-and-app.md))

Once the per-build settings (Wi-Fi credentials, MAC addresses for the wireless mesh, OTA password) can be configured at flash time rather than baked into source, a builder will be able to:

1. Plug in a fresh board via USB-C.
2. Open the Wee2-D2 flasher in their browser.
3. Enter Wi-Fi name + password.
4. Click flash.
5. Done.

No code. No `secrets.yaml`. No ESPHome install. No YAML edits.

---

## Where We Are Today

Today, flashing the custom-firmware boards (Node 1 + Node 2 + the BLE bridge) requires the developer workflow — clone the firmware repository, configure local secrets, compile, upload. The firmware repository is currently **private**; it will be published when it's ready for community distribution. Node 3 is already a no-developer-needed install via the WLED browser flasher (see below).

If you have access to the firmware repository, all build instructions live in its own README — this wiki does not duplicate that content because the build workflow changes faster than wiki cadence can keep up with.

---

## Node 3 Today: Already One-Tap

The LED hub (Node 3) runs **stock WLED 0.15.4**, which has an excellent first-party browser installer at <https://install.wled.me>. For builders, flashing Node 3 today already looks like the future flow above:

1. Plug Node 3 into your computer via USB.
2. Open `install.wled.me` in Chrome or Edge.
3. Click Install → pick the correct ESP32 board variant.
4. Done.

After flashing, the cinematic presets specific to Wee2-D2 are loaded from a JSON file via the WLED web UI's Config → Presets page. The preset file is provided alongside the firmware build.

---

## OTA Updates (Once Flashed)

Once the boards have firmware that knows your Wi-Fi, subsequent updates happen wirelessly — no USB cable, no opening the chassis. The boards listen for new firmware on the local network. This is already in place; the gating issue for builders today is just the *initial* setup, not the update loop.

---

## What's Blocking the One-Tap Future

Honest list of what needs to land before "click flash, walk away" works for a fresh builder:

- A web-based flasher UI that prompts for Wi-Fi credentials + MAC addresses at flash time and bakes them in.
- A hosted CI build pipeline that publishes pre-compiled `.bin` files on every firmware release.
- A small wizard for first-boot pairing (Node 1 and Node 2 need to know each other's MAC for the wireless mesh).
- Updated wiki page to replace this one once the flow exists.

These are all known and on the long-term roadmap.

---

**See also:**
- [Network & OTA Configuration](network-ota-guide.md) — wireless update flow once the droid is on Wi-Fi
- [Dashboard & App](../capabilities/dashboard-and-app.md) — operator UI once the droid is flashed
