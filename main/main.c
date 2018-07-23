
#include "freertos/FreeRTOS.h"

#include "sensor.h"
#include "transmission.h"
#include "sleep.h"


#include "sdkconfig.h"

#include "config.h"



void main_task(void){
  while (1) {
	int start = xPortGetFreeHeapSize();
    send_message(sensor_mesure());

    enter_sleep(MESURE_FREQUENCY);
    printf("memory used : %d\n",xPortGetFreeHeapSize() - start );

  }
}

void app_main(){
  sensor_config();
  transmission_config();

  main_task();
}
