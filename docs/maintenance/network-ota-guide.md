# <i data-lucide="wifi"></i> Network & OTA Updates

> **TECHNICAL SPECIFICATIONS** | **WIRELESS FIRMWARE UPDATES** | **NODE WEB INTERFACES**

Once Wee2-D2 has been flashed once and joined a Wi-Fi network, all subsequent firmware updates happen wirelessly — no USB cable, no opening the chassis. This page covers the OTA update flow from an operator perspective.

For initial flashing (the developer workflow + future one-tap path), see [Flashing the Firmware](flashing-firmware.md).

---

## Where Each Board Lives on the Network

Each board hosts a small web interface for status + OTA upload, reachable on the local network.

| Board | mDNS hostname |
| :--- | :--- |
| Node 1 — Dome Brain | `wee2d2-dome-master.local` |
| Node 2 — Sound Hub | `wee2d2-sound-hub.local` |
| Node 3 — LED Hub | `wled-dome.local` (WLED's own UI) |

If mDNS is blocked on your network (some guest Wi-Fi setups), look up each board's DHCP-assigned IP address in your router and use that instead.

---

## Updating a Board

1. Browse to the board's hostname (or IP) in any modern browser.
2. Scroll to the **OTA Update** section.
3. Click "Choose File" and pick the new `.bin` for that board.
4. The board accepts the upload, verifies it, and reboots into the new firmware.

**Do not power-cycle the droid during an OTA upload.** If an upload is interrupted mid-stream, the board automatically rolls back to its previous working firmware on next boot — but you'll have to start the upload over.

---

## Recovery from a Failed Update

If a board fails to rejoin Wi-Fi after an update (rare, usually means the build had a config mistake), it launches a fallback access point named `WEE2-D2_SETUP`. Connect to that AP, browse to `http://192.168.4.1`, and you can either reconfigure Wi-Fi or roll back to the previous firmware.

The fallback AP is built in — you cannot get a droid into a bricked state via OTA alone. Worst case: connect to the AP and recover.

---

## Range & Signal

Updates work best when the droid is within ~10 feet of the Wi-Fi router. The OTA transfer is small (around 1 MB) but the board needs a stable connection through the full upload. If the operator dashboard shows weak signal, move closer before starting the update.

---

## Where to Get `.bin` Files

Today, `.bin` files are produced from the firmware repository on the operator's local build machine. The long-term plan is to publish pre-compiled binaries on a release page so builders can download and OTA directly — see [Flashing the Firmware](flashing-firmware.md) for the roadmap.

---

[View Troubleshooting](troubleshooting.md) | [View Master Schematic](../architecture/electrical-schematic.md)
