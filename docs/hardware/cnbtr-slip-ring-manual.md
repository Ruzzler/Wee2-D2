# 🏛️ IMPERIAL DATABANK: CNBTR SLIP RING
> **DECRYPTED DATA REPOSITORY** | **SERIAL: CNBTR-6P-10A**

The **CNBTR Through-Hole Slip Ring** allows for 360° continuous rotation of the droid's dome while transferring power and data from the body.

![CNBTR Slip Ring](../../assets/slip-ring-cnbtr.jpg)

## ⚡ Technical Specifications
*   **Bore Diameter**: 12.7mm (1/2 inch) — *Fits over the central dome shaft.*
*   **Circuits**: 6 Circuits.
*   **Rated Current**: 10A per circuit (Total capacity: 60A).
*   **Rated Voltage**: 0 - 380V AC/DC.
*   **Max Speed**: 300 RPM.
*   **Contact Material**: Gold-to-Gold (Provides low noise for logic signals).

## 🔌 Wiring & Pinout
The slip ring uses color-coded wires. Standard CNBTR 6-circuit wiring:

| Circuit | Color | Primary Use in Wee2-D2 |
| :---: | :--- | :--- |
| **1** | **Red** | **20V Main Power (+)** |
| **2** | **Black** | **Main Ground (-)** |
| **3** | **Clear/Yellow** | **UART / Data** (Optional) |
| **4** | **Green** | **GND** (Logic Common) |
| **5** | **Blue** | **Analog/Sensor** (Optional) |
| **6** | **Orange** | **Spare** |

## 🛠️ Installation Notes
1.  **Alignment**: Ensure the slip ring is centered on the dome axis to prevent "wobble" and excessive wear on the internal brushes.
2.  **Strain Relief**: Use zip-ties to secure the wires on both the stator (body) and rotor (dome) sides to prevent the wires from rotating inside the housing.
3.  **Low Noise**: Since this uses gold-to-gold contacts, logic signals (like I2C or UART) can be passed through, but separate them from the 20V power lines by at least one circuit if possible to minimize interference.

> [!WARNING]
> Do not exceed 10A on a single wire. For high-current motors, use multiple wires in parallel or verify the peak load against the 10A rating.
