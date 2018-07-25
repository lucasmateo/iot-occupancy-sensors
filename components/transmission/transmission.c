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

int process_answer(http_answer* ans){
	print_http_answer(ans);

	free_http_answer(ans);

	return 1;
}

void transmission_config(){
  setup_connection();
  while(connect());

  process_answer(get_request(GET_PATH,WEB_SERVER));


}


void send_message(int state){
  while(!is_connected()){
    connect();
  }
  process_answer(post_request(POST_PATH,WEB_SERVER,state?"true":"false"));
}


