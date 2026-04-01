#  HOTRC F-06A Receiver
> **TECHNICAL SPECIFICATIONS**

The **HOTRC F-06A** is the native 6-channel 2.4GHz receiver paired with the DS-600 transmitter. In the Wee2-D2 project, these receivers capture wireless PWM signals and pass them to the ESP32 microcontrollers for drive and sound processing.

---

##  Technical Specifications
*   **Channels**: 6 Channels (PWM Output)
*   **Frequency Range**: 2.4GHz ISM
*   **Response Speed**: ≤ 20ms
*   **Input Power**: 4V - 9V DC (Supplied by the 5V Buck Converter via the ESP32 rail)
*   **Weight**: 5g
*   **Antenna**: Single 2.4GHz wire antenna
*   **Manual**: [Download Original PDF Manual](hotrc-f06a-manual.pdf)

> [!WARNING]
> **POWER LIMIT**: Do NOT power the F-06A receiver directly from the 20V battery. It must be powered from the regulated 5V logic rail. Supplying more than 9V will instantly destroy the receiver.

##  Binding Process (Pairing)
If your receiver loses connection to the DS-600 transmitter, or if you are setting up the secondary receiver for the dome:

1.  Make sure the DS-600 transmitter is turned **OFF**.
2.  Power on the F-06A receiver (supply 5V to any VCC/GND pin pair). The small LED on the receiver will flash rapidly, indicating it is in bind mode.
3.  Turn **ON** the DS-600 transmitter. 
4.  The receiver's LED will stop flashing and turn solid red, indicating a successful bind.

##  Failsafe Configuration
The failsafe ensures the droid stops moving if the transmitter is turned off or loses signal, preventing a runaway scenario.

1.  Turn on both the transmitter and the receiver. Ensure the LED is solid.
2.  Set the transmitter trigger and joystick to the completely neutral (center) positions.
3.  Insert a standard bind plug (or bridge the signal to ground) on the **"B" (Bind)** port of the receiver for 3 seconds.
4.  The receiver will save these neutral PWM values. If the signal drops, it will automatically output these saved values to the ESP32 and stop the droid.

##  Pinout Overview
The F-06A outputs standard 50Hz PWM signals that are natively readable by the ESP32 `pulse_width` sensor in ESPHome.

| Port | ESP32 Connection (Typical) | Signal Type |
| :--- | :--- | :--- |
| **CH1-CH6** | Any GPIO configured as Input | 1000us - 2000us PWM |
| **VCC (+)** | 5V Rail | Power (In) |
| **GND (-)** | Common Ground | Ground |
| **B (Bind)**| N/A | Failsafe bridge setting only |
