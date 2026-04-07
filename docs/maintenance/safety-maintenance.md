# <i data-lucide="shield"></i> Maintenance & Safety Manual: Wee2-D2

Safety and maintenance keep your droid running right. These protocols protect your hardware and anyone near the droid.


---


## High-Voltage Safety (20V DC)

The DeWalt battery is capable of high-current discharge. **Respect the power.**


### 1. Lithium Battery Hazards

- **Storage**: Never store the DeWalt battery below 16V or above 21V for long periods. Use the **DeWalt standard charger** for storage-mode charging if available.
- **LVC Mode**: The **MgcSTEM LVP-R1.5** Low-Voltage Cutoff is your main safety feature. Ensure it is set to **1.6V/Cell** (16V total) to prevent permanent battery damage.
- **Physical Shock**: If the droid suffers a major impact, inspect the battery for casing cracks immediately.


### 2. Fuse Protocol

- **Main Fuse**: Always use a **30A-40A** automotive fuse.
- **Replacement**: If the droid goes dead, **DO NOT** replace the fuse until you have checked for a 20V-to-GND short circuit on the main power rails.


---


## Periodic Maintenance

### 1. Slip Ring Servicing

The rotating joint is the most sensitive mechanical link.
- **Noise Check**: If your dome rotation begins to "twitch" or LEDs flicker, your slip ring contacts may have accumulated carbon dust.
- **Cleaning**: Use **DeoxIT D5** or a high-quality electrical contact cleaner. Spray a small amount through-hole and rotate the dome 20+ times to clear contacts.


### 2. Fastener Integrity

The vibration from the drive motors can loosen screws.
- **Checkpoints**: Periodically tighten the **motor mount bolts** and the **dome rotation gear** set screws.
- **Threadlock**: Use **Blue Loctite (242)** on any metal-to-metal fasteners exposed to high vibration.


### 3. ESC Cooling

The Flipsky 6.7 ESCs can generate significant heat during long drives.
- **Airflow**: Ensure the internal body vents are not blocked. Clean any dust from the ESC heatsinks every 2 months.


---


## Emergency Procedures

### 1. E-Stop Command

- **Manual Kill**: Physically remove the DeWalt battery from the droid's rear compartment.
- **Radio Kill**: Set your **Fail-Safe** on the HOTRC to "Neutral" so the droid stops if it loses signal.


### 2. Thermal Runaway

- If you smell "burning electronics" or see smoke, **DISCONNECT THE BATTERY IMMEDIATELY.** Do not attempt to diagnose with the power applied.