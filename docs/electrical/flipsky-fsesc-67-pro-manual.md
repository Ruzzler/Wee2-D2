# 🏛️ IMPERIAL DATABANK: FLIPSKY FSESC 6.7
> **DECRYPTED DATA REPOSITORY** | **SERIAL: MINI-FSESC-6.7-PRO**

The **Flipsky Mini FSESC 6.7 Pro** is a high-performance electronic speed controller based on the VESC 6.7 architecture. It is used in the Wee2-D2 to drive the high-torque hub motors.

## ⚡ Technical Specifications
*   **Voltage**: 14V – 60V (Support for 4S to 13S LiPo).
*   **Current**: 70A Continuous, 200A Instantaneous Peak.
*   **Hardware Version**: VESC 6.7.
*   **Size**: 67mm x 34mm x 21mm (Mini form factor).
*   **BEC Output**: 5V @ 1A.
*   **Control Modes**: DC, BLDC, **FOC (Field Oriented Control)** — *FOC is recommended for quiet droid drive.*

## 🔌 Pinout & Communication
*   **USB**: Type-C for configuration via VESC Tool.
*   **CAN**: For syncing dual ESCs (Master/Slave).
*   **UART**: For Node 1 communication or Bluetooth modules.
*   **PPM**: Standard RC PWM input (1000-2000μs).
*   **Hall Sensors**: For sensored motor control (Startup from 0 RPM).

## 🛠️ Calibration & Setup
1.  **VESC Tool**: Download and install the [VESC Tool](https://vesc-project.com/).
2.  **Motor Detection**: Run the "Motor Setup Wizard" to calibrate the Hub Motors.
3.  **Input Setup**: Use the "Input Wizard" to map your RC Receiver channels.
4.  **Limits**:
    *   **Current Limit Max**: 70A.
    *   **Voltage Cutoff**: Start at 16.5V for DeWalt batteries.

> [!IMPORTANT]
> **Silencing the Droid**: Use **FOC** mode for the drive motors. This eliminates the "electronic whine" common in BLDC mode and results in silent, high-torque movement.
