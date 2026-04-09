# <i data-lucide="settings"></i> HOTRC DS-600

> **TECHNICAL SPECIFICATIONS** | **6-CHANNEL TX** | **2.4GHz TRIGGER STYLE**

The **HOTRC DS-600** is a 6-channel, one-handed "trigger style" 2.4GHz transmitter. In the Wee2-D2 project, it provides the primary interface for drive and dome movement.

> [!NOTE]
> **Owner Mod (Silent Mode)**: The internal speakers have been physically removed from these units to eliminate beeping. Always rely on the **Status LEDs** on the front panel for pairing and mixing mode confirmation.

- **Channels**: 6 Channels
- **Frequency**: 2.4GHz ISM (2.4005 – 2.4835 GHz)
- **Spread Spectrum**: FHSS
- **Response Speed**: PWM ≤ 20ms
- **Control Range**: 300 – 500m (Water/Ground)
- **Transmitter Power**: Built-in 3.7V / 1200mAh Lithium Battery (USB 5V Charging)
- **Manual**: [Download Local PDF Manual](hotrc-ds600-manual.pdf)

## Control Layout

- **Trigger (CH2)**: Forward / Backward.
- **Thumb Joystick (CH1)**: Left / Right Steering.
- **CH3 Switch**: Auxiliary (Toggle).
- **CH4 Switch**: Auxiliary (Toggle).
- **CH5/CH6**: Side buttons/knobs.

## Essential Configuration

### 1. Mixing Mode (Tank Steering)

The DS-600 can internally "mix" CH1 and CH2 for dual-motor control.
- **To Toggle Mixing**:
 1. Turn the remote **OFF**.
 1. Press and hold the **[CH3]** button.
 1. Turn the remote **ON**.
 1. **Status**: Green light = Mixing ON. No light = Mixing OFF.
- **Recommendation for Wee2-D2**: Keep Mixing **OFF**. The Flipsky ESCs natively handle software mixing through their internal VESC Tool configuration, making external transmitter mixing unnecessary.

### 2. Channel Reversal

If your droid drives backward when you pull the trigger:
1. Turn the remote **OFF**.
1. Press and hold the **[CH4]** button.
1. Turn the remote **ON**.
1. Move the trigger (CH2) or joystick (CH1) to its limit. A long beep confirms the reversal.


## Wiring Topography

Wee2-D2 uses two separate DS-600 transmitters and identical F-06A receivers to isolate drive operations from dome movement.

### 1. Drive Receiver (Body)
The Body F-06A receiver bypasses microcontrollers entirely.
- **CH1 (Left/Right)**: Connects directly to the Left and Right Flipsky ESC PWM inputs.
- **CH2 (Throttle)**: Connects directly to the Left and Right Flipsky ESC PWM inputs via a Y-Splitter.

### 2. Dome Receiver (Head)
The Dome F-06A receiver is strictly for manual dome control, communicating through the **Node 1 (Dome Master)** hub.
- **CH1 (Left/Right)**: Connects to **Node 1 (GPIO 4)** for deadband clamping and autonomous routine overrides.
- **CH2-CH6**: Unused.

> [!IMPORTANT]
> **Failsafe Setup**:
> 1. Turn on both remote and droid.
> 2. Set the remote trigger to neutral (stopped).
> 3. Insert the bind plug into the **"B" port** on the receiver for 3 seconds.
> 4. Now, if the remote loses power, the receiver will output "neutral," stopping the droid immediately.