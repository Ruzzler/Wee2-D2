# <i data-lucide="workflow"></i> Automations

This section serves as the technical roadmap for **Behavioral Automations**. While the droid currently operates on direct manual triggers (RC), the future architecture will utilize a modular automation layer to execute synchronized movement, lighting, and audio routines autonomously.

---

## Automation Roadmap

The following autonomous behaviors are currently in development as high-density technical placeholders:

### 1. Idle Scanning (Future)

- **Logic**: Autonomous dome rotation in a slow, pseudo-random "scanning" pattern.
- **Trigger**: Activates after **120 seconds** of RC inactivity.
- **Goal**: Simulates droid curiosity and environmental monitoring.

### 2. Event-Based Response (Future)

- **Logic**: Real-time reaction to external sensor data (e.g., ultrasonic distances or thermal sensing).
- **Goal**: Allows the droid to "back away" or "turn towards" people in its immediate vicinity.

### 3. Synchronized Show Sequences (In-Progress)

- **Logic**: Hard-coded routines that combine precision dome timing, specific WLED presets, and multi-track audio playback.
- **Current Triggers**:
 - **Droid Thinking**: Standard synchronized "Logic" display and audio.
 - **High Alert**: Synchronized red-alert sequence and alarm audio.

---

## Programming Strategy

Automations will be programmed as **ESPHome Scripts** on **Node 3 (Dome Motion Master)** and broadcasted to the mesh via the **ESP-NOW** bridge. This ensures that even complex autonomous routines remain perfectly synchronized across all three microcontroller hubs.

> [!NOTE]
> **DEVELOPMENT NOTICE**: This page is a functional stakeholder for future software updates. Refined automation logic will be graduated to this guide as it moves from bench-testing to production.