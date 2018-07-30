#include <stdio.h>
#include "driver/gpio.h"
#include <string.h>
#include "wifi_connection.h"
#include "request.h"
#include "storage.h"

#include "config.h"
#include "esp_system.h"
#include "message.h"

char* get_mac_address(char* str) {
	uint8_t baseMac[6];
	// Get MAC address for WiFi station
	esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
	sprintf(str, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]);
	return str;
}

void transmission_config(){
  gpio_pad_select_gpio(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
  setup_connection();
  while(connect());

  check_id();
}

void send_message(int state){
  gpio_set_level(BLINK_GPIO, state);
  while(!is_connected()){
    connect();
  }
  send_readings(state);
}
