# Wee2-D2 Bill of Materials (BoM)

A comprehensive list of hardware used in the Wee2-D2 droid project.

## 🧠 Brains & Control
| Component | Qty | Description |
| :--- | :---: | :--- |
| **Node 1/2/3 Logic** | 3 | ESP32-WROOM (Node 1) & ESP32-S3 Mini (Nodes 2/3) |
| [HOTRC DS-600](docs/electrical/hotrc-ds600-manual.md) | 2 | 6-CH Transmitter (Silent Mod), [Local Manual (PDF)](docs/electrical/hotrc-ds600-manual.pdf) |
| [HOTRC F-06A](docs/electrical/hotrc-f06a-manual.pdf) | 2 | RC Receivers (One for body, one for dome), [Local Manual (PDF)](docs/electrical/hotrc-f06a-manual.pdf) |

## 🔋 Power & Protection
| Component | Qty | Description |
| :--- | :---: | :--- |
| **DeWalt 20V Battery** | 1 | Main Power Source |
| **MgcSTEM LVP-R1.5** | 1 | 40A LVC ([Manual PDF](docs/electrical/mgcstem-lvc-manual.pdf)) |
| **Fuse Bus Bar** | 1 | Safety/Distribution |
| **Mini560 5V Buck** | 1 | 20V to 5V Regulator for Dome Lights |
| **5V Buck Converter** | 1 | 20V to 5V Regulator for Body Brain |
| **CNBTR Through-Hole Slip Ring** | 1 | 12.7mm Bore, 6-Circuit @ 10A/each, [Manual](docs/electrical/cnbtr-slip-ring-manual.md) ![Slip Ring](../../assets/cnbtr-slip-ring.jpg) |

## 🔊 Audio & Lights
| **MICROCONTROLLERS** | | | | |
| :--- | :--- | :--- | :--- | :--- |
| **Node 1: Body Brain** | 1 | ESP32D Dev Board | Primary logic, sound triggers | ![ESP32D](../../assets/esp32d-dev-board.png) | [Amazon](https://www.amazon.ca/dp/B0718T2ZK6) |
| **Node 2: Dome Lights** | 1 | ESP32-S3 Super Mini | **WLED** Controller ![S3 Mini](../../assets/esp32-s3-super-mini.jpg) | [Aliexpress](https://www.aliexpress.com/item/1005005967641933.html) |
| **Node 3: Dome Motion** | 1 | ESP32-S3 Super Mini | Dedicated Dome Rotation controller ![S3 Mini](../../assets/esp32-s3-super-mini.jpg) | [Aliexpress](https://www.aliexpress.com/item/1005005967641933.html) |
| Component | Qty | Description |
| :--- | :---: | :--- |
| [PEMENOL 60W Soundboard](docs/electrical/pemenol-60w-voice-manual.md) | 1 | Soundboard w/ 60W Amp ([Amazon](https://www.amazon.ca/dp/B0CGRN3JKF)) |
| **Pyle 3.5" Car Speaker**| 1 | 60W RMS / 4 Ohm |
| **WS2812B Front Logic** | 1 | 12 x 2 Addressable LED matrix |
| **WS2812B Rear Logic** | 1 | 10 x 2 Addressable LED matrix (5x2 x 2) |
| **GrnWave Circular PSI** | 2 | 76x WS2812B-2020 LEDs (**5V ONLY**) [Manual](docs/electrical/grnwave-psi-manual.md) |

## ⚙️ Mechanical / Drive
| Component | Qty | Description |
| :--- | :---: | :--- |
| [Flipsky Mini FSESC 6.7 Pro](docs/electrical/flipsky-fsesc-67-pro-manual.pdf) | 2 | 70A Cont / 200A Peak, [Local Manual (PDF)](docs/electrical/flipsky-fsesc-67-pro-manual.pdf) ![Flipsky ESC](../../assets/flipsky-fsesc-67-pro.jpg) |
| **E-Scooter Hub Motor** | 2 | **L-faster FLD-5 5" Hub Motor** | 200W, 24V, 900 RPM | [Manual](docs/electrical/hub-motor-manual.md) |
| **goBILDA 1x15A Motor Controller** | 1 | 12-24VDC, 15A Cont, 6V BEC [Manual](docs/electrical/gobilda-motor-manual.md) |
| **goBILDA 5203 Motor** | 1 | 117 RPM (12V) Yellow Jacket [Manual](docs/electrical/gobilda-motor-manual.md) |
