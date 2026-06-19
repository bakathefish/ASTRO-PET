<img width="1000" height="1421" alt="image" src="https://github.com/user-attachments/assets/be00f532-b3fc-4bd3-be0e-3153034bed0b" />

## What is it?
 
AstroPet is a small desk pet built for astrophotographers. It consists of two boards: a sensor unit that you leave outside exposed to the sky which reads actual sky conditions in real time, and a display unit that sits on your desk with a cute little animated pet face on a round screen.
 
The pet's mood tells you whether it's worth going outside to shoot tonight. A happy face means go, a sad face means stay in. No internet, no weather app, no phone needed so its ideal for when you're at a dark site in the middle of nowhere and just want a quick answer before dragging all your gear out into the cold.

## Why did i make it?

Everytime i want to go outside and shoot theres always the laziness preventing me im always thinking what if its too bright what if theres too many clouds is the humidity right is it time to go shoot yet or do i wait more by the time iv figured it out all the motivation to shoot has faded or the time to shoot has so i figured if i have a small device pet telling me exactly what to do and if its a good idea to shoot without me ever leaving the comfort of my bed its perfect i wanted something that would work anywhere regardless of if i had wifi right now im only doing the most basic things with the sensors however overtime i plan to improve a lot on the design and firmware since this is just a v1 build of it overtime i plan on adding more moods maybe optional wifi modes that also pull planetary data and moon phase and perhaps tell you what to shoot or an ideal setup to use 

## how does it work

the two boards talk to eachother wirelessly over the esp32s esp now protocol a direct device to device protocol that needs no router no hotspot or internet connection

**board one** the sensor unit- it sits outside reading the data the sensors fire every 5 seconds and the data is then transmitted over to board 2
**board two** the display unit, it sits on your desk receives the packets runs three checks on the data and outputs a face to match all of it 

## Why the ir temperature finds clouds
a clear sky would be a direct line of sight to space which would be cold and the mlx90614 pointed upward would read that cold radiation and return a very very low temperature however if it was pointed at a cloud the temperature would be much higher and when we compare this with the surrounding temperature taken by the other sensor it allows us to predict if clouds are blocking the sky or not without using any internet forecast data or camera since those will be unreliable in the dark.

## the firmware

the firmware is two little arduino sketches, `sensor_unit.ino` for the outside board and `display_unit.ino` for the desk board. i kept it super simple on purpose, theres barely any code so its easy to read and beginner friendly if you wanna build your own or mess around with it.

the sensor board just reads the three sensors and broadcasts them over esp now every 5 seconds. the display board listens, runs the three checks, and draws a happy or sad face. if it stops hearing from the sensor for a bit the pet goes to sleep so you know the link dropped.

right now theres **no gps and no moon phase** in the code, its the bare minimum to get the core thing working and keep it easy to flash. im adding gps + moon phase (and maybe an optional wifi mode) in a **v2** once iv built and tested the boards irl. the gps connector is already on the board so its just a firmware update later.

### flashing it
- arduino ide with the **esp32 by Espressif** board package, pick **ESP32S3 Dev Module**
- sensor board libraries: `Adafruit TSL2591`, `Adafruit MLX90614`, `Adafruit BME280`
- display board library: `TFT_eSPI`
- the round display needs `TFT_eSPI` set up for the **GC9A01** driver in its `User_Setup.h`, if the screen is black or garbled thats almost always why

## assembly

first thing, head to `PCB_Files/` and download both gerber zips (`ASTROPET_SENSOR_PCB.zip` and `ASTROPET_DISPLAY_PCB.zip`) and get them made at jlcpcb. once the boards arrive, populate them using the silkscreen markers as a guide, start with the smaller parts first, everything is hand solderable.

then grab `sensor_unit.ino` and `display_unit.ino` from the `firmware/` folder and flash them using the firmware instructions above. after flashing, connect the round screen to the display unit. power both boards and the pet is ready, pop the sensor unit outside facing the sky and keep the display unit on your desk.

## BOM

