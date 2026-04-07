# <i data-lucide="sliders"></i> WLED Configuration Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: LIGHTING CONFIGURATION** | **MODEL: WLED v0.14+**


The cinematic lighting for the Wee2-D2 project is managed through the WLED framework on Node 3. This guide explains how to configure segments, presets, and sync triggers to align with the droid's behavioral logic.


---


## System Integration (UART Sync)

Node 3 (LED Distro) acts as a slave to **Node 1 (Dome Master)**. It receives serial JSON triggers to instantly apply visual presets synchronized with audio tracks.


1. **Primary Segment**: Front PSI Matrix (48 LEDs).
2. **Secondary Segment**: Rear PSI Matrix (48 LEDs).
3. **Logic Sync**: UART-synced to Node 1 at 115200 baud (firmware/production/node-1-dome-motion.yaml:137).


---


## Segment Mapping & JSON Configuration

The project uses a standard segment mapping to ensure WLED understands the physical layout of the GrnWave PSI arrays.


This configuration is verified in the `v2.6.0-Dashboard` production deployment.


- **Config File**: [node-3-segments.json](../../firmware/production/node-3-segments.json)
- **Presets**: [wled-presets.json](../../firmware/production/wled-presets.json)
- **Mapping**: Front PSI (Segment 0) | Rear PSI (Segment 1).
- **LED Order**: GRB (Standard WS2812B).


---


## Deployment Procedure (WLED Dashboard)

Follow these steps to apply a fresh configuration to your Lighting Node (Node 3).


1. **Open**: Navigate your web browser to `wled-dome.local` or the node's local IP address.
2. **Config**: Under the "Config" menu, select "Security & Updates".
3. **Upload**: Select the "Choose File" option for the configuration JSON (`wled-cfg.json`) and pick your verified folder.
4. **Reboot**: The node will receive the configuration and apply the new segment mapping automatically.


---


## Diagnostic Troubleshooting

If the lighting is not responding to Node 1 triggers, check the physical UART TX/RX connection between the dome Master and the LED Distro.


- **Grounding**: Ensure a shared ground between Node 1 and Node 3.
- **Data Noise**: Keep the 5V logic wires separate from the 20V motor trunks. 
- **Monitoring**: Use the WLED dashboard "Info" tab to check the current RX signal status.


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View LED System Guide](../capabilities/led-system.md)