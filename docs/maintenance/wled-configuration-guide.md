# <i data-lucide="sun"></i> System Logic: WLED Configuration Guide

To synchronize your 4-pin dome layout, follow these precise configuration steps within the WLED Web Interface.

---

### 1. The Automation Override

Instead of manually configuring the 2D matrices and GPIO mapping, the v2.6.0 architecture uses a pre-compiled JSON deployment to guarantee perfect synchronization with the Web Dashboard.

1. In your repository, locate the `firmware/production/node-3-wled/` directory.
1. It contains three files: `cfg.json` (Hardware settings), `presets.json` (Animations), and `ledmap.json` (Matrix routing).

### 2. Restoring the Configuration

1. Connect to the **WLED Web Interface** via your browser (`http://dome-lights.local` or its static IP).
1. Navigate to **Config > Security & Updates**.
1. Scroll down to the **Backup & Restore** section.
1. Upload the `cfg.json` file and click **Restore**. The Node will reboot.
1. Navigate back to the same page. Upload the `presets.json` file.
1. Finally, go to **Config > LED Preferences**, scroll to the bottom, and upload `ledmap.json` to lock in the 2D matrix warping.

> [!TIP]
> **COMPLETED!** Your lighting node is now fully synchronized with the 15 standard Cinematic Logic states managed by the Neural Command Center. No further pin mapping is required.