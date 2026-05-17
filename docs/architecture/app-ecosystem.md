# <i data-lucide="smartphone"></i> App & Kiosk Ecosystem

> **TECHNICAL SPECIFICATIONS** | **CONTROL SURFACES: WEB, APK, KIOSK**

Wee2-D2 has three control surfaces beyond the hard-wired HOTRC remotes and the built-in web dashboard: a browser app, a sideloaded Android app, and a public-facing tablet kiosk. This page covers what each surface is for and where they each live.

---

## At a Glance

| Surface | Form | Connection | Audience |
| :--- | :--- | :--- | :--- |
| **PWA (web app)** | Browser-based, no install | Bluetooth via the BLE bridge | Operator on a desktop or Android Chrome |
| **Android APK** | Installed app on the operator's Pixel | Bluetooth via the BLE bridge | Operator on a phone (home-screen icon, sub-2s reconnect) |
| **Public Kiosk** | Browser-based, tablet-mounted | (none — mocked for now) | Convention attendees |

The PWA and the APK share the same code. The Android version is just a native wrapper around the web app to deliver a more reliable Bluetooth reconnect experience on phones.

---

## Web App (PWA)

The browser app talks to the droid over Bluetooth via the [BLE Bridge](ble-bridge.md). It's the source of truth for the operator UI.

### Features

- One-tap **EMERGENCY STOP**
- **Status card**: Node 1 online indicator, current animation, current step, last reaction
- **11 reaction buttons** (Wolf Whistle, Razz, Annoyed, Thinking, Excited, etc.)
- **8 animation triggers** + RETURN TO IDLE banner
- **15 lighting presets** organized by category
- **Dome speed slider** (live, one tap to release)
- **Mid-session reconnect** with backoff if the link briefly drops

### Browser Support

| Browser | Desktop | Android |
| :--- | :---: | :---: |
| Chrome 56+ | yes | yes |
| Edge 79+ | yes | yes |
| Firefox | no | no |
| Safari (incl. iOS) | no | no |

iOS is not on the roadmap.

---

## Android APK (Wee2-D2 native app)

The native Android app exists because Bluetooth reconnect on stable browser Chrome is not reliable enough for at-venue use. The native version delivers the "tap home-screen icon → connected in under 2 seconds → no device picker" experience that operators actually need.

The native app is functionally identical to the PWA — same buttons, same controls — just packaged as an installable app that Android can launch directly and that has proper Bluetooth permissions.

---

## Public Interaction Kiosk

A tablet-mounted prototype designed for convention appearances. It presents a thematic "Astromech Diagnostic Terminal" experience to passing attendees so they can interact with the droid without needing the operator to hand over the actual remote.

Current state is a **mocked prototype** — features simulate droid interactions but do not yet wire through to the BLE bridge or the web dashboard. Treat it as a UX reference for the eventual full integration.

### Mocked Features
- **Astromech Translator** — type a question, get a stylized R2 response
- **System Diagnostics** — themed "tests" against dome / lights / motivators
- **Holographic Data** — themed "restricted" messages
- **Mood Matrix** — real-time personality vital animation

### Deployment
Open `index.html` on a tablet browser. Recommended:
- Guided Access / Kiosk Mode to lock the browser
- Add to Home Screen as a PWA for fullscreen
- Landscape orientation

---

## Long-Term: Configuration-Free Installation

Today, setting up the app means hosting the PWA on HTTPS (for browser Bluetooth permissions) or sideloading the Android APK. The long-term direction is a one-tap install path with no developer setup required. The PWA already lives in a public-facing repo; the APK delivery channel is the next thing to harden.

---

**See also:**
- [BLE App Control](ble-bridge.md) — how the app talks to the droid
- [Web Control Dashboard](../capabilities/web-control-dashboard.md) — on-droid web UI (separate from the app)
- [Behaviour & Personality](../capabilities/animation-framework.md) — what the buttons actually trigger
