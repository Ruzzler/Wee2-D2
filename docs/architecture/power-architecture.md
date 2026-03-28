# Wee2-D2 Power Architecture

This document tracks the electrical routing and protection systems for the Wee2-D2 droid.

## 🔋 Master Source
The droid is powered by **DeWalt 20V Batteries**.

## 🛡️ Protection Layer
1.  **MgcSTEM LVP-R1.5 (40A Cutoff)**: Protects DeWalt batteries from over-discharge (17.0V recommended cutoff).
2.  **6-Way Fuse Bus Bar**: Distributes fused 20V power to all subsystems.

## 🗺️ Power Routing
Raw 20V is sent up through a **CNBTR 12.7mm Through-Hole Slip Ring** (6 Circuits, 10A/Circuit) to the rotating dome.

### **Node 1 & Body (Lower)**
- **Drive**: 20V ➔ 2x [Flipsky Mini FSESC 6.7 Pro](../hardware/flipsky-fsesc-67-pro-manual.md) ➔ Hub Motors.
- **Audio**: 20V ➔ [DY-HL50T Sound Module](../hardware/pemenol-60w-voice-manual.md) (60W Mono).
- **Body Logic**: 20V ➔ 5V Buck Converter ➔ Node 1 (ESP32).

### **Dome Systems (Upper)**
- **Dome Motion**:
  - 20V ➔ goBILDA 1x15A Motor Controller ➔ goBILDA 5203 Yellow Jacket Motor.
  - **BEC Output (6V)**: Powers Receiver #2 and Node 3 (ESP32).
- **Dome Lights**:
  - 20V ➔ **Mini560 5V Buck Regulator** ➔ Node 2 (ESP32) and all LED Logic.
  - **5V Logic**: Front Logic (12x2), Rear Logic (10x2), and [GrnWave PSIs](../hardware/grnwave-psi-manual.md).

> [!CAUTION]
> **5V REGULATION**: All dome lighting components (Logic, PSIs, Strips) share a common 5V rail. **Never** connect the 6V BEC from the motor controller to the 5V lighting rail as it will immediately destroy the micro-LEDs.

## ⚠️ Safety Logic & Clamping
- **Dome Motion**: Software clamp in Node 3 restricts the 20V source to 60% power to simulate a safe **12V** output for the motor.
- **Dome Lights**: Brightness limiter enabled at **3500mA** to protect the Mini560 buck converter.
