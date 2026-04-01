# 🔌 MgcSTEM LVP-R1.5

The **MgcSTEM LVP-R1.5** (Purple PCB) is a high-current 40A relay controller. It features a large T90-series relay and a 3-button interface (**SET**, **UP**, **DOWN**).

> [!NOTE]
> A full PDF version of the manufacturer's manual is available here: [MgcSTEM Manual](./mgcstem-lvc-manual.pdf)

## 🕹️ Mode Selection

To switch between Charging and Discharging modes:
*   **Press and hold [UP] for 5 seconds**.
*   The screen will display **`IN`** (Charging) or **`OUT`** (Discharging).
*   **For Wee2-D2**: Ensure the mode is set to **`OUT`**.

## 🛠️ Programming Parameters

1.  **Enter Settings**: Long-press **[SET]** for 3 seconds.
2.  **Navigate**: Short-press **[SET]** to cycle through parameters.
3.  **Adjust**: Use **[UP]** and **[DOWN]** to change values.
4.  **Save & Exit**: Long-press **[SET]** for 3 seconds.

### Recommended Settings (Discharge Mode)

| Parameter | Name | Description | Recommended |
| :--- | :--- | :--- | :--- |
| **`dn`** | Lower Limit | **Relay Opens** (Power Off) at this voltage | **17.5V (Extreme Safety)** <br> **17.0V (Standard Safe)** |
| **`UP`** | Upper Limit | **Relay Closes** (Power On) at this voltage | **20.0V** |
| **`OP`** | Timer | Auto-disconnect after X time (00:00 = Off) | **00:00** |
| **`dOP`** | Delay | Re-connect delay after reaching `UP` voltage | **10 seconds** |
| **`FOP`** | Forced Start | Ignores `dn` for X seconds during startup | **3 - 5 seconds** |

> [!TIP]
> **`FOP` (Forced Start)** is extremely useful for droids. Setting it to 3-5s prevents the board from tripping if the drive motors cause a brief voltage dip when they first start moving.

## 📟 Calibration (CRL)

If the voltage reading is inaccurate:
1.  Long-press **[SET]** (3s) to enter settings.
2.  While in the setting menu, **Long-press [UP] for 3 seconds**.
3.  The voltage reading will flash; adjust to match your multimeter.
4.  Short-press **[SET]** to confirm, then long-press **[SET]** (3s) to exit.

## 🚥 Status Indicator
*   **Yellow/Blue LED ON**: Relay is **CLOSED** (Power is flowing to the Droid).
*   **Yellow/Blue LED OFF**: Relay is **OPEN** (Cutoff active).
