# <i data-lucide="sun"></i> LED Arrays & Displays

> **TECHNICAL SPECIFICATIONS** | **WS2812B LOGIC** | **ADDRESSABLE MATRIX**

The visual setup is powered by high-density **WS2812B addressable LED** matrices, controlled by **Node 3 (LED Distribution)** running the **WLED** framework. Synchronized visual behaviors (e.g., "High Alert" red pulsing) are triggered via UART directly from the **Dome Motion Master (Node 1)**.


## Power Constraints

Because there are hundreds of LEDs in the dome, they have their own dedicated **Dome LED Buck: Mini560 Pro (5A)** tied to the 20V Ganged Wago Hub.

> [!CAUTION]
> The LED matrices (especially the GrnWave PSIs) will instantly blow if exposed to more than 5.2V. By using the **Dual-Buck Strategy**, we isolate these high-current light sweeps from the sensitive logic pins of the ESP32.


## Cinematic Lighting Presets

Wee2-D2 features **15 hard-coded cinematic logic states** stored as WLED presets on Node 3. These states can be triggered manually via the [Neural Dashboard](../architecture/node-2-sound-hub.md) or automatically during behavioral animations.

| ID | Preset Name | Visual Profile | Operational Context |
| :---: | :--- | :--- | :--- |
| **0** | **All Off** | Total Blackout | Power Save / Stealth |
| **1** | **1977 Idle** | Classic Blue/Teal Scroll | Standard Operation |
| **2** | **Neural Proc** | Rapid Cyan Logic Pulse | Thinking / Calculating |
| **3** | **Alert Red** | Sychronized Red Logic Flash | Emergency / Combat |
| **4** | **Legacy Mode** | Static 1977 Colors | Low Power Logics |
| **5** | **Front Only** | Front Logic Only (20px) | Component Test |
| **6** | **Rear Only** | Rear Logic Only (24px) | Component Test |
| **7** | **PSI Scan** | Dual-PSI Alternating Pulse | Sensor Sweep |
| **8** | **Data Transfer**| High-Speed White Logic Jitter | Link Established |
| **9** | **Leia Message** | Dim Blue Logic Flicker | Holo-Projection Playback |
| **10** | **Disco Mode** | RGB Rainbow Cycle | Dance / Celebration |
| **11** | **Stealth** | Dimmed Single-Pixel Logic | Night Ops |
| **12** | **Startup Seq** | Cascading Logic Wipe | System Boot |
| **13** | **Malfunction** | Random Red/Orange Static | System Error |
| **14** | **Celebration** | Gold/White Shimmer | Victory / Taunt |
| **15** | **Imperial March**| Slow Red Logic Fade | Opposing Force Detected |


---


## Physical LED Mapping

The LEDs are split across four primary data lines emitting from Node 3:

| Display | Type | Configuration | Pin (GPIO) | Wire Color |
| :--- | :--- | :--- | :---: | :--- |
| **Front Logic** | WS2812B | 10x2 Matrix (20 pixels) | **16** | Green |
| **Rear Logic** | WS2812B | 12x2 Matrix (24 pixels) | **17** | White |
| **Front PSI** | GrnWave | Circular (76 pixels) | **18** | Yellow |
| **Back PSI** | GrnWave | Circular (76 pixels) | **19** | Yel/Blk |


## WLED 2D Setup

To achieve cinematic animations, the WLED interface is configured using **2D Matrix segments**.

1. Even though the Rear Logic is physically split into two square windows, treating them as one consecutive 10x2 strip in WLED allows scanning animations to flow across both windows.
2. The [GrnWave PSIs](../../hardware/grnwave-psi-manual.md) are mapped by concentric rings (Outer, Inner, Core) to allow layered breathing and strobing effects.


## Cinematic Presets Ledger

The Web Dashboard sends hex IDs (0xA1) corresponding to these static presets within Node 3's WLED `presets.json` memory.

| Preset ID | Scene Name | Description / Dashboard Trigger |
| :---: | :--- | :--- |
| **1** | Default Boot / Idle | Neutral blues and soft white. |
| **2** | 1977 | Aggressive analog flicker and yellowing. |
| **3** | High Alert | Fast red pulsing across all matrices. |
| **4** | Cantina | Vibrant, rapid multicolored cycling. |
| **5-15** | Expansion | Reserved for behavioral automations. |


---


**Relevant Hardware & Code:**
- [Node 3: LED Distribution](../../architecture/node-3-led-distribution.md)
- [Node Pinout Guide](../../architecture/node-pinout-guide.md)