## WORKSPACE SENSOR

The goal of this project is to gather data about the use of desks in the office. A device is placed under each desk allowing to determine if it is used or not. Once that is done the information is sent to a remote server that will analyse the data and display them. The reading are performed at a regular frequency


In the main folder you will find the code uploaded to the esp 32 chip

### Build

to setup your environment follow the instruction in this link :
<https://dl.espressif.com/doc/esp-idf/latest/get-started/index.html>

once you have completed the setup sue this command :
``` bash
make menuconfig
```
and change the value Serial flasher config > Default serial port to the value of the USB port connected to the board

once it is done you can build and flash the software to the chip the make flash or build command

You can also find some constant that you might wanna change in the ./main/config.h file

### Project Structure

The structure is according to the esp-idf structure : <https://esp-idf.readthedocs.io/en/latest/api-guides/build-system.html>

An additional folder is added that contain code that is not specific to the hardware. You can find for
exemple http request parsing. In component folder you will find code relative to the wifi connection for instance.

They were separated to ease the process of testing as both use different framework. The code in the
component can only be tested on the esp 32 chip whereas the code in the C folder can be tested on any
computer.  


### available command
"sleep_default" reset the sleep time to its default value
"sleep_3000" set the sleep time to 3000 ms
"nosleep" the device will only wait without any particular setting during the wait time
"modemsleep" after the measurment the device will go into modem sleep meaning it will consume less but won't lose the wifi connection
"deepsleep" after each measurment the device will go into deep sleep. This is similar to a shutdown.
