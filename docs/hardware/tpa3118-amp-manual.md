# <i data-lucide="volume-2"></i> TPA3118 60W Mono Amplifier

> **TECHNICAL SPECIFICATIONS**

The **TPA3118** is a high-efficiency Class-D mono audio amplifier module that serves as the primary sound projection hardware for the Wee2-D2. It receives a low-level analog signal from the **DFPlayer Mini** (Node 1) and drives the internal 3.5" speaker.

![TPA3118 Amplifier Module](../../assets/tpa3118-amplifier-module.jpg)

## Module Overview

The TPA3118 is favored for its compact footprint and low heat generation, making it ideal for the enclosed electronics bay of a droid. It operates on a wide voltage range, allowing it to run directly off the 20V battery rail for maximum output headroom.

| Feature | Specification |
| :--- | :--- |
| **Amplifier Class** | Class D (High Efficiency) |
| **Output Power** | 60W Mono |
| **Operating Voltage** | 4.5V – 26V DC (**20V Optimized**) |
| **Signal-to-Noise Ratio** | 102 dB |
| **Output Impedance** | 4 - 8 Ohms |
| **Protection** | Short-circuit, Over-temperature, Over-voltage |

## Pinout Reference

| Pin Layout | Designation | Function |
| :---: | :--- | :--- |
| **PVCC** | Power Input | 20V Positive from Fuse Box |
| **GND** | Ground | Negative Bus Bar (Star Ground) |
| **IN+** | Audio Input (+) | Analog Signal from DFPlayer (SPK_1) |
| **IN-** | Audio Input (-) | Analog Signal from DFPlayer (SPK_2) |
| **OUT+** | Speaker Output (+) | Positive Terminal to Pyle 3.5" Speaker |
| **OUT-** | Speaker Output (-) | Negative Terminal to Pyle 3.5" Speaker |
| **SDZ** | Shutdown | Pull LOW to disable (unconnected = ON) |
| **MUTE** | Mute | Pull LOW to mute (unconnected = UNMUTED) |

## Wiring Integration

The audio signal is bridged from Node 1's DFPlayer to the TPA3118 using shielded twisted-pair wiring to minimize EMI from the drive motors.

```mermaid
graph LR
    subgraph "Node 1: Sound Hub"
        DF[DFPlayer Mini]
    end

    subgraph "Power Grid"
        FUSE[Fuse Box 20V]
        GND[Negative Bus Bar]
    end

    subgraph "Audio Stack"
        AMP["TPA3118 Amplifier"]
        SPK["3.5\" Pyle Speaker"]
    end

    DF -- "SPK_1 / Analog" --> AMP
    DF -- "SPK_2 / Analog" --> AMP
    FUSE -- "20V +" --> AMP
    GND -- "GND -" --> AMP
    AMP -- "60W Output" --> SPK
```

## Best Practices

- **Heat Dissipation**: While the Class-D architecture is efficient, ensure the module's onboard heat sink has adequate airflow within the body chassis.
- **Supply Decoupling**: Wee2-D2 uses a dedicated 470uF capacitor at the power input of the TPA3118 to stabilize the voltage during high-volume transients.
- **Volume Logic**: To prevent clipping and thermal throttling, the Sound Hub firmware limits the software volume to **26/30**.

---

**Related Documentation:**
- [DFPlayer Mini Spec](./dfplayer-mini-spec.md)
- [Node 1: Sound Hub Spec](../architecture/node-1-sound-hub-spec.md)
- [Power Architecture](../architecture/power-architecture.md)
