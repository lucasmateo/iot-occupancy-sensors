

#include "sensor/sensor.h"
#include "transmission/transmission.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"



void main_task(void* param){
  while (1) {
    send_message(sensor_mesure());
    vTaskDelay(1000 / portTICK_PERIOD_MS);

  }
}

void app_main(){
  sensor_config();
  transmission_config();

  xTaskCreate(&main_task, "main_task", 10000, NULL, 5, NULL);
}
