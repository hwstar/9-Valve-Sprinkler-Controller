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
* Board Fits in a platic PLC06 case available on ALIEXPRESS.

## Hardware Description


### I2C Bus


9 Triacs are used to switch the solenoid valves. 8 of these triac drivers  valves 1 through 9 are controlled by a single PCA9554 at I2C address 0x38 (Valve 0 output is directly connected to GPIO19). The PCA9554 is attached to I2C bus A. GPIO22 is the SCL signal, and GPIO21 is the SDA signal. The DS1307 is attached to the I2C bus, and is at address 0x68. The I2C bus also goes to the expansion connector for future valve expansion.

#### Table 1. I2C Addresses

|Device Address|Device|
|--------------|------------------------------|
|0x38          | PCA9554 IO Expander          |
|0x68          | DS1307 Real Time Clock       |

#### Table 2. PCA9554 I2C Address Solder Jumpers
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


### Display

The display used is a widely available 1602 type. It is interfaced to the ESP32 in four bit parallel mode. 





 


