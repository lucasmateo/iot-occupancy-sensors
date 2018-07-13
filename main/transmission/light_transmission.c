#include <stdio.h>
#include "driver/gpio.h"
#include <string.h>
#include "../wifi_connection/wifi_connection.h"
#include "../http/request.h"

#define BLINK_GPIO 2

void transmission_config(){
  gpio_pad_select_gpio(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
  setup_connection();
  while(connect());
}


void send_message(int state){
  while(!is_connected()){
    connect();
  }
  get_request();
}
