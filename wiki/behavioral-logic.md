# Wee2-D2 Behavioral Logic
> **MAINTENANCE & OPERATIONS** | **v2.1.0-Zero-Infra Technical Overview**

The Wee2-D2 droid uses a modular behavior system based on **ESPHome States** and **Wireless Triggers**. This architecture allows for cinematic, synchronized audio and lighting changes across all MCU nodes without direct physical connections.

### Behavioral Logic (Node 3)
Behavioral states are primarily managed by **Node 3 (Dome Motion)** and broadcasted to other hubs via the **ESP-NOW** bridge.

### Primary Operational States
1.  **Rest/Standard**: Default animation loop and movement response.
2.  **Droid Thinking**: Initiated via RC input. Triggers a specialized LED pattern on Node 2 and specialized "Thinking" audio on Node 1.
3.  **High Alert**: (Formerly "Angry Mode"). Triggers "Alarm" audio and red-alert lighting sequences across all addressable arrays.
4.  **Audio Interaction**: Manual audio triggers (via DFPlayer Mini UART) that can initiate synchronized head-tilt or light-flicker behavior.

---

## 📻 Trigger Logic (Node 1 Hub)
Node 1 (Body Hub) is the primary audio executor. It converts wireless triggers into **UART** commands for the DFPlayer Mini.

- **Audio Bitrate**: 128kbps (Recommended for stability)
- **Amplification**: TPA3118 (60W)
- **Power Iso**: Managed via isolated buck converters to prevent motor noise from entering the analog audio signal path.
