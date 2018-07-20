

#include "sensor.h"
#include "transmission.h"
#include "sleep.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "config.h"



void main_task(void* param){
  while (1) {
    send_message(sensor_mesure());
    enter_sleep(MESURE_FREQUENCY);

  }
}

void app_main(){
  sensor_config();
  transmission_config();

  xTaskCreate(&main_task, "main_task", 20000, NULL, 5, NULL);
}
