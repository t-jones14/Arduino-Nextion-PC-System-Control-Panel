<p align="center">

[![Contributors](https://img.shields.io/github/contributors/t-jones14/Arduino-Nextion-PC-System-Control-Panel.svg?style=for-the-badge)](https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/graphs/contributors)
[![Forks](https://img.shields.io/github/forks/t-jones14/Arduino-Nextion-PC-System-Control-Panel.svg?style=for-the-badge)](https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/network/members)
[![Stargazers](https://img.shields.io/github/stars/t-jones14/Arduino-Nextion-PC-System-Control-Panel.svg?style=for-the-badge)](https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/stargazers)
[![Issues](https://img.shields.io/github/issues/t-jones14/Arduino-Nextion-PC-System-Control-Panel.svg?style=for-the-badge)](https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/issues)
[![MIT License](https://img.shields.io/github/license/t-jones14/Arduino-Nextion-PC-System-Control-Panel.svg?style=for-the-badge)](https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/blob/main/LICENSE)
</p>

<p align="center">
<a href="https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel"><img src="/Source/Images/project-logo.png" alt="Logo" width="313"></a>

<h3 align="center">Arduino &amp; Nextion PC System Control Panel
</h3><br>
<br>
<p align="center">
An external PC system control panel built with Arduino Nano and Nextion Display<br>
<a align="center" href="https://t-jones14.github.io/Arduino-Nextion-PC-System-Control-Panel/">Explore the docs »</a><br>
<a align="center" href="https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/issues">Report Bug »</a><br>
<a align="center" href="https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/issues">Request Feature »</a>
</p>
</p>

<br>

## About The Project
<img src="/Source/Images/complete-build.jpg">

This project started when I decided to build a computer. Having never built one before, I decided to go all-out (kind of). I wanted it to be unique and highlight my abilities. Throughout the design and construction phase I entirely neglected to incorporate any system controls and decided to get creative. To stick with the "exposed" theme of the build the idea to incorporate a raw, yet-modern approach was born.

<a href="https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel"><img src="/Source/Images/control-panel-display-pcb-mounted.jpg" alt="Finished Project"></a>

### Built With

* Arduino Nano V3.0 (Elegoo Nano V3.0+) w/ ATmega328P: <a href="https://www.amazon.com/gp/product/B07TTN2HMQ">Amazon</a>
* Nextion Enhanced 3.5" HMI Resistive Touchscreen: <a href="https://www.amazon.com/gp/product/B08535V3KW">Amazon</a>

## Getting Started

Overall, this project is rather simple... If you're somewhat semi-technically inclined.

I highly encourage you to do your research and not take on any task you're not 110% comfortable with. As a reminder, this project is provided AS-IS with ZERO WARRANTY in any way, shape, or form. You're on your own. If you fry your motherboard, that's on you.

The saying goes: "*Measure twice, cut once.*" - Abide by it.

### Here's What You Will Need

Links to all used components included. I am not receiving any commissions if you use any of the links below.

* General Electronics Experience (Highly Recommended)
* Various Electronics Components
    * X3 Schottky Diodes: <a href="https://www.amazon.com/gp/product/B07YG8K1R9">Amazon</a>
    * X2 LED: <a href="https://www.amazon.com/gp/product/B01C19ENDM">Amazon</a>
    * X2 Pushbuttons: <a href="https://www.amazon.com/gp/product/B01CGMP9GY">Amazon</a>
    * X4 Resistors: <a href="https://www.amazon.com/gp/product/B07BKVNBH6">Amazon</a>
    * X2 BC548 Power Transistors: <a href="https://www.amazon.com/gp/product/B071P849QB">Amazon</a>
    * 2.54mm Pitch Dupont Connectors: <a href="https://www.amazon.com/gp/product/B07D91MQQ8">Amazon</a>
    * Wire Strippers: <a href="https://www.amazon.com/gp/product/B07GJFVXXD">Amazon</a>
    * Wire Crimp Tool: <a href="https://www.amazon.com/gp/product/B01CE4FAMW/">Amazon</a>
    * Soldering Iron: <a href="https://www.amazon.com/gp/product/B07SCPZJYS">Amazon</a>
    * X1 Blank Prototyping PCB: <a href="https://www.amazon.com/gp/product/B07ZYNWJ1S">Amazon</a>
    * X1 Breadboard: <a href="https://www.amazon.com/gp/product/B07DL13RZH">Amazon</a>
    * Jumper Wires: <a href="https://www.amazon.com/gp/product/B01EV70C78">Amazon</a>
* Arduino IDE: <a href="https://www.arduino.cc/en/software">Link</a>
* Nextion Editor: <a href="https://nextion.tech/nextion-editor/">Link</a>
* A motherboard with front-panel system control headers for a powerswitch, reset switch, +5V & Ground connection

## Wiring Schematic

#### A Few Notes Regarding the Schematic

1. JP1 & JP2 are to disconnect the RX/TX pins from the Arduino Nano in order to be able to upload code to the Nano without removing it from the PCB. If you leave these connected or forego the jumpers, you will not be able to upload any code to the Arduino if the Nextion is connected since the RX and TX pins are used when the board is communicating via USB.
2. J1 Pin 1 MUST be a constant +5V to power the board and display. I have my BIOS set to always supply +5 to USB so I just ran a USB from an available USB header off the motherboard.
3. J2 Pin 4 must be +5V from the motherboard ONLY when the MB is alive. I used the +5V on the System Panel Connector header for the System Warning Speaker. See below.
4. You can forego the LEDs and Pushbuttons. I opted for them for extra effect and as a backup in case the Nextion display ever stopped working before I could replace it. Better to be over-prepared than under-prepared.
5. J1 are male headers for connection to the Nextion display.
6. J2 are male headers for the wiring from the motherboard front-panel system control headers.
7. If you're using LED's from your motherboard's LED connections, ensure they are regulated. If on the off-chance they are not, you will need to integrate resistors in-series prior to the LED's.

<img src="/Source/Fritzing/Schematic.png">
Image: Wiring Schematic

For the Fritzing file <a href="https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/blob/main/Source/Fritzing/Schematic.fzz">click here</a>.

## Breadboard Prototype / Bench Test

<img src="/Source/Images/breadboard.jpg">
Image: Breadboard Prototype

<img src="/Source/Images/proto-pcb-mounted.jpg">
Image: Final PCB Prototype

## Motherboard Wiring

Please reference your motherboard's user manual or contact your motherboard manufacturer to confirm wiring / operation. Again, this software and hardware is provided **AS-IS** with **NO WARRANTY** expressed or implied. I **am not** responsible if you fry your motherboard. Please DO NOT continue if you're not confident in your abilities. I cannot tell you how many times I confirmed details and reconfirmed before attaching any wires up to my $250 motherboard.

<img src="/Source/Images/x570pro-excerpt.png">
Image: ASUS Prime X570-Pro User Manual Excerpt
Link: <a href="https://dlcdnets.asus.com/pub/ASUS/mb/SocketAM4/PRIME_X570-PRO/E17432_PRIME_X570-PRO_UM_v3_web.pdf">Asus Prime X570-Pro User Manual</a>

<img src="/Source/Images/X570Pro-headers.jpg">
Image: Motherboard System Panel Connection Headers

## Roadmap

See the [open issues](https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel/issues) for a list of proposed features (and known issues).

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

Distributed under the GNU General Public License V3.0. See `LICENSE` for more information.

## Contact

Taylor Jones - taylor@nexgendms.com

Project Link: [https://github.com/github/t-jones14/Arduino-Nextion-PC-System-Control-Panel](https://github.com/t-jones14/Arduino-Nextion-PC-System-Control-Panel)

## Acknowledgements

* [Read Me Template by othneildrew](https://github.com/othneildrew/Best-README-Template)