full bom with lcsc part numbers is in `BOM.xlsx`. order the pcbs from jlcpcb using the gerber files in `PCB_Files/`.
 
| Qty | Description | Manufacturer | MPN | Supplier | Part No. | Unit (USD) | Total (USD) |
|-----|-------------|--------------|-----|----------|----------|------------|-------------|
| 2 | [ESP32-S3-MINI-1-N4R2 module](https://www.lcsc.com/product-detail/C3013941.html?s_z=n_q_C3013941&globalKeyword=C3013941) | Espressif | ESP32-S3-MINI-1-N4R2 | LCSC | C3013941 | $5.15 | $10.31 |
| 2 | [RES 4.3kΩ 0603](https://www.lcsc.com/product-detail/C2930099.html?s_z=n_q_C2930099&globalKeyword=C2930099) | FOJAN | FRC0603F4301TS | LCSC | C2930099 | $0.002 | $0.003 |
| 7 | [CAP 100nF 0603](https://www.lcsc.com/product-detail/C14663.html?s_z=n_q_C14663&globalKeyword=C14663) | YAGEO | CC0603KRX7R9BB104 | LCSC | C14663 | $0.03 | $0.18 |
| 4 | [CAP 47µF 0805](https://www.lcsc.com/product-detail/C6119904.html?s_z=n_q_C6119904&globalKeyword=C6119904) | HRE | CGA0805X5R476M100MT | LCSC | C6119904 | $0.13 | $0.53 |
| 6 | [RES 10kΩ 0603](https://www.lcsc.com/product-detail/C2930027.html?s_z=n_q_C2930027&globalKeyword=C2930027) | FOJAN | FRC0603J103TS | LCSC | C2930027 | $0.001 | $0.008 |
| 4 | [Tactile button](https://www.lcsc.com/product-detail/C720477.html?s_z=n_q_C720477&globalKeyword=C720477) | XUNPU | TS-1088-AR02016 | LCSC | C720477 | $0.054 | $0.22 |
| 1 | [GPS connector JST 4-pin](https://www.lcsc.com/product-detail/C131334.html?s_z=n_q_C131334&globalKeyword=C131334) | JST | B4B-PH-K-S(LF)(SN) | LCSC | C131334 | $0.047 | $0.047 |
| 1 | [BME280 temp/humidity/pressure](https://www.lcsc.com/product-detail/C92489.html?s_z=n_q_C92489&globalKeyword=C92489) | Bosch | BME280 | LCSC | C92489 | $6.37 | $6.37 |
| 1 | [MLX90614ESF-BAA IR cloud sensor](https://www.lcsc.com/product-detail/C490604.html?s_z=n_q_C490604&globalKeyword=C490604) | Melexis | MLX90614ESF-BAA-000-TU | LCSC | C490604 | $6.56 | $6.56 |
| 1 | [TSL25911FN sky brightness sensor](https://www.lcsc.com/product-detail/C176812.html?s_z=n_q_C176812&globalKeyword=C176812) | AMS | TSL25911FN | LCSC | C176812 | $3.22 | $3.22 |
| 2 | [LED indicator](https://www.lcsc.com/product-detail/C5354976.html?s_z=n_q_C5354976&globalKeyword=C5354976) | Kingbright | APHHS1005LSECK/J3-PF | LCSC | C5354976 | $0.49 | $0.97 |
| 2 | [CAP 22µF](https://www.lcsc.com/product-detail/C5674.html?s_z=n_q_C5674&globalKeyword=C5674) | Samsung | CL21A226MQQNNNE | LCSC | C5674 | $0.039 | $0.078 |
| 2 | [LDO 3.3V AP2112K](https://www.lcsc.com/product-detail/C51118.html?s_z=n_q_C51118&globalKeyword=C51118) | Diodes Inc. | AP2112K-3.3TRG1 | LCSC | C51118 | $0.163 | $0.327 |
| 2 | [CAP 10µF](https://www.lcsc.com/product-detail/C15850.html?s_z=n_q_C15850&globalKeyword=C15850) | Samsung | CL21A106KAYNNNE | LCSC | C15850 | $0.048 | $0.095 |
| 4 | [RES 22Ω 0603](https://www.lcsc.com/product-detail/C23345.html?s_z=n_q_C23345&globalKeyword=C23345) | UNI-ROYAL | 0603WAF220JT5E | LCSC | C23345 | $0.002 | $0.006 |
| 2 | [ESD diode USBLC6-2SC6](https://www.lcsc.com/product-detail/C7519.html?s_z=n_q_C7519&globalKeyword=C7519) | ST | USBLC6-2SC6 | LCSC | C7519 | $0.154 | $0.308 |
| 2 | [Schottky diode MBR0520](https://www.lcsc.com/product-detail/C5204745.html?s_z=n_q_C5204745&globalKeyword=C5204745) | TWGMC | MBR0520 | LCSC | C5204745 | $0.021 | $0.042 |
| 2 | [Ferrite bead BLM18PG121SN1D](https://www.lcsc.com/product-detail/C14709.html?s_z=n_q_C14709&globalKeyword=C14709) | muRata | BLM18PG121SN1D | LCSC | C14709 | $0.017 | $0.034 |
| 2 | [PTC resettable fuse 75mA](https://www.lcsc.com/product-detail/C2830242.html?s_z=n_q_C2830242&globalKeyword=C2830242) | Jinrui | JK-nSMD075/6V | LCSC | C2830242 | $0.039 | $0.077 |
| 4 | [RES 5.1kΩ 0603](https://www.lcsc.com/product-detail/C2907044.html?s_z=n_q_C2907044&globalKeyword=C2907044) | FOJAN | FRC0603F5101TS | LCSC | C2907044 | $0.002 | $0.006 |
| 1 | [Display header 1x7 2.54mm](https://www.lcsc.com/product-detail/C22438157.html?s_z=n_q_C22438157&globalKeyword=C22438157) | Hanxia | HX PM2.54-1x7P ZC-Y | LCSC | C22438157 | $0.12 | $0.12 |
| 1 | [NEO-6M GPS module](https://robu.in/product/neo-6m-gps-module-with-eprom-normal-quality/) * | — | — | Robu.in | 1270231 | $3.00 | $3.00 |
| 1 | [GC9A01 1.28" round IPS display](https://robu.in/product/goldenmorning-gc9a01-7p-240x240-spi-1-28-inch-round-display-module/?gad_source=1&gad_campaignid=17416544847) | — | — | Robu.in | R123209 | $4.00 | $4.00 |
| 2 | [2-layer PCB](https://cart.jlcpcb.com/quote?spm=jlcpcb.Public.2006) | — | — | JLCPCB | — | $2.10 | $4.20 |

**Total: ~$40.50 USD**

\* the neo-6m gps isnt used by the v1 firmware, its only on the board so gps + moon phase can be added later as a firmware update (see the firmware section). you can leave it unpopulated for now if you want.

## PCB 1- Sensor Unit Schematic
<img width="1254" height="890" alt="image" src="https://github.com/user-attachments/assets/387eb00c-4090-4941-8522-82c020f500f5" />

## PCB 1- Sensor Unit Board
<img width="699" height="778" alt="image" src="https://github.com/user-attachments/assets/da1e4bcc-55bd-47d4-9825-041cb42d2b69" />

## PCB 2- Display Unit Schematic
<img width="889" height="629" alt="image" src="https://github.com/user-attachments/assets/34339de9-19a9-4032-b9bc-2f7a38123eea" />

## PCB 2 - Display Unit Board
<img width="551" height="553" alt="image" src="https://github.com/user-attachments/assets/47162c53-ad4b-45b6-b6fa-8b214f50ab22" />

## 3d models / case

the `3d models/` folder has the printable case for the desk (indoors) unit. the round window is for the display.

<img width="755" height="493" alt="image" src="https://github.com/user-attachments/assets/c85898d4-9b1f-404f-9d57-bd25225d3585" />



the outdoors sensor unit still needs a proper weatherproof housing, thats on the v2 list, for now you can leave the board exposed or pop it in any vented box that still lets the sensors see the sky.
