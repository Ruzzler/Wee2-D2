# <i data-lucide="bluetooth"></i> Node 4: BLE Bridge

> **TECHNICAL SPECIFICATIONS** | **GATT BRIDGE FOR APP CONTROL** | **PROTOCOL: BLE 0.2.0 (SLICE 1B)** | **VERIFIED AGAINST FIRMWARE v2.12.1**

Node 4 is a dedicated BLE-only ESP32 board that bridges the operator's app + APK ([wee2d2-app](app-ecosystem.md)) to the droid mesh. It hosts the GATT server, accepts command writes from the app, and relays them via ESP-NOW to Node 1 (animations / reactions / lighting / dome speed) and Node 2 (audio + display mode). It also surfaces droid telemetry back to the app over the GATT Status notify characteristic.

The bridge runs **BLE + ESP-NOW only** — no Wi-Fi, no web server. The original "GATT on Node 2" plan was replaced after a coexistence finding (BLE radio + Wi-Fi web server on the same chip degraded both); the dedicated bridge gives the operator a clean app surface without competing with the dashboard.

---

## At a Glance

| Item | Value |
| :--- | :--- |
| **Board** | Dedicated ESP32 (Node 4) |
| **Firmware** | ESPHome `firmware/node-4-bridge.yaml` |
| **Bridge advertising name** | `wee2d2-bridge` |
| **Protocol version** | 0.2.0 (Slice 1B feature parity) |
| **Radios used** | BLE GATT + ESP-NOW (no Wi-Fi) |
| **Range** | ~10 m typical |

---

## GATT Service

| Item | UUID / Value |
| :--- | :--- |
| **Service UUID** | `a6b1c03a-d5cc-4bed-b696-6b91d1dd94a2` |
| **Command characteristic** | `af6c7fa8-b02d-4967-a1ac-3aaa4a02c4de` — WRITE / WRITE_NO_RESPONSE, up to 244 bytes (MTU negotiated) |
| **Status characteristic** | `8098aac9-8b02-4ebb-8ce5-d25bbdcecaed` — READ / NOTIFY, fixed 6-byte payload |
| **Advertising** | Always on (no other workload to suspend it) |

### Frame Format (Commands)

```
+----------+----------+------------------+
| len:1    | type:1   | payload: 0..N    |
+----------+----------+------------------+
```

- `len` — total frame length including this byte (range 2–244)
- `type` — command type (see catalog below)
- `payload` — type-specific bytes (may be zero length)

Validation is strict: empty writes, `len < 2`, declared `len` mismatching actual write size, or unknown `type` are all logged at WARN and silently rejected. Never partial-execute. Never crash. Never emit ESP-NOW.

### Status Notify Payload (6 bytes)

```
Byte 0:  flags         bit 0 = node1_online (1 if heartbeat seen < 15 s ago)
                       bits 1-7: reserved (must be 0)
Byte 1:  anim_id       current animation byte from latest 0xB1 telemetry
Byte 2:  anim_step     current step
Byte 3:  anim_total    total steps in the current animation
Byte 4:  last_react_id last reaction relayed (0 if none since boot)
Byte 5:  reserved      always 0
```

The bridge derives this struct from two upstream packets sent by Node 1 (dual-unicast to both Node 2 AND Node 4):

- `0xB0` — heartbeat every 5 s. Drives the `node1_online` flag (clears 15 s after the last seen ping).
- `0xB1` — full telemetry struct (`anim_id`, `anim_step`, `anim_total`, `last_react_id`). Pushed on every Node 1 animation state change.

---

## Active Command Set (BLE 0.2.0)

| BLE Type | Name | Frame example (hex) | Payload | Relayed ESP-NOW | Target |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `0x01` | E-Stop | `02 01` | (none) | `0xFF` to Node 1 + `0x99` to Node 2 (audio stop fan-out) | Node 1 + Node 2 |
| `0x10` | Animation trigger | `03 10 04` | `[anim_id:1]` | `0xA0 <anim_id>` | Node 1 |
| `0x11` | Reaction trigger | `03 11 06` | `[react_id:1]` | `0xA3 <react_id>` | Node 1 |
| `0x12` | Lighting preset | `03 12 05` | `[preset:1]` | `0xA1 <preset>` | Node 1 → Node 3 (UART) |
| `0x13` | Dome speed | `03 13 32` | `[speed_x100:1]` | `0xA2 <speed_x100>` | Node 1 |
| `0x14` | Volume | `03 14 14` | `[volume:1]` | `0xA5 <volume>` | Node 2 |
| `0x15` | Sound trigger | `03 15 01` | `[trigger_id:1]` | `0xA4 <trigger_id>` | Node 2 |
| `0x21` | Display Mode | `04 21 01 01` | `[subcmd:1][value:1]` | `0xA6 <subcmd> <value>` | Node 2 |

### Argument Constraints

