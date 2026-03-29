# 🛠️ Mechanical & Chassis Design
> **HARDWARE MANIFEST** | **SERIAL: MECH-BIGBABY-v1.0**

Wee2-D2 is a highly customized iteration of the **"Big Baby" Astromech** design, originally created by the legendary community astromech designer **Mr. Baddeley**. 

## 🏗️ 3D Printing the Chassis
The Big Baby chassis is engineered to be 100% 3D-printable. It acts as a massive "ridable" astromech platform with a detachable dome that can even be worn!

*   **Repository Access**: The master `.STL` files for the Big Baby project are securely hosted on [Mr. Baddeley's Patreon](https://www.patreon.com/mrbaddeley). You must subscribe to gain access to the official repository files.
*   **Material Selection**: 
    *   **PLA+ / PETG**: Highly recommended for the main chassis body, legs, and dome for high rigidity and dimensional accuracy.
    *   **TPU / Ninjaflex**: Recommended for the drive wheel treads to ensure adequate grip on smooth convention center floors.
*   **Infill Strategy**: 
    *   **Dome & Skins**: 10-15% Gyroid infill (Keep it light to reduce top-heaviness during rotational motion).
    *   **Legs & Ankles**: 30-40% Cubic infill (Requires higher structural strength to support the heavy 20V battery and metal drive motors).
    *   **Motor Mounts & Brackets**: 50%+ or solid walls (Critical for torque transfer without shearing).

## 🛞 Drive & Motion Integration
The Big Baby chassis is designed to house specialized hub motors directly in the feet for incredibly smooth locomotion:
*   **Foot Drives**: 2x [L-faster FLD-5 Hub Motors](../hardware/hub-motor-manual.md) provide the primary forward/reverse capabilities.
*   **Dome Rotation**: The internal dome gear meshes with the [goBILDA 5203 Yellow Jacket Motor](../hardware/gobilda-motor-manual.md).

## 👥 Community Resources
Building a 3D-printed astromech is a massive undertaking. The Wee2-D2 Databank covers the unique *electrical* architecture of this specific droid, but we highly recommend consulting the following community knowledge bases for mechanical slicing profiles, structural engineering, and assembly support:
1.  **[Mr. Baddeley Patreon](https://www.patreon.com/mrbaddeley)**: The official source for the files and community access.
2.  **[Printed-Droid.com](https://www.printed-droid.com/)**: A fantastic, highly-organized secondary resource for Baddeley part documentation and build diaries.
3.  **[Astromech.net Forums](https://astromech.net/)**: The premier builder's repository and engineering forum for astromechs worldwide.
