# 🧠 MCU 1: Body Controller (Audio & Dispatch)
> **ESPHome Firmware** | **ESP32-WROOM-32D**

The **Body Controller** acts as the central nervous system for Wee2-D2. It decodes PWM signals from the primary RC receiver and translates them into digital triggers for the PEMENOL/DY-HL50T soundboard.

| **Hardware Node** | ESP32-WROOM-32D |
| :--- | :--- |
| **Logic Framework** | ESPHome |
| **Primary Function** | Audio & Dispatch |
| **Visual ID** | ![ESP32D](../../assets/esp32d-dev-board.png) |

## 🚀 Core Features
*   **RC Signal Decoding**: Monitored on CH3, CH4, and CH5.
*   **Bank Switching**: Uses CH5 (3-position or toggle switch) to cycle through 4 distinct sound banks.
*   **Sound Matrix**: Triggers S1-S9 on the soundboard based on current bank and stick position.
*   **Auto-Mode (Bank 4)**: Automatically plays a random sound every 5–15 seconds for "ambient" droid behavior during events.
*   **OTA Updates**: Fully support Over-The-Air updates via the [Imperial Databank Dashboard](docs/maintenance/network-ota-guide.md).

## 🔌 Pinout Configuration
| Connection | ESP32 Pin | Logic |
| :--- | :---: | :--- |
| **RC CH3 (Audio 1)** | GPIO25 | Input |
| **RC CH4 (Audio 2)** | GPIO32 | Input |
| **RC CH5 (Bank Switch)** | GPIO33 | Input |
| **Sound Trigger S1 - S9** | GPIO4, 5, 16-19, 21-23 | Output (Active Low) |
| **Status LED** | GPIO2 | Heartbeat |

## 🛠️ Configuration
The configuration is defined in [`body-brain.yaml`](./body-brain.yaml). 

### Auto-Mode Logic
When the `current_bank` is set to `3` (Bank 4), an internal 1-second interval timer decrements. When it reaches zero, a random trigger is fired and the timer is reset to a value between 5s and 15s.
