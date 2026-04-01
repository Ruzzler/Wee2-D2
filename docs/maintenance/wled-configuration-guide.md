# <i data-lucide="sun"></i> System Logic: WLED Configuration Guide

To synchronize your 4-pin dome layout, follow these precise configuration steps within the WLED Web Interface.

---

### 1. LED Preferences
**Navigate to: Config LED Preferences**

| Hardware Line | LED Type | GPIO | Length | wire Color |
| :--- | :--- | :---: | :---: | :--- |
| **Output 1: Front Logic** | WS2812B | **18** | 20 | Yellow |
| **Output 2: Rear Logic** | WS2812B | **19** | 24 | / Yellow/Blk |
| **Output 3: Front PSI** | WS2812B | **21** | 76 | Green |
| **Output 4: Back PSI** | WS2812B | **22** | 76 | White |

> [!IMPORTANT]
> **POWER LIMITER**: Ensure the **"Maximum Current"** is set to **3500mA**. This protects your Mini560 Buck Converter from blowing during high-intensity white flash effects.

---

### 2. 2D Matrix Calibration
**Navigate to: Config 2D Configuration**
*This ensures your logic scrolls correctly rather than just blinking in a straight line.*

- **Matrix 1 (Front)**: 
 - Width: **10** | Height: **2**
 - Layout: **Serpentine** (If your strip zig-zags)
- **Matrix 2 (Rear)**: 
 - Width: **12** | Height: **2**
 - Layout: **Serpentine**

---

### 3. Segment Mapping (Visual Layout)
**Navigate to: Main Dashboard Segments**
Divide your pixels into these blocks to allow different effects on different windows:

| Segment ID | Start | Stop | Component | Recommended Effect |
| :---: | :---: | :---: | :--- | :--- |
| **0** | 0 | 20 | Front Logic | **2-D Matrix (Scanning)** |
| **1** | 20 | 44 | Rear Logic | **2-D Matrix (Scanning)** |
| **2** | 44 | 120 | Front PSI | **Breathing** (Blue/Green) |
| **3** | 120 | 196 | Back PSI | **Flicker** (Amber/Red) |

---

> [!TIP]
> **OTA UPDATE**: Once your WLED board is on the network, you can push these settings wirelessly. Use the [Local Server Guide](docs/maintenance/local-server-guide.md) to keep your Documentation and WLED synced!
