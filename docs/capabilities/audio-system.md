# <i data-lucide="volume-2"></i> Audio System Architecture

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: AUDIO HUB** | **MODEL: DY-HV20T / TPA3118**

This guide covers the audio stack: sound module, ESP-NOW trigger flow, UART pinout, SD card layout, and amplifier configuration. All references verified against firmware v2.12.1.

![TPA3118 Amplifier Module](../../assets/tpa3118-amplifier-module.jpg)

---

## Hardware Components (Audio Hub)

The audio system lives in the body of the droid. Node 2 hosts the audio module + amplifier and drives a single 3.5" full-range speaker.

- **Sound Module**: DY-HV20T (replaced legacy DFPlayer Mini in firmware v2.12.x)
- **Amplifier**: TPA3118 60W mono (PBTL mode)
- **Speaker**: Pyle 3.5" full-range (4 Ohm)
- **Power**: 5V logic rail (Mini560 Pro)

---

## Trigger Flow (ESP-NOW + Local UART)

The droid uses a wireless animation bridge instead of physical signal wires through the slip ring.

1. **Event Capture**: Node 2 captures an event from the Web Dashboard, the BLE bridge (Slice 1B), an RC trigger, or an autonomous script.
2. **Local UART**: Node 2 sends the serial command directly to the DY-HV20T.
3. **ESP-NOW Sync**: Node 2 broadcasts an ESP-NOW packet (e.g. `0xA0` animation ID) so Node 1 can sync dome motion and Node 3 can sync lighting.
4. **Amplification**: DY-HV20T outputs a low-level analog signal to the TPA3118, which drives the 60W speaker from the 20V rail.

---

## Animation Audio Triggers

Audio cues are catalogued in the firmware sound ledger (`Firmware/wee2d2-firmware/sdcard/SD_CARD_LEDGER.md`).

| ESP-NOW Byte | Animation ID | Lighting Sync (WLED) | Audio Character |
| :--- | :--- | :--- | :--- |
| `0xA0` + `0x01` | Idle | Default | Happy / inquisitive |
| `0xA0` + `0x02` | Processing | 1977 analog | Static / thinking |
| `0xA0` + `0x03` | High Alert | Alert red | Alarms / screams |
| `0xA0` + `0x04` | Cantina | Cantina preset | Musical / joyful |
| `0x99` | Stop Sound | n/a | Immediate silence (E-Stop) |

> Forward-looking `0xA3` reaction codes follow the **folder-aligned** convention (not sequential). See `Firmware/.../docs/animation/ANIMATION-ENGINE.md` for the canonical byte table.

---

## SD Card Formatting (DY-HV20T Standard)

Format the microSD as **FAT32**. Folders are `01`–`99`, files are 3-digit-prefixed.

```text
SD_ROOT/
  01/                # Folder 1: Happy
    001_beep_boop.mp3
    002_whistle.mp3
  02/                # Folder 2: Alert
    001_scream.mp3
    002_alarm.mp3
  03/                # Folder 3: Ambient
    001_low_hum.mp3
    002_processing.mp3
  04/                # Folder 4: High Alert (Red)
```

The DY-HV20T supports up to 255 tracks per folder. See `Firmware/wee2d2-firmware/sdcard/SD_CARD_LEDGER.md` for the production sound inventory.

---

## Audio Stack Interconnect (UART)

A 4-wire serial bus connects Node 2 to the DY-HV20T.

| Pin | Source (Node 2 / S3 Mini) | Destination (DY-HV20T) | Role |
| :---: | :--- | :--- | :--- |
| **TX** | GPIO 12 | RX | Serial data out |
| **RX** | GPIO 13 | TX | Status data in |
| **VCC** | 5V rail | VCC | Power (5V/1A peak) |
| **GND** | Star ground | GND | Logic reference |

---

## Ambient Mode

In Ambient Mode (Bank 1), Node 2 fires random tracks from folder `03` every 15–45 s to give the droid an idle "thinking" pulse during downtime.

---

## Practical Maintenance

- **Audio Popping**: if popping appears during motor movement, verify the star-ground at the central negative bus bar.
- **Volume Limit**: TPA3118 can damage the 3.5" driver if gain is set too high. The CLAUDE.md hard safety constraint caps `audio_volume` at 26/30 (verified at the BLE bridge for Slice 1B).
- **Heat**: the mono amplifier warms during long playback. Maintain airflow in the body cavity.

---

**Relevant Hardware & Code:**
- [Node 2: Sound Hub](../architecture/node-2-sound-hub.md)
- [TPA3118 Amplifier](../hardware/tpa3118-amp-manual.md)
- [DY-HV20T Audio Module](../hardware/dy-hv20t-manual.md)

[View Master Schematic](../architecture/electrical-schematic.md) | [View Battery Runtime Guide](../maintenance/battery-runtime-guide.md)
