# <i data-lucide="sun"></i> GrnWave Circular PSI

> **TECHNICAL SPECIFICATIONS**

![GrnWave PSI](../../assets/grnwave-psi-logic.jpg)

The **GrnWave Circular PSI** is a high-density addressable LED display used for the Processor Status Indicators in the dome.

## CRITICAL POWER WARNING

> [!CAUTION]
> **5V DC ONLY**: These boards use **WS2812B-2020** micro-LEDs. They are extremely sensitive to over-voltage. Do not exceed **5.2V**.
> - **DO NOT** power these from the 6V BEC of the goBILDA motor controller.
> - **DO NOT** share power with 6V servos.
> - **ALWAYS** use a high-quality 5V regulator (like the Mini560).

- **LED Type**: WS2812B-2020 (Addressable RGB with integrated IC).
- **Pixel Count**: 76 LEDs per board.
- **Data Sequence**: The LEDs are chained in a specific sequence labeled **D1 through D76** on the PCB.
- **Physical Topology**:
 1. **Outer Ring**: LEDs **D1 - D24** (Clockwise from top-center).
 1. **Inner Ring 1**: LEDs **D25 - D44**.
 1. **Inner Ring 2**: LEDs **D45 - D60**.
 1. **Core / Matrix**: LEDs **D61 - D76** (Central logic cluster).

## Configuration Guide (WLED)

To achieve the cinematic scanning look in **WLED**, use the following settings for **Node 2: Lighting Controller**:

### 1⃣ LED Settings

- **LED Type**: WS2812B
- **Color Order**: GRB
- **Maximum Current**: Set to **2000mA (2A)**.
 - *Why?* 76 LEDs at full brightness (white) can pull over 4.5A, which will overheat the micro-2020 LEDs and potentially melt your 3D-printed housing. 2A provides plenty of brightness for a droid.

### 2⃣ Segment Mapping (Crucial)

Define these segments in the WLED UI to allow for layered animations:

| Segment Name | Start LED | Stop LED | Description |
| :--- | :---: | :---: | :--- |
| **Full PSI** | 0 | 76 | The entire board. |
| **Outer Ring** | 0 | 24 | The boundary ring (Use 'Sweep' or 'Spin'). |
| **Mid & Inner** | 24 | 60 | The intermediate flickering logic rings. |
| **Core** | 60 | 76 | The central logic cluster. |

### 3⃣ Recommended Effects

- **Classic Idle**: Set Segment 0 (Outer) to a slow **Breathing** effect in Blue/Green. Set Segment 2 (Core) to a rapid **Flicker** or **Strobe** in White/Amber.
- **Spinning Disc**: Apply the **Wiper** or **Scan** effect to the **Outer Ring** segment only.
- **2D Matrix**: In WLED's 2D settings, you can define this as a "Ring" layout with a diameter of 10 to create even more complex geometric patterns.

## Pinout & Wiring

The board typically features a 3-pin interface:

| Pin | Label | Function | Connection |
| :--- | :--- | :--- | :--- |
| **1** | **5V / VCC** | Power Input | Connect to **5V Regulator (+) ** |
| **2** | **GND** | Ground | Connect to **Common Ground (-)** |
| **3** | **DIN / DATA** | Data Input | Connect to **Node 2 (ESP32) GPIO** |

## Firmware Configuration (WLED / ESPHome)

- **LED Type**: WS2812B / SK6812.
- **Color Order**: GRB (Standard).
- **Control**: Can be mapped as a 1D segment or a 2D matrix in WLED.