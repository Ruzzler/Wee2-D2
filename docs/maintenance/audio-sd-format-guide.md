# 🔊 Audio SD Card Formatting Guide
> **OPERATION & MAINTENANCE** | **SERIAL: SD-FMT-v1.0**

The PEMENOL 60W Soundboard relies on a very specific folder and file naming structure to work correctly with the Body Controller's ESPHome bank-switching logic. 

If your SD card is formatted incorrectly, triggers **S1 - S9** will not play the expected sounds.

## 💾 SD Card Constraints
*   **Format**: FAT32
*   **Capacity Limit**: 32GB Max (An 8GB or 16GB micro-SD is highly recommended).
*   **File Format**: Standard `.mp3` or `.wav` format.

## 🗂️ Directory Structure
The soundboard's "1-on-1" trigger mode (with the DIP switches set to `000` or `100`) maps physical trigger pins (S1-S9) directly to folders named `01` through `09`.

Since our ESPHome logic uses "Bank Switching" to drastically increase the number of available sounds, you must place multiple MP3 files inside each of these numbered folders. When a trigger is hit twice, the soundboard will automatically shuffle to the next MP3 in that folder.

Your SD card root directory must look exactly like this:

```text
SD_ROOT/
├── 01/                     # Triggered by S1
│   ├── 001_happy.mp3
│   ├── 002_excited.mp3
│   └── 003_chirp.mp3
├── 02/                     # Triggered by S2
│   ├── 001_sad.mp3
│   └── 002_whimper.mp3
├── 03/                     # Triggered by S3 (etc.)
├── 04/
├── 05/
├── 06/
├── 07/
├── 08/
└── 09/                     # Triggered by S9
```

> [!WARNING]
> **FOLDER NAMING IS CRITICAL**: The folders **must** be named exactly `01`, `02`, `03`... up to `09`. If you name a folder `1` instead of `01`, the board will silently fail to read it.

## 🔄 How the Body Controller Plays Sounds
The Body Controller's ESPHome code uses a 4-position "Bank" system. Here is how the radio clicks route to the SD card folders:

| ESPHome Bank | Trigger Mode | Mapped Audio Folder |
| :--- | :--- | :--- |
| **Bank 1 (Default)** | CH3 Up / Down | Folder `01` / `02` |
| **Bank 1 (Default)** | CH4 Up / Down | Folder `03` / `04` |
| **Bank 2 (Alt 1)** | CH3 Up / Down | Folder `05` / `06` |
| **Bank 2 (Alt 1)** | CH4 Up / Down | Folder `07` / `08` |
| **Bank 3 (Alt 2)** | CH3 Up only | Folder `09` (Angry/Red) |

## 🤖 Bank 4 (Auto-Mode)
When you switch into **Bank 4**, the Body Controller enters "Auto Mode." Every 5 to 15 seconds, the ESP32 will randomly select a trigger from S1 to S9. 
This means you should ensure every folder (`01` through `09`) has at least one sound in it, otherwise Auto-Mode might randomly trigger a silent folder.
