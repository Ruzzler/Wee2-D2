# <i data-lucide="server"></i> Local Server Guide

> **TECHNICAL SPECIFICATIONS** | **SYSTEM: INFRASTRUCTURE** | **MODEL: LAN HUB**


The Wee2-D2 project is designed to operate primarily in a **Wiki-Only** environment without a central server. However, for development and convention management, a local laptop or mini-PC can be used to host a backup repository or a Home Assistant instance.


---


## System Connectivity

The droid operates on a local 2.4GHz Wi-Fi network. If you are using a local server, ensure it is on the same subnet as the microcontroller nodes.


- **Node 1 (Dome Master)**: `wee2d2-dome-master.local`
- **Node 2 (Sound Hub)**: `wee2d2-sound-hub.local`
- **Dashboard Port**: Standard HTTP Port 80


---


## Management & Updates

A local server can be used to manage OTA (Over-The-Air) updates more efficiently by caching the compiled `.bin` files. 


1. **Cache**: Keep a copy of the `v2.6.0-Dashboard` binary files on your local drive.
2. **Deploy**: Navigated to the node's individual server page and upload the verified file.


---


[View Status Schematic](../architecture/electrical-schematic.md) | [View Troubleshooting](troubleshooting.md)