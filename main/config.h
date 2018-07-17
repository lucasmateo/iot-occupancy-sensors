#define MS_TIMEOUT 5000 //maximum time in ms to connect to the wifi
#define SSID      "IBMInternet"	//wifi ssid
#define PASS      "" //ssid password

#define WEB_SERVER "9.233.64.30" //server of the request
#define WEB_PORT "9000" //port of the server

#define GET_PATH "/" //path for the first GET request
#define POST_PATH "/" //path for the first POST request

#define BLINK_GPIO 2 //pin that will be set to high when to sensor is detecting smth

#define THRESHOLD 1000 //above this value the reading will be considered as high
#define ON_GPIO 17 //output that will power the sensor
#define READ 0 //input that will read the sensor output

#define MESURE_FREQUENCY 5000 //delay between each mesure