| Type | Valid range |
| :--- | :--- |
| `0x10` Animation | `anim_id ∈ {0x01, 0x03, 0x04, 0x05, 0x10, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x21, 0xFF}` (Node 1 ignores unknown) |
| `0x11` Reaction | `react_id ∈ {0x06, 0x07, 0x09, 0x0A, 0x0F, 0x10, 0x11, 0x12, 0x14, 0x15, 0x16}` — **folder-aligned**, NOT sequential |
| `0x12` Preset | `preset ∈ 0..33` (WLED preset count as of v2.11.2) |
| `0x13` Dome speed | `speed_x100 ∈ 10..100` (Node 1 clamps) |
| `0x14` Volume | `volume ∈ 0..30` — **bridge clamps to ≤ 26** to enforce the CLAUDE.md hard safety constraint. Node 2 clamps again as defence in depth. |
| `0x15` Sound trigger | `trigger_id ∈` sound-trigger table (`0x00 = stop`, `0x01–0x0C = random pools`, then music tracks) |
| `0x21` Display Mode | `subcmd ∈ {0x01, 0x02, 0x03}` (display select / kiosk relay / dimmed preset) |

Reaction codes are folder-aligned, not sequential. Apps must use the exact codes from the list. Authoritative switch lives at `firmware/node-1-dome.yaml` `0xA3 — Reaction trigger`.

### Sound Trigger Pools (`0x15` payload)

| `trigger_id` | Entity | Effect |
| :---: | :--- | :--- |
| `0x00` | `sfx_stop` | Stop all audio gracefully (does NOT clear animations or motor stops) |
| `0x01` | `sfx_random_happy` | random `/HAP/` |
| `0x02` | `sfx_random_sad` | random `/SAD/` |
| `0x03` | `sfx_random_alarm` | random `/ALR/` |
| `0x04` | `sfx_random_scream` | random `/SCR/` |
| `0x05` | `sfx_random_whistle` | random `/WHS/` |
| `0x06` | `sfx_random_hum` | random `/HUM/` |
| `0x07` | `sfx_random_misc` | random `/MSC/` |
| `0x08` | `sfx_random_razz` | random `/RAZ/` |
| `0x09` | `sfx_random_processing` | random `/PRO/` |
| `0x0A` | `sfx_random_ooh` | random sad/ooh subset |
| `0x0B` | `sfx_random_sentences` | random `/SNT/` |
| `0x0C` | `sfx_random_quotes` | random `/QUO/` |

(Music track triggers `0x10+` live in the firmware-side catalog; see `Firmware/wee2d2-firmware/docs/BLE-COMMAND-CATALOG.md` §3.3.)

---

## Pairing & Security (Current Status)

**No on-the-wire authentication as of Slice 1B-bridge.** Any nearby BLE central can connect and write commands. This is an intentional, scoped trade-off:

1. **Toolchain gap.** The `auth_req_mode` YAML key landed in ESPHome 2026.4 (2026-04-15). The operator's installed ESPHome is `2026.2.2`, which predates it. Enabling bonding requires a cross-cutting upgrade.
2. **Web Bluetooth limitation.** Even after the upgrade, ESPHome does not expose a per-characteristic `enforce_security` flag, so Chrome cannot be made to initiate bonding. The "open Chrome → bond once → silent re-pair forever" UX is instead delivered app-side via `navigator.bluetooth.getDevices()`.

**Risk framing**: the droid is for personal/event use, not public infrastructure. The bridge advertises only the command + status characteristics. An attacker in BLE range (≤ 10 m) can fire commands the operator already controls via RC. The worst case (E-Stop fan-out — `0xFF` to Node 1 + `0x99` to Node 2) is recoverable by power-cycling.

**Future work (post-ESPHome upgrade)**: add `auth_req_mode: sc_bond` to `esp32_ble:` in `firmware/node-4-bridge.yaml`, then file an upstream ESPHome PR to land `enforce_security: true` at the characteristic level. Until then, native APKs (Capacitor `@capacitor-community/bluetooth-le`) benefit most from enabling bonding — Chrome Web Bluetooth still won't initiate it.

---

## Reserved (Not Yet Implemented)

Sending these types is logged at WARN as "unknown type" and silently dropped — the catalog is forward-compatible.

| Type | Name | Reason deferred |
| :--- | :--- | :--- |
| `0x20` | Mode toggle | Reserved for future Home/Con runtime mode switch (bridge is BLE-only by design today). |
| `0x30` | Auth handshake | Blocks on the ESPHome ≥ 2026.4 toolchain upgrade above. |
| `0x40+` | Future | Reserved. |

Apps must not depend on any of these.

---

## Versioning

Document version `MAJOR.MINOR.PATCH`:

- **MAJOR** — incompatible wire-format change (e.g. framing redesign)
- **MINOR** — new command type or status payload extension
- **PATCH** — doc-only clarifications

Wire format envelope locked at 0.1.0. The 0.1.1 → 0.2.0 bump added new command types (`0x14` Volume, `0x15` Sound, `0x21` Display Mode) without changing the envelope. An app pinned to 0.1.1 keeps working against a 0.2.0 bridge — it just has no UI for the new commands. Formal compatibility negotiation is deferred until a true wire-format change is needed.

---

**See also:**
- [App & Kiosk Ecosystem](app-ecosystem.md) — how the PWA + Capacitor APK consume this bridge
- [Node Mesh Architecture](node-mesh.md) — ESP-NOW topology the bridge sits on
- [Animation Framework](../capabilities/animation-framework.md) — what the relayed commands trigger
- Authority docs in firmware repo:
  - `Firmware/wee2d2-firmware/docs/BLE-PROTOCOL-SPEC.md`
  - `Firmware/wee2d2-firmware/docs/BLE-COMMAND-CATALOG.md`
