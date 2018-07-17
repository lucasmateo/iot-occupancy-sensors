#include <stdio.h>
#include "driver/gpio.h"
#include <string.h>
#include "../wifi_connection/wifi_connection.h"
#include "../http/request.h"

#include "../config.h"



void transmission_config(){
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
