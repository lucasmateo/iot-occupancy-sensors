#include <stdio.h>
#include "driver/gpio.h"
#include <string.h>
#include "wifi_connection.h"
#include "request.h"

#include "config.h"
#include "esp_system.h"

char* get_mac_address(char* str) {
	uint8_t baseMac[6];
	// Get MAC address for WiFi station
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	sprintf(str, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
	return str;
}

void transmission_config(){
  char* str = (char*)malloc(sizeof(char) *18);
  get_mac_address(str);
  printf(str);
  free(str);

  setup_connection();
  while(connect());

  get_request(GET_PATH);
}


void send_message(int state){
  while(!is_connected()){
    connect();
  }
  post_request(POST_PATH,state?"true":"false");
}
