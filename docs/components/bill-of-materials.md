# Wee2-D2 Bill of Materials (BoM)

A comprehensive list of hardware used in the Wee2-D2 droid project.

## 🧠 Brains & Control
| Component | Qty | Specifications & Project Documentation |
| :--- | :---: | :--- |
| **Node 1: Body Brain** | 1 | ESP32D Dev Board; primary logic/sound triggers ![ESP32D](../../assets/esp32d-dev-board.png) |
| **Node 2: Dome Lights** | 1 | ESP32-S3 Super Mini; **WLED** Controller ![S3 Mini](../../assets/esp32-s3-super-mini.jpg) |
| **Node 3: Dome Motion** | 1 | ESP32-S3 Super Mini; Dedicated Dome Rotation ![S3 Mini](../../assets/esp32-s3-super-mini.jpg) |
| [HOTRC DS-600](docs/electrical/hotrc-ds600-manual.md) | 2 | 6-CH Transmitter (Silent Mod), [Local PDF](docs/electrical/hotrc-ds600-manual.pdf) |
| [HOTRC F-06A](docs/electrical/hotrc-f06a-manual.pdf) | 2 | 6-CH RC Receivers, [Local PDF](docs/electrical/hotrc-f06a-manual.pdf) |

## 🔋 Power & Protection
| Component | Qty | Specifications & Project Documentation |
| :--- | :---: | :--- |
| **DeWalt 20V Battery** | 1 | 4.0Ah / 80Wh Lithium-ion nominal (18.5V - 21.0V) |
| **MgcSTEM LVP-R1.5** | 1 | 40A LVC; **17.5V** Safety Floor, [Manual PDF](docs/electrical/mgcstem-lvc-manual.pdf) |
| **Fuse Bus Bar** | 1 | Multi-circuit safety distribution |
| **Buck Converter (Dome)** | 1 | Mini560 20V to 5V Regulator |
| **Buck Converter (Body)** | 1 | Standard 20V to 5V Regulator |
| [CNBTR Slip Ring](docs/electrical/cnbtr-slip-ring-manual.md) | 1 | 12.7mm Bore, 6-Circuit @ 10A/ch ![Slip Ring](../../assets/cnbtr-slip-ring.jpg) |

## 🔊 Audio & Lights
| Component | Qty | Specifications & Project Documentation |
| :--- | :---: | :--- |
| [PEMENOL 60W Soundboard](docs/electrical/pemenol-60w-voice-manual.md) | 1 | DY-HL50T; Integrated 60W AMP, 8-bit Trigger |
| **Pyle 3.5" Car Speaker**| 1 | 60W RMS / 4 Ohm High-Output Driver ![Pyle Speaker](../../assets/pyle-3.5-speaker.webp) |
| **WS2812B Logic Arrays** | 1 | Addressable LED matrices (Front & Rear) |
| [GrnWave Circular PSI](docs/electrical/grnwave-psi-manual.md) | 2 | 76x WS2812B-2020 LEDs (**5V ONLY**) ![GrnWave PSI](../../assets/grnwave-psi-logic.jpg) |

## ⚙️ Mechanical / Drive
| Component | Qty | Specifications & Project Documentation |
| :--- | :---: | :--- |
| [Flipsky Mini FSESC 6.7 Pro](docs/electrical/flipsky-fsesc-67-pro-manual.md) | 2 | 70A Cont / 200A Peak, VESC 6.6 base, [PDF](docs/electrical/flipsky-fsesc-67-pro-manual.pdf) ![Flipsky ESC](../../assets/flipsky-fsesc-67-pro.jpg) |
| [L-faster FLD-5 Hub Motor](docs/electrical/hub-motor-manual.md) | 2 | 200W, 24V, 900 RPM Brushless Drive ![Hub Motor](../../assets/l-faster-hub-motor.jpg) |
| [goBILDA 1x15A ESC](docs/electrical/gobilda-motor-manual.md) | 1 | 12-24VDC, 15A Cont PWM Motor Controller |
| [goBILDA 5203 Motor](docs/electrical/gobilda-motor-manual.md) | 1 | 117 RPM (12V Hub) Yellow Jacket Gearmotor |
