# <i data-lucide="zap"></i> Flipsky FSESC 6.7 Pro
> **TECHNICAL SPECIFICATIONS**

The **Flipsky Mini FSESC 6.7 Pro** is a high-performance electronic speed controller based on the VESC 6.6 architecture. It is used in the Wee2-D2 to drive the high-torque hub motors.

![Flipsky FSESC 6.7 Pro](../../assets/flipsky-fsesc-67-pro.jpg)

##  Technical Specifications
*   **Current**: 70A Continuous, 200A Instantaneous Peak.
*   **Voltage Range**: 14V – 60V (Support for 4S to 13S LiPo; **Safe Limit: 12S**).
*   **Hardware Version**: VESC 6.6 base (6.7 Pro specific features).
*   **MOSFETs**: 6x NVMFS5C612NL (60V/235A).
*   **ERPM**: 150,000 max.
*   **BEC Output**: 5V @ 1A.
*   **Manual**: [Download Local PDF Manual](flipsky-fsesc-67-pro-manual.pdf)
*   **Control Modes**: DC, BLDC, **FOC (Field Oriented Control)** — *FOC is recommended for quiet droid drive.*

##  Pinout & Communication
*   **USB**: Type-C for configuration via VESC Tool.
*   **CAN**: For syncing dual ESCs (Master/Slave).
*   **UART**: For MCU 1 communication or Bluetooth modules.
*   **PPM**: Standard RC PWM input (1000-2000μs).
*   **Hall Sensors**: For sensored motor control (Startup from 0 RPM).

##  Calibration & Setup
1.  **VESC Tool**: Download and install the [VESC Tool](https://vesc-project.com/).
2.  **Motor Detection**: Run the "Motor Setup Wizard" to calibrate the Hub Motors.
3.  **Input Setup**: Use the "Input Wizard" to map your RC Receiver channels.
4.  **Limits**:
    *   **Current Limit Max**: 70A.
    *   **Voltage Cutoff**: Start at 16.5V for DeWalt batteries.

> [!IMPORTANT]
> **Silencing the Droid**: Use **FOC** mode for the drive motors. This eliminates the "electronic whine" common in BLDC mode and results in silent, high-torque movement.
