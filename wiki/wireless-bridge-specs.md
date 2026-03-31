# Wee2-D2 Wireless Bridge (ESP-NOW)
> **TECHNICAL SPECIFICATIONS** | **v2.1.0-Zero-Infra Architecture**

The **Wireless Bridge** is the core communication layer of the Wee2-D2. It uses ESP-NOW (a proprietary 2.4GHz protocol) to transmit low-latency control and synchronization commands between the three distributed MCUs.

## 📡 Protocol Summary
- **Type**: Connectionless (Unicast/Broadcast)
- **Range**: ~50m (Internal Chassis Range optimized for stability)
- **Latency**: <10ms (Real-time motor/audio sync)
- **Framework**: `esp-idf` (Required on ESP32-S3 for stable RMT/Wireless threading)

## 🏗️ Node Roles & Binding
The bridge is established through hardcoded MAC addresses in the `base-config.yaml` to ensure zero interference from other 2.4GHz devices.

1.  **Broadcast Master (Node 3)**: Monitors RC inputs and movement. Broadcasts state changes to all other nodes.
2.  **Listener (Node 1)**: Listens for audio-trigger states and executes UART commands for the DFPlayer.
3.  **Listener (Node 2)**: Listens for visual-trigger states and executes WLED pattern changes.

---

## 🛡️ Reliability & Safety
- **Fallback**: If the bridge signal is lost for >100ms, the **Safety Heartbeat** (defined in `node-3-motion-master.yaml`) triggered on all receiving nodes enters a "Hold/Rest" state.
- **EMI Mitigation**: The bridge operates independently of the local Wi-Fi router, allowing total field-operation without a network connection.
