## WORKSPACE SENSOR

The goal of this project is to gather data about the use of desks in the office. A device is placed under each desk allowing to determine if it is used or not. Once that is done the information is sent to a remote server that will analyse the data and display them. The reading are performed at a regular frequency


### How the device work

The goal of the device is to give regular update to the server. I will explain the basic lifecycle of this program for the esp32.

When it starts, the device need to be identified by the server. So if it has no id, it will send a request to the server for one. The id is then saved in memory, so if it reboot, it won't ask again.   

Once it has an id it will start sending data. For that it will use the sensor to determine if the desk is occupied or not. Once the data is acquired it sends it to the server and goes to sleep, when it wakes up it will through the same cycle again.  

When the data are sent, the server can answer with some commands in order to configure the device. For example, it can change the sleep time or how does the device sleep.  

Those are important settings to optimize the power consumption according to your needs.  

You can also change how the data are sent to the server. Instead of sending them after each readings, the device can also store them and send them once the memory is full allowing for less power consumption as the wifi will be up for less time.

### wifi

The wifi protocol is wpa. So you can only connect to the ibm guest wifi. the connection to the wifi is required for the tests to pass

#### wpa2

In order to connect to the ibm wifi you will need some certificate.
to get them go to <https://w3.ibm.com/help/#/article/install_digicert/install_overview>  
From this link you should
be able to get two document one named "ca.pem" and another one finishing with ".p12". From the p12 file you need to get
two files using the openssl tool and the following command :

```bash
openssl pkcs12 -in filename.p12 -clcerts -nokeys -out filename.crt
```

```bash
openssl pkcs12 -nodes -in yourP12File.p12 -nocerts -out privateKey.key
```


Both the wifi protocol are implemented. To change wich one is used change the wifi_build.h file and build the application again. Once you have the files you can put them in the components/wifi_connection folder and specify their name in the components/wifi_connect/component.mk file 

The file are not present on the github as it is public 

### Build

to setup your environment follow the instruction in this link :
<https://dl.espressif.com/doc/esp-idf/latest/get-started/index.html>

once you have completed the setup use this command :
``` bash
make menuconfig
```
and change the value Serial flasher config > Default serial port to the value of the USB port connected to the board

You have to make sure that the driver are properly installed. Usually on linux distribution the drivers are already installed but not on macOS or windows. 

once it is done you can build and flash the software to the chip the make flash or build command

some building script are provided :

1. flash.sh build and flash the app to the esp32 and will display the logs once the device is running
2. clean.sh clean the project builds and erase esp32 non-volatile memory
3. test.sh build and upload the testing app and will display the logs once the device is running


You can also find some constant that you might wanna change in the ./configuration/include/config.h file

Before launching the device try and make the test.sh script run. It upload a test application to the device
if all the test are ok, the device is working and you launch the application with the launch.sh script

sometime the wifi connection can timeout and fail one test, try and lauch the tst multiple times. If other test are failing you will have to fix them.

### Project Structure

The structure is according to the esp-idf structure : <https://esp-idf.readthedocs.io/en/latest/api-guides/build-system.html>

An additional folder is added that contain code that is not hardware specific. You can find for
exemple http request parsing. In component folder you will find code relative to the wifi connection for instance. So if the device is changed only the code in the component folder should be modified. The driver are the driver provided by esp-idf.

They were separated to ease the process of testing as both use different framework. The code in the
component can only be tested on the esp 32 chip whereas the code in the C folder can be tested on any
computer in theory.  

The build is handled by the makefile provided by esp-idf so we have to use a specific structure. Our code must be separated into components that is found into components folder.

For the main there is multiple components folder : C, components, configuration, and main plus the the components folder provided by the esp-idf sdk. The configuration file is in another folder so it can easily be excluded.  

A component folder contain a file named "component.mk", some code, and a folder named "include" containing header files. The component.mk file is need if you want the code in this folder to be compiled.  

There is two conditions for a folder to be compiled: to be in a components folder and to contain a file named "component.mk".


### Test

In order to test the code and the device, there is an other application using Unity test framework. It can be uploaded to the device using the script test.sh. Some of the test try to reach the server. If you want them to pass the server will need to be up. It also will try to connect to the wifi.
The config.h file is different for main and test application. The test config file can be found in main_test/include/

### communication protocols

The device is communicating to the server via http protocols

To get the id it will send a GET request to the server to the specified path(set in the config.h file).
It expects an answer of this type :

```json
{"status":"OK","id":"theid"}
```

To send the data it is using POST request with this type of body :

```json
{"id":"theid","val":0}
```

and expect a response containing or not commands :
```json
["nosleep","sleep_3000"]
```

For a more specific specification refer to the API server documentation

### available command
+ `sleep_default` reset the sleep time to its default value  

+ `sleep_3000` set the sleep time to 3000 ms  

+ `nosleep` the device will only wait without any particular setting during the wait time  

+ `modemsleep` after the measure the device will go into modem sleep meaning it will consume less but won't lose the wifi connection  

+ `deepsleep` after each measure the device will go into deep sleep. This is similar to a shutdown.  

+ `switch_send` will put the device in send mode, meaning that no data will be stored  


+ `switch_store` will put the device in store mode, data will saved into memory until the memory is full.  

+ `max_data64`,`max_data128`,`max_data512` will respectively set the max stored data to 64, 128, 512. Those values will only be used in the store mode. If it is set to 64, the data will be sent once 64 readings are done.  

### External Library

The cJSON library is used to format the JSON string used for the communication with the server
<https://github.com/DaveGamble/cJSON>

The hashmap library used is <https://github.com/petewarden/c_hashmap>

All opertion related to build or flash is handled by the esp-idf sdk <https://github.com/espressif/esp-idf>
