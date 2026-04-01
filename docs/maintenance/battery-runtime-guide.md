# <i data-lucide="battery"></i> Battery Runtime & Power Estimates
> **POWER MANAGEMENT** | **SYSTEM: DEWALT 20V (4Ah)**

This guide provides predicted operational durations for the Wee2-D2 based on the 4Ah 20V DeWalt battery system.

## <i data-lucide="zap"></i> Energy Capacity (4Ah / 74Wh)
The 20V DeWalt battery operates at **18.5V Nominal**. A 4Ah pack contains **74 Watt-Hours (Wh)** of raw energy. To protect the Lithium-ion cells, the [LVP-R1.5 Cutoff](../hardware/mgcstem-lvp-r15-manual.md) is set to 17.5V, leaving approximately **63Wh** of "Safe Usable" energy.

---

##  Power Consumption Breakdown
*Real-world estimates for a "Con Day" duty cycle.*

### **1. Baseline (Always-On Logic & Lights)**
- **Logic MCUs**: 3x ESP32-S3 + RC Receivers.
- **Lighting Pattern**: Front/Rear Logics + Circular PSIs @ 40% Brightness.
- **Conversion Loss**: Buck converter overhead (15%).
- **Estimated Load**: **11.0 Watts**

### **2. Audio (Intermittent Chatter)**
- **System**: DFPlayer Mini + TPA3118 Amp.
- **Duty Cycle**: 20% (Droid chirps every 30 seconds).
- **Estimated Load**: **2.0 Watts (Avg)**

### **3. Drive Motion (2x 200W Hub Motors)**
- **Conditions**: Level convention floor, slow walking pace.
- **Duty Cycle**: 40% (Moving 24 minutes per hour).
- **Throttling**: **15A Software Clamp** applied for endurance.
- **Estimated Load**: **16.0 Watts (Avg)**

### **4. Motion Controller (goBILDA 5203)**
- **Condition**: Continuous random dome rotation.
- **Duty Cycle**: 15%.
- **Estimated Load**: **1.5 Watts (Avg)**

---

##  Operational Estimates (4Ah Battery)

| Usage Mode | Total Average Load | Estimated Runtime |
| :--- | :---: | :--- |
| **Active Patrol** (Moving/Beeping) | **30.5 Watts** | **~2.0 Hours** |
| **Booth Guard** (Static/Beeping) | **14.5 Watts** | **~4.3 Hours** |
| **Stealth Mode** (Logic only/Dark) | **4.0 Watts** | **~15.5 Hours** |

> [!TIP]
> **ENDURANCE UPGRADE**: For a full 6-hour convention day with minimal battery swaps, it is recommended to transition to a **6Ah or 9Ah** DeWalt FlexVolt pack, which provides **133Wh to 200Wh** of capacity.

##  Battery Safety Note
The **MgcSTEM LVP-R1.5** will automatically cut power at **17.5V**. If your droid suddenly goes dark, please replace the battery immediately. **Do not** attempt to bypass the LVC, as discharging below 16V will cause permanent cell damage to your power tool batteries.
