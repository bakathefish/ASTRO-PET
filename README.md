# ASTRO-PET
## What is it?
 
AstroPet is a small desk pet built for astrophotographers. It consists of two boards: a sensor unit that you leave outside exposed to the sky which reads actual sky conditions in real time, and a display unit that sits on your desk with a cute little animated pet face on a round screen.
 
The pet's mood tells you whether it's worth going outside to shoot tonight. A happy face means go, a sad face means stay in. No internet, no weather app, no phone needed so its ideal for when you're at a dark site in the middle of nowhere and just want a quick answer before dragging all your gear out into the cold.

## Why did i make it?

Everytime i want to go outside and shoot theres always the laziness preventing me im always thinking what if its too bright what if theres too many clouds is the humidity right is it time to go shoot yet or do i wait more by the time iv figured it out all the motivation to shoot has faded or the time to shoot has so i figured if i have a small device pet telling me exactly what to do and if its a good idea to shoot without me ever leaving the comfort of my bed its perfect i wanted something that would work anywhere regardless of if i had wifi right now im only doing the most basic things with the sensors however overtime i plan to imporve a lot on the design and firmware since this is just a v1 build of it overtime i plan on adding more moods maybe optional wifi modes that also pull platery data and moon phase and perhaps tell you what to shoot or an ideal setup to use 

## how does it work

the two boards talk to eachother wirelessly over the esp32s esp now protocol a direct device to device protocol that needs no router no hotspot or internet connection

**board one** the sensor unit- it sits outside reading the data the sensors fire every 5 seconds and the data is then tramitted over to board 2
**board two** the display unit, it sits on your desk recieves the packets runs three checks on the data and outputs a face to match all of it 

## Why the ir tempratiure finds clouds
a clear sky would be a direct line of sight to space which would be cold and the mlx90614 pointed upward would read that cold raditon and return a very very low templrature however if it was pointed at a clouid the temprature would be much higher and when we compare this wiht the surrounding temprature taken by the other sensor it allows us to predict if clouds are blocking the sky or not without using any internet forcast data or camera since those will be unreliable in the dark.

## Full BOM with LCSC part numbers is in `BOM.xlsx`. Order the PCBs from JLCPCB using the Gerber files in `PCB_Files/`.
 
| Qty | Description | Manufacturer | MPN | Supplier | Part No. | Unit (USD) | Total (USD) |
|-----|-------------|--------------|-----|----------|----------|------------|-------------|
| 2 | ESP32-S3-MINI-1-N4R2 module | Espressif | ESP32-S3-MINI-1-N4R2 | LCSC | C3013941 | $5.15 | $10.31 |
| 2 | RES 4.3kΩ 0603 | FOJAN | FRC0603F4301TS | LCSC | C2930099 | $0.002 | $0.003 |
| 7 | CAP 100nF 0603 | YAGEO | CC0603KRX7R9BB104 | LCSC | C14663 | $0.03 | $0.18 |
| 4 | CAP 47µF 0805 | HRE | CGA0805X5R476M100MT | LCSC | C6119904 | $0.13 | $0.53 |
| 6 | RES 10kΩ 0603 | FOJAN | FRC0603J103TS | LCSC | C2930027 | $0.001 | $0.008 |
| 4 | Tactile button | XUNPU | TS-1088-AR02016 | LCSC | C720477 | $0.054 | $0.22 |
| 1 | GPS connector JST 4-pin | JST | B4B-PH-K-S(LF)(SN) | LCSC | C131334 | $0.047 | $0.047 |
| 1 | BME280 temp/humidity/pressure | Bosch | BME280 | LCSC | C92489 | $6.37 | $6.37 |
| 1 | MLX90614ESF-BAA IR cloud sensor | Melexis | MLX90614ESF-BAA-000-TU | LCSC | C490604 | $6.56 | $6.56 |
| 1 | TSL25911FN sky brightness sensor | AMS | TSL25911FN | LCSC | C176812 | $3.22 | $3.22 |
| 2 | LED indicator | Kingbright | APHHS1005LSECK/J3-PF | LCSC | C5354976 | $0.49 | $0.97 |
| 2 | CAP 22µF | Samsung | CL21A226MQQNNNE | LCSC | C5674 | $0.039 | $0.078 |
| 2 | LDO 3.3V AP2112K | Diodes Inc. | AP2112K-3.3TRG1 | LCSC | C51118 | $0.163 | $0.327 |
| 2 | CAP 10µF | Samsung | CL21A106KAYNNNE | LCSC | C15850 | $0.048 | $0.095 |
| 4 | RES 22Ω 0603 | UNI-ROYAL | 0603WAF220JT5E | LCSC | C23345 | $0.002 | $0.006 |
| 2 | ESD diode USBLC6-2SC6 | ST | USBLC6-2SC6 | LCSC | C7519 | $0.154 | $0.308 |
| 2 | Schottky diode MBR0520 | TWGMC | MBR0520 | LCSC | C5204745 | $0.021 | $0.042 |
| 2 | Ferrite bead BLM18PG121SN1D | muRata | BLM18PG121SN1D | LCSC | C14709 | $0.017 | $0.034 |
| 2 | PTC resettable fuse 75mA | Jinrui | JK-nSMD075/6V | LCSC | C2830242 | $0.039 | $0.077 |
| 4 | RES 5.1kΩ 0603 | FOJAN | FRC0603F5101TS | LCSC | C2907044 | $0.002 | $0.006 |
| 1 | Display header 1x7 2.54mm | Hanxia | HX PM2.54-1x7P ZC-Y | LCSC | C22438157 | $0.12 | $0.12 |
| 1 | NEO-6M GPS module | — | — | Robu.in | 1270231 | $3.00 | $3.00 |
| 1 | GC9A01 1.28" round IPS display | — | — | Robu.in | R123209 | $4.00 | $4.00 |
| 2 | 2-layer PCB | — | — | JLCPCB | — | $2.10 | $4.20 |
 
**Total: ~$40.50 USD**

## PCB 1- Sensor Unit Schematic
<img width="1254" height="890" alt="image" src="https://github.com/user-attachments/assets/387eb00c-4090-4941-8522-82c020f500f5" />

## PCB 1- Board
<img width="699" height="778" alt="image" src="https://github.com/user-attachments/assets/da1e4bcc-55bd-47d4-9825-041cb42d2b69" />

## PCB 2- Schematic
<img width="889" height="629" alt="image" src="https://github.com/user-attachments/assets/34339de9-19a9-4032-b9bc-2f7a38123eea" />

## PCB 2 - Board
<img width="551" height="553" alt="image" src="https://github.com/user-attachments/assets/47162c53-ad4b-45b6-b6fa-8b214f50ab22" />



