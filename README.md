# 9 Valve Sprinkler controller

This is the code and documentation repository for a 9 valve sprinkler
controller based on an ESP32. It has the following features:

* Uses a 40VA 24VAC wall transformer with an internal fuse.
* Operates the 24 Volt AC sprinkler valves commonly used for irrigation.
* 9 Indpendently controllable valve outputs.
* Optional 1602 LCD display.
* Optional Front panel buttons.
* Real time clock.
* Individual triac valve drivers rated for 0.5A each.
* Monitoring of the total valve current.
* Safety watchdog relay to help prevent overwatering if the code stops running.
* Expansion connector for future valve expanders.
* Board Fits in a plastic PLC06 case available on ALIEXPRESS.

## Hardware Description

### Serial Connector

The Serial connector J301 is pinned out to accept an FTDI cable. It is a 1x6 2.54mm pitch header located to the right of the ESP32 board. The serial connector is used to upload firmware to the Sprikler controller should the OTA programming fail.  The pinout of this connector is:


#### Table 1. FTDI Connector

|PIN| Signal|
|---|------------------------- |
| 1 | Ground |
| 2 | No connection |
| 3 | No Connection |
| 4 | RXD referenced to ESP32 |
| 5 | TXD referenced to ESP32 |
| 6 | No Connection |

### Expansion Connector

The expansion connector J201 is an 8 pin 3mm pitch Molex micro fit connector (43025 series). It will allow for future expansion of the sprinkler controller to add additional zones.

#### Table 2. Expansion Connector

|PIN| Signal|
|---|-----------------------------|
| 1 | 24VAC live |
| 2 | DC Ground |
| 3 | I2C SCL |
| 4 | DC Ground |
| 5 | 24VAC Return |
| 6 | 3.3V
| 7 | I2C SDA |
| 8 | DC Ground |



### I2C Bus


9 Triacs are used to switch the solenoid valves. 8 of these triac drivers  valves 1 through 9 are controlled by a single PCA9554 at I2C address 0x38 (Valve 0 output is directly connected to GPIO19). The PCA9554 is attached to I2C bus A. GPIO22 is the SCL signal, and GPIO21 is the SDA signal. The DS1307 is attached to the I2C bus, and is at address 0x68. The I2C bus also goes to the expansion connector for future valve expansion.

#### Table 3. I2C Addresses

|Device Address|Device|
|--------------|------------------------------|
|0x38          | PCA9554 IO Expander          |
|0x68          | DS1307 Real Time Clock       |

#### Table 4. PCA9554 I2C Address Solder Jumpers
|SJ401|SJ402|SJ403|I2C Device Address|
|-----|-----|-----|------------------|
| -   | -   | -   | 0x38 (default)   |
| -   | -   | X   | 0x39             |
| -   | X   | -   | 0x3A             |
| -   | X   | X   | 0x3B             |
| X   | -   | -   | 0x3C             |
| X   | -   | X   | 0x3D             |
| X   | X   | -   | 0x3E             |
| X   | X   | X   | 0x3F             |

'X' Denotes a solder bridge

The I2C address of the master controller need to remain at the default of 0x38. The other addresses will be used with valve expanders, should they be developed in the future.

### Display

The display used is a widely available 3.3V 1602 type. It is interfaced to the ESP32 in four bit parallel mode. 

#### Table 5. Display Signals
|GPIO|Display Signal Name|
|------|-----------------------|
|GPIO17| RS                    |
|GPIO18| E                     |
|GPIO23| DB4                   |
|GPIO25| DB5                   |
|GPIO26| DB6                   |
|GPIO27| DB7                   |

### Buttons

The 3 momentary buttons are connected directly to the ESP32. With associated definintions in the .yaml file, they provide a way to manually initiate operations in case the homeassistant server goes off line.

#### Table 6. Button Inputs
|GPIO| Button Location|
|------|-------------------------|
|GPIO32| Button 1 (Top)          |
|GPIO33| Button 2 (Middle)       |
|GPIO34| Button 3 (Bottom)       |
|GPIO0 | Boot (Internal Only)    |










 


