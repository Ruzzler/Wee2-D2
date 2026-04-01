# <i data-lucide="graduation-cap"></i> Bill of Materials (BOM)

A comprehensive list of hardware used in the Wee2-D2 project, organized by system tier. Click on any thumbnail in the **Visual ID** column to enlarge it.

## Brains & Control

| Component | Qty | Specifications | Visual ID |
| :--- | :---: | :--- | :--- |
| [Node 1: Sound Hub](architecture/node-1-sound-hub-spec.md) | 1 | ESP32-S3 Super Mini; Audio & Drive Sync | ![S3 Mini](../assets/esp32-s3-super-mini.jpg) |
| [Node 2: LED Distribution](architecture/node-2-led-distribution-spec.md) | 1 | ESP32-Dev Board; **WLED** Matrix Controller | ![ESP32D](../assets/esp32d-dev-board.png) |
| [Node 3: Dome Motion](architecture/node-3-dome-motion-spec.md) | 1 | ESP32-S3 Super Mini; Behavioral Master | ![Node 3 Master](../assets/esp32-s3-super-mini.jpg) |
| [HOTRC DS-600](hardware/hotrc-ds600-manual.md) | 2 | 6-CH Transmitter (Silent Mod) [PDF](hardware/hotrc-ds600-manual.pdf) | ![Transmitter](../assets/hotrc-ds600-transmitter.webp) |
| [HOTRC F-06A Receivers](hardware/hotrc-f06a-manual.md) | 2 | 6-CH PWM Output @ **115200 Baud (UDNS)** [PDF](hardware/hotrc-f06a-manual.pdf) | ![Receiver](../assets/hotrc-f06a-receiver.png) |

## Power & Protection

| Component | Qty | Specifications | Visual ID |
| :--- | :---: | :--- | :---: |
| DeWalt 20V Battery | 1 | 4.0Ah / 80Wh (18.5V - 21.0V) | [Guide](maintenance/battery-runtime-guide.md) |
| [MgcSTEM LVP-R1.5](hardware/mgcstem-lvp-r15-manual.md) | 1 | 40A LVC; **17.5V** Safety Floor [PDF](hardware/mgcstem-lvp-r15-manual.pdf) | ![LVC](../assets/mgcstem-lvp-r15.jpg) |
| Positive Blade Fuse Box | 1 | 20V Positive distribution to main electronics | ![Fuse Box](../assets/fuse-bus-bar.jpg) |
| Negative Bus Bar | 1 | Central Star Ground connection point | ![Negative Bus](../assets/negative-bus-bar.jpg) |
| Mini560 Pro Buck Converter | 2 | 20V to 5V Step-Down (Dome Logic & LEDs) | ![Buck Converter](../assets/mini560-buck-converter.jpg) |
| 5-Port Wago Connectors | 4 | 2x Dome (Power Trunk), 2x Body (Signal/GND) | - |
| [CNBTR Slip Ring](hardware/cnbtr-slip-ring-manual.md) | 1 | 12.7mm Bore, 6-Circuit @ 10A/ch (2x Ganged) | ![Slip Ring](../assets/slip-ring-cnbtr.jpg) |

## Audio & Lights

| Component | Qty | Specifications | Visual ID |
| :--- | :---: | :--- | :---: |
| [DFPlayer Mini](hardware/dfplayer-mini-spec.md) | 1 | UART-Controlled MP3 Module; Node 3 Broadcast Sink | ![DFPlayer](../assets/dfplayer-mini-module.jpg) |
| [TPA3118 Amplifier](capabilities/lights-and-sounds/audio-system.md) | 1 | 60W Mono Amp (Body Hub); Direct analog from DFPlayer | ![TPA3118](../assets/tpa3118-amplifier-module.jpg) |
| [Pyle 3.5" Car Speaker](capabilities/lights-and-sounds/audio-system.md) | 1 | 60W RMS / 4 Ohm High-Output Driver | ![Pyle Speaker](../assets/pyle-3.5-speaker.webp) |
| [WS2812B Logic Arrays](capabilities/lights-and-sounds/led-system.md) | 1 | Addressable LED matrices (Front & Rear) | ![Logic Array](../assets/ws2812b-logic-arrays.webp) |
| [GrnWave Circular PSI](hardware/grnwave-psi-manual.md) | 2 | 76x WS2812B-2020 LEDs (**5V ONLY**) | ![GrnWave PSI](../assets/grnwave-psi-logic.jpg) |

## 3D Print & Mechanical Assembly

| Component | Qty | Specifications | Visual ID |
| :--- | :---: | :--- | :---: |
| [Flipsky Mini FSESC 6.7 Pro](hardware/flipsky-fsesc-67-pro-manual.md) | 2 | 70A Hardware (Throttled to **15A Software**) | ![Flipsky ESC](../assets/flipsky-fsesc-67-pro.jpg) |
| [L-faster FLD-5 Hub Motor](hardware/hub-motor-manual.md) | 2 | 200W, 24V, 900 RPM Brushless Drive | ![Hub Motor](../assets/l-faster-hub-motor.jpg) |
| [goBILDA 1x15A ESC](hardware/gobilda-motor-manual.md) | 1 | 12-24VDC, 15A Cont PWM Controller | ![goBILDA ESC](../assets/gobilda-esc-top.png) |
| [goBILDA 5203 Motor](hardware/gobilda-motor-manual.md) | 1 | 117 RPM (12V Hub) Yellow Jacket Gearmotor | ![Yellow Jacket](../assets/gobilda-5203-motor.webp) |

---

> [!NOTE]
> **TECHNICAL REPOSITORY**: For detailed wiring and signal paths, please refer to the [Interactive Electrical Schematic](architecture/electrical-schematic.md).