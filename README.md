# **altair-electronics**

![Board View 1](https://github.com/Altair-GMRT/altair-electronics/blob/main/design/v1.0/altair_brd_3d1.png?raw=true)
![Board View 2](https://github.com/Altair-GMRT/altair-electronics/blob/main/design/v1.0/altair_brd_3d2.png?raw=true)
![Board View 3](https://github.com/Altair-GMRT/altair-electronics/blob/main/design/v1.0/altair_brd_3d3.png?raw=true)

## **1. Contents**

- **altair-mcu/**

    This folder contains the Arduino IDE source code for the Altair MCU's firmware. Make sure the following libraries have been installed on your IDE before compiling:

    1. [**Adafruit GFX**](https://github.com/adafruit/Adafruit-GFX-Library)
    2. [**Adafruit SSD1306**](https://github.com/adafruit/Adafruit_SSD1306)
    3. [**Adafruit Sensor**](https://github.com/adafruit/Adafruit_Sensor)
    4. [**Adafruit BNO055**](https://github.com/adafruit/Adafruit_BNO055)

- **design/**

    This folder contains the Eagle/Fusion schematics and board designs, including the libraries used.

## **2. Electronics Design**
The robot will be powered by 4s 35c 5200mAh Li-Po battery. Hence, the battery voltage will be in the range of 12.8V - 16.8V with a maximum discharge of 182A. The Raspberry Pi 5 needs 5V 5A power supply, and 20 Dynamixel MXs need 14V 2A per servo. We will convert the battery voltage to supply those two with a 5V regulator and a Buck-Boost Converter, respectively. Read more about the design at ```design/simulations```.

### **2.1 Buck-Boost Converter**
The buck and the boost in the Buck-Boost Converter will be used interchangeably. The equation describing the behaviour of the buck is:

$$V_{out} = DV_{in}$$

$$I_{ripple} = V_{out}\left(\frac{1}{R} \pm \frac{1 - D}{2L}T \right)$$

$$V_{ripple} \propto \frac{(1-D)V_{out}T^2}{8LC}$$

and for the boost:

$$V_{out} = \frac{1}{1 - D}V_{in}$$

$$I_{ripple} = V_{in}\left(\frac{1}{R(1-D)^2} \pm \frac{1}{2L}DT\right)$$

$$V_{ripple} \propto \frac{DTV_{out}}{RC}$$

Consider the following table: 

|No.|Parameter|Value|
|:---:|:---:|:---:|
|1|$D_{buck}$|$[0.83, 1]$|
|2|$D_{boost}$|$[0, 0.086]$|
|3|$V_{in}$|$[12.8, 16.8]\text{V}$|
|4|$V_{out}$|$14\text{V}$|
|5|$I_{max}$|$30\text{A}$|
|6|$T_S$|$12.5\mu\text{s}$|
|7|$f_S$|$80\text{kHz}$|
|8|$R$|$V_{out}/I_{max} = 0.5\Omega$|

We obtain the optimal (smallest possible, yet acceptable performance) value of $L = 330\mu\text{H}$ and $C = 4.7\text{mF}$ in 3 parallels.

### **2.2 Components**
The following table shows the entire components required for assembling a complete circuit.

| No. | Component Name | Qty. | Datasheets |
| :---: | :--- | :---: | :---: |
| 1 | **ESP32-WROOM-32D** | | |
| 2 | **BNO055** 9-Axis IMU | | |
| 3 | **SSD1306** OLED Display | | |
| 4 | **LM2596S-5.0** 5V 3A Regulator | | |
| 5 | **1N5824** Schottky Diode | | |
| 6 | **CDRH127R** Power Inductor | | |
| 7 | **IRF9540** P-Channel Power MOSFET | | |
| 8 | **S9013** NPN Transistor | | |
| 9 | **SR5100 & 1N58219** Schottky Diode | | |
| 10 | **MOLEX 22-03-5035** Dynamixel Connector | | |
| 11 | **USB Female Type-C** | | |
| 12 | **USB Female Type-A** | | |
| 13 | **SMD Button** | | |