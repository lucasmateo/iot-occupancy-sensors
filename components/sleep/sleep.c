#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>
#include <sys/time.h>
#include "esp_sleep.h"

#include "config.h"


void enter_sleep(int time){

	esp_sleep_enable_timer_wakeup(time * 1000);
	//esp_deep_sleep_start();
    vTaskDelay(MESURE_FREQUENCY/portTICK_PERIOD_MS);
}
