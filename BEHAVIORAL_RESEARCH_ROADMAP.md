# <i data-lucide="book-open"></i> Behavioral Research Roadmap (v2.7.6)

> **TECHNICAL SPECIFICATIONS** | **BABY ASTROMECH ADAPTATION** | **COMMUNITY STANDARDS**

This document serves as the primary research and engineering roadmap for the long-term personality development of the **Wee2-D2** droid. It synthesizes "Full-Size" industry standards from the R2 Builders Club with the specific constraints of our **Distributed Node Mesh** architecture.

---

## 1. The MarcDuino Cinematic Archive

The MarcDuino system remains the "Industrial Standard" for cinematic astromech behavior. We adopt the **:SE00 through :SE15** sequence set as our functional baseline.

| Sequence | Category | Technical Logic (N1 -> N2 -> N3) | Movie Reference |
| :--- | :--- | :--- | :--- |
| **:SE01** | **Scream** | Open Panels -> High-Pitch Scream -> Red Logic Pulse | ESB: Hoth Attack |
| **:SE02** | **Wave** | Panel oscillation -> Whistle -> Teal Logic Scan | ANH: Sandcrawler |
| **:SE03** | **Smirk** | Back-and-forth dome sway -> Double-whistle -> Teal Pulse | ANH: Restraining Bolt |
| **:SE05** | **Cantina** | Rhythmic march -> Music Playback -> "Marching Ants" LEDs | ANH: Cantina Scene |
| **:SE06** | **Faint** | Immediate Brake -> Groan SFX -> Random Logic Flicker | ANH: Jawas Capture |
| **:SE08**| **Leia** | Stationary Dome -> "Message" Audio -> Dim Blue Holo-Pattern | ANH: Help me Obi-Wan |
| **:SE09** | **Disco** | Continuous Dome Scan -> Orchestral Bleeps -> **Rainbow Logic** | Community Flavor |
| **:SE15** | **Stealth** | Same Logic as SE01 but with **NO Audio** (Motion/Light only) | Night Ops |

### Source Repositories & Deep-Dive Links
- **Official Documentation**: [MarcDuino.com](https://www.marcduino.com)
- **Firmware Logic**: [CuriousMarc GitHub](https://github.com/curiousmarc/MarcDuino)
- **Sequence Visuals**: [Printed Droid Tutorial](https://printed-droid.com/tutorials/marcduino-sequences/)

---

## 2. "Baby Astromech" Adaptation Protocol

The Wee2-D2 is a high-fidelity "Baby Astromech" (3D files by Michael Baddeley). We must adapt full-size logic to our specific hardware constraints.

### Adaptation Logic Matrix
| Hardware | Constraint | Adaptation Profile |
| :--- | :--- | :--- |
| **Dome Motor** | **160° Limit** | Full-size 360° sweeps must be scaled to ±80° from center with increased acceleration to maintain cinematic "snap." |
| **LED Matrices** | **WLED Segments** | Standard 24x2 patterns are re-mapped to our 4-Segment system (0:PSI Front, 1:PSI Rear, 2:Logic Front, 3:Logic Rear). |
| **Communication** | **Distributed Mesh** | Single serial commands are fragmented into ESP-NOW payloads (Motion) and UART pulses (Lights/Audio). |

### Priority Sequence: The "Nervous Shake"
To simulate distress on a 160-degree dome, we implement the **Micro-Jitter Protocol**.
- **Logic**: Node 1 oscillates the servo ±5 degrees at 20Hz for 800ms.
- **Sync**: Sound Hub plays Folder 14/File 02 (Angry/Panic).

---

## 3. Audio Procurement & Sync Logic

Personality is defined by the **Emotional Sound Bank**. We synchronize with the community's **9-Bank Standard**.

### Sound Bank Mapping (Node 2 / DFPlayer)
| Bank | Category | Source SFX Library | Required Files |
| :---: | :--- | :--- | :---: |
| **1-5** | **Classic Chatty** | Michael Baddeley (Printed Droid) | 100+ |
| **6** | **Whistles** | CuriousMarc V3 Pack | 20+ |
| **7** | **Singing** | R2-D2 Vocalizer App | 15+ |
| **8** | **Leia SFX** | Ben Burtt Movie Archive | 5+ |
| **9** | **Music** | John Williams Score | 10+ |

### Audio Procurement Nodes
- **[Printed Droid SFX Pack](https://printed-droid.com/downloads/)**: Verified, clean WAV/MP3 files mapped for Baddeley builds.
- **[Astromech.net Forums](https://astromech.net/forums/forumdisplay.php?81-Electronics-Sound)**: Central hub for user-submitted sound "Remixes."
- **[R2-D2 Vocalizer](https://vocalizer.r2d2.xyz/)**: Essential for generating new, non-repetitive "Organic" bleeps.

---

## 4. Missing Audio Audit (Current Gaps)

| Gap | Status | Resolution Path |
| :--- | :---: | :--- |
| **Organic Chat** | **MISSING** | Batch-normalize 100 files from Printed Droid "Standard Pack." |
| **Scream Loop** | **VERIFIED** | Present in Folder 14/02. Needs 3000ms sustain. |
| **Cantina Sync** | **HARDENED** | Present in Folder 13/02. Linked to Animation 0x04. |
| **Simon Says** | **ROADMAP** | Require 4 distinct "Success" beeps and 4 "Fail" groans. |

---

## 5. Ongoing Research Plan

- [ ] **Interactive Gameplay**: Determine the feasibility of a "Simon Says" light pattern game using the Front Logic LEDs.
- [ ] **Voice Recognition (VR)**: Research ESP32-S3 Voice Command integration using the onboard microphones for "Hey R2" interactions.
- [ ] **Holographic Sync**: Research "Holographic" light flicker profiles used in the Reel R2 community for future projector installation.
