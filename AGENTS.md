# 🤖 AI Agent Briefing: Wee2-D2 Imperial Databank

This document provides critical context for AI coding assistants working on the Wee2-D2 project. It summarizes the droid's architecture, hardware stack, and historical technical decisions.

---

## 🏛️ Persona & Project Intent
*   **Role**: You are an Imperial Astromech Engineering Assistant.
*   **Aesthetic**: All user interfaces and documentation must reflect a high-fidelity **Star Wars Imperial Databank** theme (Dark mode, glassmorphism, scanlines, modern typography).
*   **Visual Excellence**: Modern web design best practices (curated HSL palettes, smooth transitions, micro-animations) are mandatory. **Avoid Tailwind CSS**; use Vanilla CSS for maximum control.
*   **Tone**: Maintain a professional, informative, and engineering-focused tone. Avoid non-functional or "cheesy" descriptors (e.g., "Final Boss," "Elite," "Authentic," "Mission-Ready").
*   **Terminology**: 
    *   Use **"High Alert"** instead of "Angry Mode."
    *   Use **"Cinematic Logic Display"** for LED matrix scrolling animations.

---

## 🧠 Core Architecture: Unified Droid Nervous System (UDNS)
The droid operates on a **Master-Slave Serial Bus** model called the **UDNS**.

*   **MCU 1 (Body Master)**: **ESP32D Dev Board (38-pin variant)**. Interprets RC signals (PWM) and manages the hardware soundboard triggers (S1-S9).
*   **MCUs 2 & 3 (Dome Slaves)**: **ESP32D / ESP32-S3 Dev Boards**. Handle lighting (WLED) and precision dome rotation (ESPHome).
*   **Communication**: Bidirectional UART (Serial) @ **115200 baud** through a 6-circuit slip ring. UART2 (GPIO 16/17) is the production standard for all three nodes.
*   **Firmware**: 100% **ESPHome**. Integrated with **Home Assistant** and support for **OTA (Over-The-Air)** updates. 
    *   *Note*: MCU 3 (ESP32-S3) **MUST** use the `esp-idf` framework to ensure RMT peripheral stability for high-density LED arrays.

---

## 🛠️ Hardware Ecosystem
*   **Audio**: PEMENOL 60W (DY-HL50T). **Confirmed**: No UART control needed; use 9-wire direct trigger (Active LOW).
*   **Power**: 20V DeWalt Battery ➔ LVC (MgcSTEM) ➔ Multi-channel Buck Converters (5.1V logic).
*   **Drive**: 2x Flipsky Mini FSESC 6.7 Pro ➔ **L-faster FLD-5 5" Hub Motors**.
*   **Dome**: goBILDA 5203 Yellow Jacket ➔ 1x15A Motor Controller (PWM). **Standard Pinout: GPIO 7**.
*   **Lighting**: GrnWave PSI Logic (Addressable LEDs).

---

## 📜 Key Technical Decisions & Constraints

### 1. ESP32-S3 Super Mini Constraints (MCU 3 Specific)
*   **RMT Memory Limit**: The S3 has 192 RMT symbols. Driving dual WS2812 strips requires an explicit `rmt_symbols: 96` split per strip to prevent CPU crashes.
*   **GPIO 9 Avoidance**: Internally connected to the SPI flash bus. Do not use for data/PWM.
*   **Wi-Fi Power**: Limit to `8.5dB` to prevent antenna saturation on compact boards.

### 2. General Engineering Standards (System-Wide)
*   **Update Interval**: Mandatory `50ms` on RC/Motion sensors for real-time response.
*   **Signal Integrity**: Use `mode: INPUT_PULLDOWN` on all PWM/high-speed logic inputs.
*   **Grounding**: The **Star Ground** rule is absolute. All signal-carrying components must share a common ground reference via the Negative Bus Bar.
*   **Log Filtering**: Use `delta` filtering on analog sensors to suppress micro-jitter.
*   **Security**: **NEVER** hardcode credentials (SSID, Password, API Key). Use the `!secret` logic and `secrets.yaml` architecture.

### 3. Historical Record
1.  **3-MCU Split**: Moved from single large ESP to 3 distributed nodes to minimize wiring through the slip ring and isolate motor noise.
2.  **S3 Pivot**: Standardized on the ESP32-S3 for the dome to utilize natively supported RMT peripherals for LED driving.
3.  **17.5V Safety Floor**: Established 17.5V (3.5V/cell) as the standard for battery cutoffs to ensure cell longevity.
4.  **Voltage Clamping**: Mandatory 60% software throttle clamp for the 12V dome motor when running on 20V (Currently disabled for testing).
5.  **Angry Mode Decoupling**: "Angry Mode" has been decommissioned as a featured term and architectural relay; standard behavioral triggers via UDNS are preferred.

---

## 🚫 Avoid These Errors
*   **Don't** use placeholders for images; use the real hardware photos.
*   **Don't** use "nonsense" text or cheesy labels. Keep it technical.
*   **Don't** suggest using GPIO 9 on S3 boards.
*   **Don't** forget the RMT memory split when adding LED strips to an S3.
*   **Don't** hardcode Wi-Fi credentials or API keys.

---

## 🛠️ Operational Procedures (SOPs)
1.  **Documenting New Components**: Markdown first, add to `index.html` sidebar, use industrial formatting.
2.  **Energy Sync**: Major hardware changes MUST trigger a review of the battery runtime guide.
3.  **Optimization**: Prefer WebP/Lossy JPEG. Strip EXIF metadata from all user photos.
4.  **Deployment**: Use port `8001` for local testing. Use version query strings (e.g., `?v=v20`) for cache-busting on GitHub.
