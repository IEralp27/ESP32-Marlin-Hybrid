<p align="center"><img src="buildroot/share/pixmaps/logo/marlin-outrun-nf-500.png" height="250" alt="MarlinFirmware's logo" /></p>

<h1 align="center">Marlin 2.1.x - ESP32 Hybrid CoreXY Controller</h1>
<h3 align="center">Custom Firmware for 38-Pin Type-C ESP32-WROOM</h3>

<p align="center">
    <a href="/LICENSE"><img alt="GPL-V3.0 License" src="https://img.shields.io/github/license/marlinfirmware/marlin.svg"></a>
    <a href="#"><img alt="Kinematics" src="https://img.shields.io/badge/Kinematics-CoreXY-orange.svg"></a>
    <a href="#"><img alt="MCU" src="https://img.shields.io/badge/MCU-ESP32_WROOM-blue.svg"></a>
    <a href="#"><img alt="Display" src="https://img.shields.io/badge/Display-2004_I2C-brightgreen.svg"></a>
</p>

## 🚀 About This Project

This repository is a highly customized fork of **Marlin 2.1.x**, specifically engineered to run a **CoreXY** 3D printer using a standard [38-Pin Type-C ESP32-WROOM Module](https://www.komponentci.net/esp32-wroom-wifi-ve-bluetooth-modulu-38-pin-type-c-pmu60767). 

Running a 3D printer on an ESP32 often comes with severe GPIO limitations, boot-loop issues, ADC noise, and 3.3V logic constraints. This project solves all of these hardware bottlenecks through a custom "Hybrid" electronic setup.

## ⚡ Key Hardware Modifications & Engineering Solutions

### 1. Optocoupler Isolation (3.3V to 5V/12V/24V)
The ESP32 operates on 3.3V logic, which is often insufficient or unsafe for driving heavy MOSFETs directly.
* **3x Optocouplers** are implemented for the **Hotend Heater**, **Bed Heater**, and **Turbo Fan (Part Cooling)**. 
* This provides complete galvanic isolation, protecting the ESP32 from high-voltage spikes while perfectly shifting the logic level to trigger the power MOSFETs.

### 2. Temperature ADC Stabilization (RC Filter)
ESP32 ADCs are notoriously noisy, causing extreme temperature fluctuations in Marlin.
* A custom **RC Filter** is applied to the Hotend thermistor circuit using a **10uF Capacitor** and a **4.7K Pull-up Resistor**.
* This results in dead-stable temperature readings.

### 3. Thermal Protection Tweaks (Important Note)
Because the `10uF` capacitor in the RC filter introduces a slight electrical delay (lag) in temperature reading during rapid heating, Marlin's strict thermal runaway protection may trigger false "Heating Failed" errors.
* **Modification:** Hotend thermal protection strictness has been bypassed/relaxed to accommodate the capacitor's curve.
* **How to Re-enable:** If you want to turn the standard safety back on (or if you use a smaller capacitor), go to `Configuration.h`, find `#define THERMAL_PROTECTION_HOTEND`, and uncomment/adjust the `WATCH_TEMP_PERIOD` to a higher value.

### 4. I2C 2004 LCD + Hardware SPI SD Card Integration
Marlin often struggles to run both an SD Card and an I2C screen on ESP32 due to pin sharing.
* **SD Card:** Uses pure Hardware VSPI (Pins 18, 19, 34). The `CS` (Chip Select) pin was moved to **GPIO 0**. This prevents the infamous ESP32 boot-loop issue (as GPIO 0 acts as a boot-strapping pin, it ignores SD card noise during startup).
* **LCD Display:** A standard 2004 Character LCD with an I2C backpack is independently routed to the default ESP32 I2C pins (**SDA: 21, SCL: 22**).

### 5. Independent Limit Switches & Extruder Re-routing
* Freed from the traditional shared limit switch necessity. X, Y, and Z min pins are independently assigned (32, 15, 5).
* Extruder (E0) Step/Dir signals are safely moved to pins 14 and 23 to avoid PWM conflicts.

---

## ⚙️ Pin Map Overview (`pins_ESP32.h`)

| Component | ESP32 Pin | Notes |
| :--- | :--- | :--- |
| **X / Y / Z Min** | `32` / `15` / `5` | Independent endstops |
| **X Stepper** | Step: `25` / Dir: `26` | En: `33` (Shared Enable) |
| **Y Stepper** | Step: `27` / Dir: `12` | En: `33` |
| **Z Stepper** | Step: `16` / Dir: `17` | En: `33` |
| **E0 Stepper** | Step: `14` / Dir: `23` | Re-routed for stability |
| **Heater 0 (Hotend)**| `13` | Routed through Optocoupler |
| **Heater Bed** | `4` | Routed through Optocoupler |
| **Turbo Fan** | `2` | Routed through Optocoupler |
| **Temp 0 (Hotend)** | `36` (VP) | RC Filtered (10uF + 4.7K) |
| **Temp Bed** | `39` (VN) | Standard 4.7K Pull-up |
| **SD MOSI/MISO/SCK** | `19` / `34` / `18` | Hardware VSPI |
| **SD CS (Chip Select)**| `0` | Solves boot-loop conflict |
| **I2C SDA / SCL** | `21` / `22` | 2004 LCD Display |

---

## 📂 How to Use
1. Download or clone this repository.
2. Open the folder using **VS Code** with the **PlatformIO** extension installed.
3. Review `Configuration.h` to ensure the CoreXY settings match your physical belt routing.
4. Click the PlatformIO **Build** button (Tick icon).
5. Connect your 38-Pin Type-C ESP32-WROOM via USB and click **Upload** (Arrow icon).

---

*(The base Marlin 3D Printer Firmware is published under the GPL license. For more information about the base firmware, visit the [Marlin Home Page](https://marlinfw.org/)).*
*(This project was developed with the help of AI, and I've been doing some intense mental gymnastics on it for the past 2-3 days. I'm leaving the project as it is for now because my university classes are starting and I have other projects to catch up on. If you have any questions, feel free to reach out and I'll do my best to answer them!)*
