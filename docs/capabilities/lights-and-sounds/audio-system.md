# <i data-lucide="volume-2"></i> Audio & Voice Triggers

Wee2-D2's voice and sound system uses a distributed modular stack with the **DFPlayer Mini** (MP3 Hub) and a **TPA3118 60W Amplifier**. Triggers are handled wirelessly via the **ESP-NOW** bridge.


![TPA3118 Amplifier Module](../../../assets/tpa3118-amplifier-module.jpg)


---


## How it Works: The Wireless Trigger

Instead of physical wires running through the slip ring, the droid uses a **Wireless Behavioral Bridge**.

1. **Event Capture**: The **Sound Hub (Node 2)** captures an event via the Web Dashboard or autonomous script.
2. **Command Execution**: Node 2 executes the **Serial (UART)** command directly to the local **DFPlayer Mini**.
3. **Broadcast Sync**: Node 2 also broadcasts an **ESP-NOW** packet (e.g., `0xA0` Animation ID) to Node 1 for dome and lighting synchronization.
4. **Amplification**: The DFPlayer outputs a low-level analog signal to the **TPA3118 Amplifier**, which drives the 60W Pyle speaker at 20V.


---


## SD Card Formatting (DFPlayer Standard)

For the DFPlayer Mini to recognize tracks, the SD card must follow the standard naming layout. Ensure the card is formatted to **FAT32**.

The folders must be named `01` through `99`, and files must start with a 3-digit prefix.


```text
SD_ROOT/
 01/ # Folder 1: Happy Sounds
 001_beep_boop.mp3
 002_whistle.mp3
 02/ # Folder 2: Alert Sounds
 001_scream.mp3
 002_alarm.mp3
 03/ # Folder 3: Ambient
 001_low_hum.mp3
 002_processing.mp3
 04/ # Folder 4: High Alert (Red)
```


*Note: The DFPlayer supports up to 255 tracks per folder, allowing for massive behavioral variety.*


---


## Behavioral Animation Logic

By interacting with the **Neural Command Center Dashboard**, users can trigger saved sound banks. Node 2 broadcasts the Animation ID wirelessly, which syncs the lighting patterns and the sound selection:

| Animation ID | Lighting Sync (WLED) | Audio Character |
| :--- | :--- | :--- |
| **0xA0, 0x01** | Default / Idle | Happy / Inquisitive |
| **0xA0, 0x02** | 1977 Analog | Processing / Static |
| **0xA0, 0x03** | High Alert (Red) | Alarms / Screams |
| **0xA0, 0x04** | Cantina | Musical / Joyful |


---


## Ambient Mode

When set to **Ambient Mode (Bank 1)**, the Body Hub will automatically fire random tracks from Folder `03` every 15-45 seconds to simulate droid "thinking" during idle periods.


---


## Audio Stack Interconnect (UART)

Unlike the legacy 9-wire trigger system, the v1.8 stack uses a 4-wire serial bus for absolute control:

| Pin | Source (S3) | Destination (DFPlayer) | Role |
| :---: | :--- | :--- | :--- |
| **TX** | **GPIO 12** | RX Pin | Serial Data Output |
| **RX** | **GPIO 13** | TX Pin | Status Data Input |
| **VCC** | 5V Rail | VCC Pin | Power (5V/1A Peak) |
| **GND** | Star Ground | GND Pin | Logic Reference |


---


**Relevant Hardware & Code:**
- [DFPlayer Mini Data Sheet](../../manuals/dfplayer-mini-manual.pdf)
- [Node 2: Sound Hub](../../architecture/node-2-sound-hub.md)