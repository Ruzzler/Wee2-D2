That is a great call. Relying on cloud connectivity can turn a living astromech into a static prop the second a router goes down. Keeping Wee2-D2 entirely localized and self-sufficient is the best way to ensure the droid feels genuinely alive.

To expand your research roadmap, I’ve looked into the hardware techniques used by both the R2 Builders Club and the engineering behind classic offline interactive toys (like the 2002 Hasbro Interactive Astromech). I've added a dedicated subsection to **Section 5** focusing on advanced, entirely offline sensor automations.

Here is the updated v2.8.2 roadmap:

-----

# \<i data-lucide="book-open"\>\</i\> Behavioral Research Roadmap (v2.8.2)

> **TECHNICAL SPECIFICATIONS** | **BABY ASTROMECH ADAPTATION** | **COMMUNITY STANDARDS**

This document serves as the primary research and engineering roadmap for the long-term personality development of the **Wee2-D2** droid. It synthesizes "Full-Size" industry standards from the R2 Builders Club with the specific constraints of our **Distributed Node Mesh** architecture, ensuring 100% offline, router-independent functionality.

-----

## 1\. The MarcDuino Cinematic Archive

The MarcDuino system remains the "Industrial Standard" for cinematic astromech behavior. We adopt the complete **:SE00 through :SE15** sequence set as our functional baseline.

| Sequence | Category | Technical Logic (N1 -\> N2 -\> N3) | Movie Reference |
| :--- | :--- | :--- | :--- |
| **:SE00** | **Stop/Reset** | Center Dome -\> Stop Audio -\> Default Blue/White Logic | System Default |
| **:SE01** | **Scream** | Open Panels -\> High-Pitch Scream -\> Red Logic Pulse | ESB: Hoth Attack |
| **:SE02** | **Wave** | Panel oscillation -\> Whistle -\> Teal Logic Scan | ANH: Sandcrawler |
| **:SE03** | **Smirk** | Back-and-forth dome sway -\> Double-whistle -\> Teal Pulse | ANH: Restraining Bolt |
| **:SE04** | **Fidget** | Quick minor twitches -\> Annoyed bleeps -\> Fast erratic logic | ESB: Dagobah |
| **:SE05** | **Cantina** | Rhythmic march -\> Music Playback -\> "Marching Ants" LEDs | ANH: Cantina Scene |
| **:SE06** | **Faint** | Immediate Brake -\> Groan SFX -\> Random Logic Flicker | ANH: Jawas Capture |
| **:SE07** | **Sad/Ooh** | Slow droop -\> Low mournful tone -\> Slow dimming logic | RotJ: Ewok Trap |
| **:SE08**| **Leia** | Stationary Dome -\> "Message" Audio -\> Dim Blue Holo-Pattern | ANH: Help me Obi-Wan |
| **:SE09** | **Disco** | Continuous Dome Scan -\> Orchestral Bleeps -\> **Rainbow Logic** | Community Flavor |
| **:SE10** | **Razz/Fart** | Quick shake -\> Raspberry sound -\> Single Red flash | Community Flavor |
| **:SE11** | **Angry** | Fast aggressive shaking -\> Loud rapid bleeps -\> Red/Yellow Logic | ESB: Swamp Monster |
| **:SE12** | **System Failure** | Micro-jitter -\> Sparking SFX -\> All lights flash then power down | ESB: Spit out of Swamp |
| **:SE13** | **Excited** | Fast left/right sweeps -\> High-tempo chirps -\> Rapid Rainbow Logic | TPM: Space Battle |
| **:SE14** | **Scan** | Slow sweeping motion -\> Radar pings -\> Sequential Logic Wipe | ESB: Hoth Ice Plains |
| **:SE15** | **Stealth** | Same Logic as SE01 but with **NO Audio** (Motion/Light only) | Night Ops |

-----

## 2\. "Baby Astromech" Adaptation Protocol

The Wee2-D2 is a high-fidelity "Baby Astromech" (3D files by Michael Baddeley). We must adapt full-size logic to our specific hardware constraints, utilizing peer-to-peer protocols that do not require a local network.

### Adaptation Logic Matrix

