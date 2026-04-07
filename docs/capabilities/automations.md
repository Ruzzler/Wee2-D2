# <i data-lucide="activity"></i> Autonomous Automations

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: BEHAVIORAL LOGIC** | **MODEL: AUTONOMOUS SEQUENCES**


The Wee2-D2 project uses a combination of random and triggered automations to create a living droid experience. These behaviors are managed by Node 1 (Dome Master) and are synchronized with the sound and lighting hubs.


---


## System Logic (Autonomous Master)

The Wee2-D2 droid uses a **Modular Behavioral System** based on **ESPHome States** and **Wireless Triggers**. All autonomy is processed by **Node 1 (Dome Master)**, which monitors its idle state and triggers synchronized movement/AV events to maintain character realism.


- **Update Frequency**: **50ms** (Internal Heartbeat) for real-time behavioral response.
- **Interval**: A random trigger is calculated every **30 to 60 seconds** (firmware/production/node-1-dome-motion.yaml:454).
- **Inhibition**: Automations are immediately paused if a manual RC stick command is detected.
- **Mesh Status**: Triggers are only sent if the **MAC-Address Binding** to the Sound Hub is verified.


---


## Behavioral Animation Library

The project includes a library of verified animation sequences that coordinate dome speed, audio tracks, and **Cinematic Logic Display** presets.


| Trigger | Movement Result | Sound CMD | Cinematic Logic |
| :--- | :--- | :---: | :---: |
| **Idle Chirp** | Slow 15-degree scan | 0x01 | Preset 1 |
| **Random Beep** | Rapid 5-degree snap | 0x01 (Random) | Preset 1 |
| **Angry Tantrum**| Rapid jitter (8Hz) | 0x02 | Preset 3 |
| **Dance Groove** | Synchronized 360 spin | 0x03 | Preset 10 |
| **Cantina Band** | Continuous scan pattern | 0x04 | Preset 14 |


---


## Safety Overrides & E-Stop

To ensure pilot safety and hardware longevity, the automations system includes a hardware-level override protocol.


1. **Manual Takeover**: If the HotRC stick moves >5% from center, the autonomous script is killed instantly.
2. **Battery Sag**: If the 20V trunk drops below **17.5V**, all heavy animations (Tantrum/Dance) are disabled to save power for the logic rails. (firmware/production/node-1-dome-motion.yaml:425).
3. **Connectivity Fail**: If the mesh bridge between Node 1 and Node 2 is lost, the droid enters a "Safe Stationary" mode.


---


## Maintenance & Tuning

Automations can be tuned and adjusted using the interactive dashboard hosted by Node 2 (`wee2d2-sound-hub.local`).


- **Trigger Rate**: Adjust the `random_seed` interval to make the droid more or less active.
- **Speed Cap**: Set the maximum dome speed for autonomous scans at 40% for convention floors. 
- **Sound Volume**: Cap the automation audio volume at 60% relative to manual triggers.


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Troubleshooting](../maintenance/troubleshooting.md)
