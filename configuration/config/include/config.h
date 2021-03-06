#define MS_TIMEOUT 15000 //maximum time in ms to connect to the wifi
#define SSID      "IBMInternet"	//wifi ssid
#define PASS      "" //ssid password

#define WEB_SERVER "IOT-api-occupancy.eu-gb.mybluemix.net" //server of the request
#define WEB_PORT "80" //port of the server

#define GET_PATH "/device/id" //path for the first GET request
#define POST_PATH "/device/measure" //path for the first POST request

#define BLINK_GPIO 2 //pin that will be set to high when to sensor is detecting something

#define THRESHOLD 1000 //above this value the reading will be considered as high
#define ON_GPIO 17 //output that will power the sensor
#define READ 4 //input that will read the sensor output

#define MESURE_FREQUENCY 1000 //delay between each mesure

#define MAX_STORAGE 128