| Hardware | Constraint | Adaptation Profile |
| :--- | :--- | :--- |
| **Dome Motor** | **160° Limit** | Full-size 360° sweeps must be scaled to ±80° from center using **Cubic Ease-In-Out** algorithms to simulate physical dome mass/inertia. |
| **LED Matrices** | **WLED Segments** | Standard 24x2 patterns are re-mapped to our 4-Segment system (0:PSI Front, 1:PSI Rear, 2:Logic Front, 3:Logic Rear). |
| **Communication** | **Offline Mesh** | Single serial commands are fragmented into ESP-NOW payloads (Motion) and UART pulses (Lights/Audio). ESP-NOW operates via direct MAC-to-MAC radio, ensuring functionality anywhere without a Wi-Fi router. |

### Priority Sequence: The "Nervous Shake"

To simulate distress on a 160-degree dome without stripping gears, we implement a variable **Micro-Jitter Protocol**.

  - **Logic**: Node 1 oscillates the servo with randomized variance (between 12Hz-20Hz, and ±2° to ±5°) for 800ms to mimic organic mechanical panic.
  - **Sync**: Sound Hub plays Folder 14/File 02 (Angry/Panic).

-----

## 3\. Audio Procurement & Sync Logic

Personality is defined by the **Emotional Sound Bank**. We synchronize with the community's **9-Bank Standard**.

### Sound Bank Mapping (Node 2 / DFPlayer)

| Bank | Category | Source SFX Library | Required Files |
| :---: | :--- | :--- | :---: |
| **1-5** | **Classic Chatty** | Michael Baddeley (Printed Droid) | 100+ |
| **6** | **Whistles** | CuriousMarc V3 Pack | 20+ |
| **7** | **Singing** | R2-D2 Vocalizer App | 15+ |
| **8** | **Leia SFX** | Ben Burtt Movie Archive | 5+ |
| **9** | **Music** | John Williams Score | 10+ |

-----

## 4\. Missing Audio & Hardware Audit (Current Gaps)

| Gap | Status | Resolution Path |
| :--- | :---: | :--- |
| **Organic Chat** | **MISSING** | Batch-normalize 100 files to -3dB to prevent power clipping on playback. |
| **DFPlayer Indexing** | **CRITICAL** | Utilize a FAT Sorter script to enforce physical write-order on the SD card (required for strict 14/02 calls). |
| **Scream Loop** | **VERIFIED** | Present in Folder 14/02. Needs 3000ms sustain. |
| **Cantina Sync** | **HARDENED** | Present in Folder 13/02. Linked to Animation 0x04. |

-----

## 5\. Ongoing Research Plan: Autonomous Offline Automations

To ensure Wee2-D2 feels like a living companion rather than a static puppet, we will investigate integrating hardware-level sensors that process environmental data entirely on the ESP32 nodes.

  - [ ] **Capacitive Dome Interactions:** Investigate lining the interior of the 3D-printed dome with copper foil tape wired directly to an ESP32 capacitive touch pin. This allows for physical interaction: a gentle "pet" could trigger a happy chirp, while a harder tap on the head could interrupt an action or trigger the `:SE11 Angry` sequence.
  - [ ] **The Bray Sentry Protocol:** Hardwire an LD2410 mmWave radar sensor or a PIR sensor directly to the master ESP32. This enables a localized "Patrol" or "Sentry" mode where the droid stands guard and sounds an alarm (or triggers `:SE01 Scream`) if a human enters the room while the system is armed.
  - [ ] **Offline Face Tracking:** Research standalone computer vision modules (like the HuskyLens) that process facial recognition directly on their own silicon. By feeding UART coordinate data from the camera to the dome servo node, Wee2-D2 can autonomously turn its head to track people walking by without ever touching the cloud.
  - [ ] **Ambient Light Adaptation:** Install a simple LDR (photoresistor) sensor. As the bright Jasper sun sets and the room darkens, the master node can automatically dim the logic displays to a "night mode" or transition into the silent `:SE15 Stealth` sequence to avoid waking anyone up.
  - [ ] **Ultrasonic Object Avoidance:** Determine the feasibility of mounting HC-SR04 ultrasonic sensors inside the foot shells. If future motorized foot drives are installed, this ensures the droid can freely roam the new house without colliding with walls or furniture.
  - [ ] **Local Voice Recognition (VR):** Research *microWakeWord* on ESP32-S3 for entirely offline "Hey Wee2" trigger interactions (sub-500ms latency, zero cloud dependency).

-----

How do those offline automation concepts look for the build?