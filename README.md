# 9 Valve Sprinkler controller

This is the code and documentation repository for a 9 valve sprinkler
controller based on an ESP32. It has the following features:

* Uses a 40VA 24VAC wall transformer with an internal fuse.
* Operates the 24 Volt AC sprinkler valves commonly used for irrigation.
* 9 Indpendently controllable valve outputs.
* Optional 1602 LCD display.
* Optional Front panel buttons.
* Real time clock.
* Individual triac valve drivers.
* Monitoring of the total valve current.
* Watchdog relay disconnects all valves if not serviced periodically by the firmware.
* Expansion connector for future valve expanders.
* Plastic Enclosure and graphic overlay.

The hardware is primarily designed to work with [ESPHome](https://github.com/esphome/esphome) firmware.

## Disclaimer

By purchasing and/or using the hardware, you you indicate you are using it at your own risk. 

## Audience

The controller is shipped without firmware, and will require some firmware programming and electrical knowledge to successfully implement. One should have some experience modifying esphome yaml files,
reading wiring diagrams, using a Windows or Linux command line shell, using serial devices such as the FTDI serial cable, and using the esphome tool to program esphome devices. 
If you are not sure how to program firmware into an esphome device, please study the documentation on esphome.com and become familiar with it before purchasing a board. 
A link to the the programming documentation can be found [here](https://esphome.io/guides/cli.html)


## Firmware

The firmware will need to be installed on your controller before you can use it. This is because the WIFI passwords and SSID's will need to be modified so the firmware knows how to log in to your
WIFI network. 

Clone this repository to get the source code for the sprinkler controller.

The firmware consists of ESPHome platform compiled with a user-customizable YAML file and some custom components which support features not currently contained in the ESPHome release. These custom components
are discussed below.

You will need to compile and upload the software after you rename secrets-sample.yaml to secrets.yaml, and change the SSID and passwords in secrets.yaml to match your WIFI network and passwords respectively.

Once compiled the firmware is installed via a 3.3V serial cable. J201 on the board is a male header which is compatible with FTDI serial cables such as FTDI part number TTL-232R-3V3. 

### Uploading the firmware

There are 2 tact switches on the board which are only accessible with the front cover removed. One is labeled BOOT, and the other is labeled EN. To place the firmware in boot mode, connect the 24VAC transformer
to the 2 pin power connector, and the serial cable to J201 (FTDI black wire is pin 1), power up the board, and then press the EN switch and BOOT switch. While keeping the EN switch depressed, release the BOOT switch. One second after
the red LED lights, release the EN switch. The red LED should stay lit if this is done correctly.

The board is now ready to a accept firmware upload via the serial cable.

To comple the firmware, make sure you have renamed and modified secrets-sample.conf to secrets.conf, then run the following command in the build directory:

'''
esphome run esp32-
''' 

### ESPHOME yaml file 

An example YAML file is provided to aid in the implementation of the sprinkler controller. It contains some examples on how to do things with the hardware. Please refer to the file esp32-sprinkler.yaml
This file can be used as the basis for your customized yaml file. 

### Custom components

3 Custom components are located in the /custom_components directory. They are for support of the display, the PCA9554, and a modified version of the ESPHome sprinkler controller component.
Some of these components may get removed when they are integrated into ESPHome or are otherwise no longer required. No modification of these custom components should be necessary, but they must
be present when the firmware is compiled, or there will be compile errors.

### External Component

There is one external_component located in the /external_components directory. This external component controls the Valve watchdog relay.No modification of this external component
should be necessary, but it must be present when the firmware is compiled, or there will be compile errors.


## Hardware


Hardware included in the kit:

1. 1 ea. Main PCB and display
2. 1 ea. Pre-drilled enclosure and front panel overlay with 4 retaining screws.

Not supplied in the kit:

1. CR927 battery for the real time clock.

2. 3.3V serial adapter for flashing firmware onto the board and connecting wires.

3. 24V 40VA transformer


### Power Connector

The 2 pin power connector J402 accepts 22-28VAC power at 60Hz from a 40VA wall transformer with an internal fuse (IMPORTANT!). A suitable transformer can be found [here](https://www.amazon.com/Transformer-Auto-resetting-Compatible-Doorbell%EF%BC%8CNest-Thermostat/dp/B085WPNC29)


### Valve Connector

J401 is the valve connector. It has the following pinout:

### Table 1. Valve Connector

|PIN| Signal|
|----| ----------------|
| 1  | Valve 0|
| 2  | Valve 1|
| 3  | Valve 2|
| 4  | Valve 3|
| 5  | Valve 4|
| 6  | Valve 5|
| 7  | Valve 6|
| 8  | Valve 7|
| 9  | Valve 8|
| 10 | Valve Common|
| 11 | Valve Common|
| 12 | Valve Common|


Note: The valves used must not draw more than 0.4 amps each. Do not put more then 1 valve on a valve driver.


### Serial Connector


The Serial connector J301 is pinned out to accept an FTDI cable. It is a 1x6 2.54mm pitch header located to the right of the ESP32 board. The serial connector is used to upload firmware to the Sprinkler controller should the OTA programming fail.  The pinout of this connector is:


#### Table 2. FTDI Connector

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

#### Table 3. Expansion Connector

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


### Real Time Clock Jumper and Battery

J302 on the board can be in one of 2 positions. In position 1-2, the battery is connected to the DS1307 clock. In position 2-3 The DS1307 battery input is grounded. The board is shipped with the jumper in positions 2-3. 
To fully utilize the DS1307, a CR927 battery (not-supplied) must be inserted, and the the jumper must be moved to positions 1-2. If the real time clock battery back feature isn't going to be used, the jumper should remain
in positions 2-3. 

Note: If the jumper is removed or missing, the battery input to the DS1307 will be left floating, and the DS1307 may not be able to be properly accessed via the software.


### I2C Bus


9 Triacs are used to switch the solenoid valves. 8 of these triac drivers  valves 1 through 9 are controlled by a single PCA9554 at I2C address 0x38 (Valve 0 output is directly connected to GPIO19). The PCA9554 is attached to I2C bus A. GPIO22 is the SCL signal, and GPIO21 is the SDA signal. The DS1307 is attached to the I2C bus, and is at address 0x68. The I2C bus also goes to the expansion connector for future valve expansion.

#### Table 4. I2C Addresses

|Device Address|Device|
|--------------|------------------------------|
|0x38          | PCA9554 IO Expander          |
|0x68          | DS1307 Real Time Clock       |

#### Table 5. PCA9554 I2C Address Solder Jumpers
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

The display used is a widely available 3.3V 1602 type. It is interfaced to the ESP32 in four bit parallel mode. R310 on the board adjusts the LCD display contrast.

#### Table 6. Display Signals
|GPIO|Display Signal Name|
|------|-----------------------|
|GPIO17| RS                    |
|GPIO18| E                     |
|GPIO23| DB4                   |
|GPIO25| DB5                   |
|GPIO26| DB6                   |
|GPIO27| DB7                   |
|GPIO13| LCD Backlight         |


### Buttons

The 3 momentary buttons are connected directly to the ESP32. With associated definintions in the .yaml file, they provide a way to manually initiate operations in case the homeassistant server goes off line.

#### Table 7. Button Inputs
|GPIO| Button Location|
|------|-------------------------|
|GPIO32| Button 1 (Top)          |
|GPIO33| Button 2 (Middle)       |
|GPIO34| Button 3 (Bottom)       |
|GPIO0 | Boot (Internal Only)    |

### Watchdog Relay

The watchdog relay will disconnect all the valves if no output toggling is detected on GPIO16. There is an external component called valve_dog.h which toggles GPIO16 each time the loop function is called.
If this output stops toggling, the valves will be disconnected from the 24VAC power source. According to the ESPHome docs, the setup method in valve_dog.h is called at approximately a 60Hz rate. There is a charge pump on the board connected to a MOSFET which drives the watchdog relay. If the input to the charge pump stops toggling, then the relay opens.

In the .yaml code example and in valve_dog.h the state of the irrigation controller is monitored. If it isn't active, then no toggling will appear on the output of GPIO16, and the relay contacts will be open within 2-6 seconds. Once the irrigation controller becomes active, toggling will appear on GPIO16 and a short time later, the relay will close. This will ususally happen within 2 seconds, so that should be factored into the sprinkler controller start delay time.


### Fault LED

The fault LED is controlled by GPIO14. Setting it high turns the fault LED on.

### Current Sensor

The current sensor connects to GPIO36. It has a sensitivity of 2.02 volts per amp. To get amps RMS, the following formula should be used: Arms = (x/2.02)*0.707
Please note that the ESP32 ADC is not very linear bottom end of its range. The current measurement value should be clipped at the bottom end by using the following code:

```
         if (x < 0.08)
            return 0.0;
          else
            return x;
```

### Valve Drivers

There are 9 valve drivers on the board. Valve zero is controlled by GPIO19 directly from the ESP32 chip. The other valves are accessed over I2C using the PCA9554 I2C expander. 

For the valves controlled over I2C, the following table shows how the bit number (0-7) map to a specific valve:

#### Table 8. I2C Bit to Valve mapping

|BIT| Valve Number|
|---| ------------|
| 0 | Valve 1|
| 1 | Valve 2|
| 2 | Valve 3|
| 3 | Valve 4|
| 4 | Valve 5|
| 5 | Valve 6|
| 6 | Valve 7|
| 7 | Valve 8|






 


