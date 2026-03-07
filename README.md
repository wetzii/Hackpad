# Hackpad V1
This is my first real try for the **Hack Club Blueprint** challenge! I wanted to build something functional and learn the full process from PCB design to 3D modeling.

![3D-View in Fusion 360](Screenshots/Rendert_hackpad.png)

## 1. The Idea
My goal was to create a clean and simple macro pad with the following features:
* **16 Mechanical Switches:** A full 4x4 matrix for maximum input options.
* **OLED Display:** A 0.91" screen to show status or a clock.
* **Rotary Encoder:** An EC11 knob for volume control or scrolling.
* **Simplicity:** Keeping the design beginner-friendly but powerful.

### Bill of Materials (BOM)
To build this, I am using the following components:
* **16x** 1N4148 Diodes (Through-hole).
* **16x** MX-Style Switches (Kailh Polia).
* **1x** EC11 Rotary Encoder.
* **2x** 100nF Ceramic Capacitors.
* **1x** 0.91-inch OLED Display (SSD1306).
* **16x** White Blank DSA Keycaps.
* **1x** Seeed Studio XIAO RP2040 Controller.

### Use Case
I will use it as a custom **Numpad with extra Shortcuts**. The OLED screen will act as a system monitor or a simple clock to keep track of time while working.

---

## 2. Schematic & Electronics
I designed the circuit to be reliable and easy to solder. It uses a row-column matrix to handle all 16 switches with the limited pins of the XIAO.
![Schematic](Screenshots/FormworkPlan.png)

---

## 3. PCB Design
This is the heart of the Hackpad. I routed everything carefully to fit the 4x4 grid and the extra components like the encoder and OLED.
![PCB Layout](Screenshots/PCB.png)

---

## 4. 3D Modeling & Case
This was my first time 3D modeling anything! I used **Fusion 360** for the case design to ensure everything fits perfectly.

### KiCad 3D Preview
First, I checked the component placement in KiCad's 3D viewer.
![3D-View in KiCad](Screenshots/PCB_3d_View_V1.png)

### Fusion 360 Implementation
I exported the PCB as a `.step` file and imported it into Fusion 360 to build the case around it.
* **PCB Size:** 100mm x 100mm – a perfect size for a beginner like me.
* **Case Interior:** 100.5mm x 100.5mm to ensure a snug fit for the PCB.
* **Case Exterior:** 120mm x 120mm total width.
* **Switch Cutouts:** 14.2mm x 14.2mm for easy snapping of the MX switches.
* **Dimensions:** 12mm total height with a 3mm thick floor for stability.

![3D-View in Fusion 360](Screenshots/Full_Case_Fusion360.png)

> **Note:** The top plate might need some light sanding for a perfect fit, but I can handle these tolerances during assembly!

---

## 5. Firmware
The Hackpad runs on **QMK Firmware**. 
* **Layout:** A standard Numpad on the left 3 columns, with 4 customizable shortcut keys on the right.
* **OLED:** Displays the active layer and system status like Num Lock.
* **Encoder:** Programmed for volume control.