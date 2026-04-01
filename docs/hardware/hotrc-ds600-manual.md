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
- **Recommendation for Wee2-D2**: Keep Mixing **OFF**. The ESP32 (Node 1) performs more precise software-based mixing and safety clamping.

### 2. Channel Reversal

If your droid drives backward when you pull the trigger:
1. Turn the remote **OFF**.
1. Press and hold the **[CH4]** button.
1. Turn the remote **ON** (you will hear a beep).
1. Move the trigger (CH2) or joystick (CH1) to its limit. A long beep confirms the reversal.

## Wiring to ESP32 (Node 1)

The **F-06A Receiver** should be connected to the Node 1 ESP32 using standard 3-pin servo cables.

| Receiver Port | Node 1 Pin | Wire Color | Function |
| :--- | :--- | :--- | :--- |
| **CH3** (Data Pin 3) | **GPIO 25** | Grey/Black | Audio Bank/Trigger A |
| **CH4** (Data Pin 4) | **GPIO 33** | Blue/Black | Audio Bank/Trigger B |
| **CH5** (Data Pin 5) | **GPIO 32** | Purple/Black | Audio Bank Cycle Switch |
| **Slot 5 (+)** | **5V / VIN** | Red | Power Bridge (5V Rail) |
| **Slot 5 (-)** | **GND** | Black | Common Ground |

> [!IMPORTANT]
> **Failsafe Setup**:
> 1. Turn on both remote and droid.
> 2. Set the remote trigger to neutral (stopped).
> 3. Insert the bind plug into the **"B" port** on the receiver for 3 seconds.
> 4. Now, if the remote loses power, the receiver will output "neutral," stopping the droid immediately.