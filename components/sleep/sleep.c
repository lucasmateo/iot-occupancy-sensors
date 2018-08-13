#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>
#include <sys/time.h>
#include "esp_sleep.h"
#include "storage.h"
#include "config.h"
#include "esp_wifi.h"
#include "sleep.h"
#include "wifi_connection.h"


int mode = NO_SLEEP;

void enter_sleep(){
	int status = 0;
	int sleep_time = get_sleep_time(&status);

	if(status == STORAGE_NOT_SET || status == STORAGE_ERROR){
		sleep_time = MESURE_FREQUENCY;
		set_sleep_time(MESURE_FREQUENCY);
	}

	switch (mode) {
		case MODEM_SLEEP:
			esp_sleep_enable_timer_wakeup(sleep_time * 1000);
			modem_sleep();
			vTaskDelay(sleep_time/portTICK_PERIOD_MS);
			break;
		case NO_SLEEP:
			vTaskDelay(sleep_time/portTICK_PERIOD_MS);
			break;
		case DEEP_SLEEP:
			esp_sleep_enable_timer_wakeup(sleep_time * 1000);
			esp_deep_sleep_start();
			break;
	}
}

void switch_sleepmode(int mode_switch){
	mode = mode_switch;
}
