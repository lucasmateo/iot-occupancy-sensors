
#include "freertos/FreeRTOS.h"

#include "sensor.h"
#include "transmission.h"
#include "sleep.h"
#include "storage.h"
#include "nvs_flash.h"
#include "esp_log.h"


#include "sdkconfig.h"

#include "config.h"



void main_task(void){
  while (1) {

	int start = xPortGetFreeHeapSize();
    send_message(sensor_mesure());

    enter_sleep(MESURE_FREQUENCY);
    ESP_LOGI("memory","memory used : %d\n",xPortGetFreeHeapSize() - start );

  }
}

void app_main(){
  sensor_config();
  transmission_config();
  main_task();
}
