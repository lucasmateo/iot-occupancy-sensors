#include <stdio.h>
#include "driver/gpio.h"
#include <string.h>
#include "wifi_connection.h"
#include "request.h"
#include "storage.h"

#include "config.h"
#include "message.h"

void transmission_config(){
  gpio_pad_select_gpio(BLINK_GPIO);
  gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

  check_id();
}

void send_message(int state){
  gpio_set_level(BLINK_GPIO, state);

  send_readings(state);
}
