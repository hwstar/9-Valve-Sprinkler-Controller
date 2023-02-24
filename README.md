# 9 Valve Sprinkler controller

![alt text](https://github.com/hwstar/9-Valve-Sprinkler-Controller/blob/main/assets/proto-pic.png)

This is the code and documentation repository for a 9 valve sprinkler
controller based on an ESP32. It has the following features:

* ESP32 Microcontroller
* Uses a 40VA 24VAC wall transformer with an internal fuse.
* Operates the 24 Volt AC sprinkler valves commonly used for irrigation.
* 9 Indpendently controllable valve outputs.
* 1602 LCD display.
* 3 Front panel buttons.
* Real time clock.
* Individual triac valve drivers rated for 0.4A.
* Monitoring of the total valve current.
* Watchdog relay disconnects all valves if not serviced periodically by the firmware.
* Expansion connector for future valve expanders.
* Plastic Enclosure and graphic overlay.



The hardware is primarily designed to work with [ESPHome](https://github.com/esphome/esphome) firmware version 2023.2.1 or later.

## Disclaimer

By purchasing and/or using the hardware, you you indicate you are using it at your own risk. 

## Audience

The controller is shipped without firmware which can connect to your WIFI network. It will require some firmware programming and electrical knowledge to successfully implement. 
One should have some experience modifying esphome yaml files, reading wiring diagrams, using a Windows or Linux command line shell, using serial devices such as the FTDI serial cable,
and using the esphome tool to program esphome devices. If you are not sure how to program firmware into an esphome device, please study the documentation on esphome.com and become
familiar with it before purchasing a board. A link to the the programming documentation can be found [here](https://esphome.io/guides/cli.html)


## Firmware

The firmware will need to be installed on your controller before you can use it. This is because the WIFI passwords and SSID's will need to be modified so the firmware knows how to log in to your
WIFI network. 

Clone this repository to get the source code for the sprinkler controller.

The firmware consists of ESPHome platform compiled with a user-customizable YAML file and some custom components which support features not currently contained in the ESPHome release. These custom components
are discussed below.

You will need to compile and upload the software after you rename secrets-sample.yaml to secrets.yaml, and change the SSID and passwords in secrets.yaml to match your WIFI network and passwords respectively.

Once compiled the firmware is installed via a 3.3V serial cable. J201 on the board is a male header which is compatible with FTDI serial cables such as FTDI part number TTL-232R-3V3. 

For firmware upload instructions please refer to the (wiki)[https://github.com/hwstar/9-Valve-Sprinkler-Controller/wiki]


### ESPHOME yaml file 

An example YAML file is provided to aid in the implementation of the sprinkler controller. It contains some examples on how to do things with the hardware. Please refer to the file esp32-sprinkler.yaml
This file can be used as the basis for your customized yaml file. 

### Custom components

2 Custom components are located in the /custom_components directory. They are for support of the display, and a modified version of the ESPHome sprinkler controller component.
Some of these components may get removed when they are integrated into ESPHome or are otherwise no longer required. No modification of these custom components should be necessary, but they must
be present when the firmware is compiled, or there will be compile errors.

### External Component

There is one external_component located in the /external_components directory. This external component controls the Valve watchdog relay.No modification of this external component
should be necessary, but it must be present when the firmware is compiled, or there will be compile errors.


## Hardware

The hardware can be purchased from me directly.

Hardware included in the kit:

1. 1 ea. Main PCB and display
2. 1 ea. Pre-drilled enclosure and front panel overlay with 4 retaining screws.
3. 1 ea. 2 pin screw terminal pluggable power connector.
4. 1 ea. 12 pin screw terminal pluggable power connector.

Not supplied in the kit:

1. CR927 battery for the real time clock.
2. 3.3V serial adapter for flashing firmware onto the board and connecting cable.
3. 24V 40VA transformer
4. Wire


### Connectors Pinouts and GPIO's

Please refer to the (wiki)[https://github.com/hwstar/9-Valve-Sprinkler-Controller/wiki] for this reference information.


### Power, Valve, and Serial Connectors

The picture below shows the location of the power, valve and serial connectors.

![alt text](https://github.com/hwstar/9-Valve-Sprinkler-Controller/blob/main/assets/scm9-power-valves-serial.png)

The 2 pin power connector J402 accepts 22-28VAC power at 60Hz from a 40VA wall transformer with an internal fuse (IMPORTANT!). A suitable transformer can be found [here](https://www.amazon.com/Transformer-Auto-resetting-Compatible-Doorbell%EF%BC%8CNest-Thermostat/dp/B085WPNC29)

Note: The valves used must not draw more than 0.4 amps each. Do not put more then 1 valve on a valve output pin.

The Serial connector J301 is pinned out to accept an FTDI cable. It is a 1x6 2.54mm pitch header located to the right of the ESP32 module. The serial connector is used to initially upload firmware to the Sprinkler controller 


### Expansion Connector

The expansion connector J201 is an 8 pin 3mm pitch Molex micro fit connector (43025 series). It will allow for future expansion of the sprinkler controller to add additional zones.


### Real Time Clock Jumper and Battery

J302 on the board can be in one of 2 positions. In position 1-2, the battery is connected to the DS1307 clock. In position 2-3 The DS1307 battery input is grounded. The board is shipped with the jumper in positions 2-3. 
To fully utilize the DS1307, a CR927 battery (not-supplied) must be inserted, and the the jumper must be moved to positions 1-2. If the real time clock battery back feature isn't going to be used, the jumper should remain
in positions 2-3. 

Note: If the jumper is removed or missing, the battery input to the DS1307 will be left floating, and the DS1307 may not be able to be properly accessed via the software.


### Display

The display used is a widely available 3.3V 1602 type. It is interfaced to the ESP32 in four bit parallel mode. R310 on the board adjusts the LCD display contrast.

### Buttons

The 3 momentary buttons are connected directly to the ESP32. With associated definintions in the .yaml file, they provide a way to manually initiate operations in case the homeassistant server goes off line.

### Watchdog Relay

The watchdog relay will disconnect all the valves if no output toggling is detected on GPIO16. There is an external component called valve_dog.h which toggles GPIO16 each time the loop function is called.
If this output stops toggling, the valves will be disconnected from the 24VAC power source. According to the ESPHome docs, the loop() method in valve_dog.h is called at approximately a 60Hz rate. There is a charge pump on the board connected to a MOSFET which drives the watchdog relay. If the input to the charge pump stops toggling, then the relay opens.

In the .yaml code example and in valve_dog.h the state of the irrigation controller is monitored. If it isn't active, then no toggling will appear on the output of GPIO16, and the relay contacts will be open within 2-6 seconds. Once the irrigation controller becomes active, toggling will appear on GPIO16 and a short time later, the relay will close. This will ususally happen within 2 seconds, so that should be factored into the sprinkler controller start delay time.

Note: The watchog relay should never be used to interrupt power to the valves in normal circumstances. Use the the individual valve triacs instead. 

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







 


