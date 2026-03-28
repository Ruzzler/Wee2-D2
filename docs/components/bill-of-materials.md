# Wee2-D2 Bill of Materials (BoM)

A comprehensive list of hardware used in the Wee2-D2 droid project.

## 🧠 Brains & Control
| Component | Qty | Description |
| :--- | :---: | :--- |
| **ESP32 Dev Board** | 3 | Node 1 (Audio), Node 2 (Lights), Node 3 (Motion) |
| **HOTRC DS-600** | 1 | 6-CH Transmitter (**Silent Mode Mod / No Beeps**) [Manual](docs/electrical/hotrc-ds600-manual.md) |
| **HOTRC F-06A** | 2 | RC Receivers (One for body, one for dome) |

## 🔋 Power & Protection
| Component | Qty | Description |
| :--- | :---: | :--- |
| **DeWalt 20V Battery** | 1 | Main Power Source |
| **MgcSTEM LVP-R1.5** | 1 | 40A LVC ([Manual PDF](docs/electrical/mgcstem-lvc-manual.pdf)) |
| **Fuse Bus Bar** | 1 | Safety/Distribution |
| **Mini560 5V Buck** | 1 | 20V to 5V Regulator for Dome Lights |
| **5V Buck Converter** | 1 | 20V to 5V Regulator for Body Brain |
| **CNBTR Through-Hole Slip Ring** | 1 | 12.7mm Bore, 6-Circuit @ 10A/each, [Manual](docs/electrical/cnbtr-slip-ring-manual.md) |

## 🔊 Audio & Lights
| Component | Qty | Description |
| :--- | :---: | :--- |
| **DY-HL50T** | 1 | Soundboard w/ 60W Amp [Manual](docs/electrical/dy-hl50t-manual.md) |
| **Pyle 3.5" Car Speaker**| 1 | 60W RMS / 4 Ohm |
| **WS2812B Front Logic** | 1 | 12 x 2 Addressable LED matrix |
| **WS2812B Rear Logic** | 1 | 10 x 2 Addressable LED matrix (5x2 x 2) |
| **GrnWave Circular PSI** | 2 | 76x WS2812B-2020 LEDs (**5V ONLY**) [Manual](docs/electrical/grnwave-psi-manual.md) |

## ⚙️ Mechanical / Drive
| Component | Qty | Description |
| :--- | :---: | :--- |
| **Flipsky Mini FSESC 6.7 Pro** | 2 | 70A Cont / 200A Peak, [Manual](docs/electrical/flipsky-fsesc-67-pro-manual.md) |
| **E-Scooter Hub Motor** | 2 | Drive Motors |
| **goBILDA 1x15A Motor Controller** | 1 | 41g, 12-24VDC (9-30V Limit), 15A Cont / 25A Throttle, 6V/3A BEC, 1050-1950μsec PWM, Reverse-Voltage/Over-Current/Heat Protection |
| **goBILDA 5203 Motor** | 1 | 117 RPM (12V), 50.9:1 Ratio, 68.4 kg.cm Torque, 9.2A Stall |
