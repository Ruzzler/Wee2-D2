# 🏛️ IMPERIAL DATABANK: L-FASTER HUB MOTOR (FLD-5)
> **DECRYPTED DATA REPOSITORY** | **SERIAL: LF-FLD5-200W**

This entry covers the dual high-torque brushless drive motors that power the Wee2-D2. The **FLD-5** is a gearless, brushless hub motor designed for electric scooters, repurposed here for precision droid locomotion.

## ⚙️ Core Specifications (FLD-5)
The **FLD-5** provides silent, high-efficiency direct-drive power with integrated Hall Sensors for smooth low-end torque.

### 📊 Technical Blueprint
| Specification | Data / Value |
| :--- | :--- |
| **Model** | FLD-5 (Gearless / Brushless DC) |
| **Rated Voltage** | 24V / 36V DC |
| **Rated Power** | 200 Watts |
| **No-Load Speed** | 900 RPM |
| **No-Load Current** | 1.3A |
| **Rated Efficiency** | ≥84% |
| **Max Loading Capacity**| 70 KG (per unit) |
| **Weight** | 1.9 KG |
| **Wheel Diameter** | 5 inch (Solid Rubber) |

---

## 🔌 Wiring & Interface (8-Wire)
Each motor utilizes **8 wires** total (3 Phase + 5 Hall) for high-fidelity commutation control.

| Signal Type | Color Code | Description |
| :--- | :---: | :--- |
| **Phase A** | **Yellow** | High-Current Motor Phase |
| **Phase B** | **Green** | High-Current Motor Phase |
| **Phase C** | **Blue** | High-Current Motor Phase |
| **Hall +5V** | **Red** | Sensor Power (3.3V - 5V) |
| **Hall GND** | **Black** | Sensor Ground |
| **Hall A** | **Yellow (Thin)** | Sensor Feedback |
| **Hall B** | **Green (Thin)** | Sensor Feedback |
| **Hall C** | **Blue (Thin)** | Sensor Feedback |

> [!IMPORTANT]
> When connecting to the **Flipsky FSESC 6.7 Pro**, ensure the Hall sensor harness matches the VESC pinout. Incorrect wiring of Phase vs Hall sensors can result in "Cogging" or high-current faults during startup.

---

## 🧠 Recommended VESC Configuration
To ensure the **Unified Nervous System** remains stable and responsive, the following VESC-tool parameters are recommended for the FLD-5 motors:

### **1. Commutation Profile**
*   **Motor Type**: **FOC (Field Oriented Control)**.
*   **Sensor Mode**: **Hall Sensors**. Use the VESC-tool detection wizard to auto-calibrate.
*   **Pole Pairs**: **15** (Standard for 5-inch Hub Motors).

### **2. Current & Voltage Safety**
| Parameter | Value | Rationale |
| :--- | :---: | :--- |
| **Motor Max** | 25.0 A | Allows for high-torque bursts during starts. |
| **Motor Max Brake** | -18.0 A | Strong regenerative braking. |
| **Battery Max** | 12.0 A | Synchronized with 200W @ 24V (x2). |
| **Battery Max Regen**| -8.0 A | Safe charge back into the DeWalt battery. |
| **Voltage Cutoff Start** | 21.0 V | Safe floor for 24V/20V operation. |
| **Voltage Cutoff End**| 20.0 V | Critical system shutdown to protect battery cells. |

### **3. Drive Smoothness**
*   **Startup Boost**: 0.01 (Minimum for FOC to avoid jerky starts).
*   **Current Ramping**: Standard (Ensure "Traction Control" is enabled for dual-drive stability).

---

## 🏢 Mechanical Maintenance
*   **Tire Care**: The 5-inch solid rubber tires are maintenance-free, but check for cracks or severe wear after operations in rough terrain.
*   **Mounting**: The hub motor axle usually features a flattened profile (D-shaft style) for anti-rotation in the droid bracket. Ensure high-grade M12/M14 locknuts are used.

