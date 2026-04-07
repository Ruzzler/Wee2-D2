# <i data-lucide="lightbulb"></i> Node 3: LED Distribution

> **TECHNICAL SPECIFICATIONS** | **WLED v0.14** | **ESP32D Dev Board** | **Visual Output Hub**

| Component | Detail |
| :--- | :--- |
| **Node ID** | **3** |
| **Role** | Cinematic Visual Output & Peripheral Sync |
| **Source Code** | [`node-3-wled/`](../../firmware/production/node-3-wled/) |
| **Logic Framework** | WLED (Native) |
| **Primary Function** | Addressable LEDs |
| **Visual ID** | ![ESP32D](../../assets/esp32d-dev-board.png) |
| **Sync Protocol** | **UART (Serial)** |
| **Status LED** | **GPIO 2** |

## Power Management & Safety

> [!IMPORTANT]
> To protect the **Dome LED Buck: Mini560 Pro (5A)** from overheating or melting during high-intensity light shows (e.g., full-white flashes), the WLED brightness limiter **MUST** be enabled.

- **Current Limit**: Clamp to **3500mA** in the WLED "LED Preferences" menu.
- **Hardware**: Dome LED Buck: Mini560 Pro (5A) powered by 20V from the slip ring.

| Device | LED Type | Qty | wire Color | Pin (GPIO) |
| :--- | :--- | :---: | :---: | :---: |
| **Front Logic** | WS2812B | 20 | Yellow | **18** |
| **Rear Logic** | WS2812B | 24 | Yel/Blk | **19** |
| **Front PSI** | GrnWave | 76 | Green | **21** |
| **Back PSI** | GrnWave | 76 | White | **22** |

> [!CAUTION]
> **VOLTAGE SENSITIVITY**: The GrnWave PSI boards use micro 2020-size LEDs that are extremely sensitive. **Do not exceed 5.0V**. Powering them from the 6V BEC of the motor controller will cause immediate failure. Use the dedicated **Dome LED Buck: Mini560 Pro (5A)**.

## WLED 2D Configuration

To achieve the cinematic logic scrolling seen in the [Automations](../capabilities/automations.md), ensure your segment mapping matches the firmware's expected indices:

| Segment ID | Component | Pixels | Role |
| :---: | :---: | :---: | :--- |
| **0** | **Front PSI** | 0 - 76 | Primary Visual Feedback |
| **1** | **Rear PSI** | 76 - 152 | Secondary Visual Feedback |
| **2** | **Front Logic** | 152 - 172 | High-Speed Logic Matrix (10x2) |
| **3** | **Rear Logic** | 172 - 196 | High-Speed Logic Matrix (12x2) |

---

## Behavioral Heartbeat (Serial Sync)

Node 3 acts as a "listening node" for the **Dome Master (Node 1)**.

- **Serial Mode**: WLED is set to **JSON Serial** mode (115200 Baud).
- **Hardwired Link**: GPIO 16 (Node 3 RX) is tied to GPIO 5 (Node 1 TX).
- **Heartbeat Pulsing**: Node 1 sends a diagnostic pulse `{"v":true}` (Version Request) every **60 seconds**. This prevents the UART bus from entering a sleep or "timeout" state during long periods of idle operation.
- **Trigger Execution**: Preset transitions (e.g. `{"ps":10}`) are handled instantly over this bus with <15ms latency.

> [!TIP]
> **[WLED Configuration Guide](../maintenance/wled-configuration-guide.md)**
> Master guide for setting up segments, presets, and sync triggers on Node 3.

- **Total Pixels**: ~200 LEDs.
- **PSI Boards**: 2x Grnwave PSI boards.
- **Support Strips**: 1x 12-pixel strip, 2x 5-pixel strips.

## WLED Serial Sync

This Node receives high-level commands from **Node 1 (Dome Master)** via a hardwired UART connection.
- **Data Signal**: Connect the Blue wire (Node 1 TX) to **GPIO 16**.
- **Response Signal**: Connect the Green wire (Node 3 TX) to **Node 1 RX** (Optional).
- **Protocol**: 115200 Baud, 8N1. WLED is configured to react to serial JSON payloads representing the 15 standard Cinematic Logic states.

## Useful Links

- [WLED Documentation](https://kno.wled.ge/)
- [Grnwave PSI Setup Guide](https://grnwave.com/)