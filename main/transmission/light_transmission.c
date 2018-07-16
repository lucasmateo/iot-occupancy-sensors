#include <stdio.h>
#include "driver/gpio.h"
#include <string.h>
#include "../wifi_connection/wifi_connection.h"
#include "../http/request.h"



void transmission_config(){
  setup_connection();
  while(connect());
}


void send_message(int state){
  while(!is_connected()){
    connect();
  }

  post_request(state?"true":"false");
}
