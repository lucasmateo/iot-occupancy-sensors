
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "wifi_connection.h"

#include "config.h"

#include "wifi_build.h"

#if WIFI_BUILD_TYPE==WPA_BUILD


#define TIMEOUT MS_TIMEOUT/portTICK_PERIOD_MS

static EventGroupHandle_t wifi_event_group;
static const char *TAG = "simple wifi";

//determine if the wifi is connected or not
const int WIFI_CONNECTED_BIT = BIT0;

int is_setup = 0;
int event_loopinit = 0;
int wifi_mode = WIFI_NORMAL;


static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        ESP_LOGI(TAG, "got ip:%s",
                 ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        xEventGroupClearBits(wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void setup_connection(){
	if(is_setup){
		return;
	}
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
	  ESP_ERROR_CHECK(nvs_flash_erase());
	  ret = nvs_flash_init();
	}

	tcpip_adapter_init();

	wifi_event_group = xEventGroupCreate();
  if(!event_loopinit){
	   ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL) );
     event_loopinit = 1;
  }
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	wifi_config_t wifi_config = {
	  .sta = {
		  .ssid = SSID,
		  .password = PASS
	  },
	};
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
	ESP_ERROR_CHECK(esp_wifi_start());

	is_setup = 1;

}

int wifi_connect(){
  if(!is_setup){
    setup_connection();
  }
	ESP_ERROR_CHECK(esp_wifi_connect());
  //waiting for the connection
  EventBits_t uxBits = xEventGroupWaitBits(
            wifi_event_group,
            WIFI_CONNECTED_BIT,
            pdFALSE,
            pdFALSE,
            TIMEOUT );

  if((uxBits & WIFI_CONNECTED_BIT )== 0){
    ESP_LOGI(TAG, "wifi_init_sta timeout.");
    wifi_stop();
    return 1;
  }

  ESP_LOGI(TAG, "wifi_init_sta finished.");

  return 0;
}

int is_connected(){
  if(wifi_event_group){
	ESP_LOGI(TAG, "status %d",xEventGroupGetBits(wifi_event_group));
    return xEventGroupGetBits(wifi_event_group);
  }
  return 0;
}

void wifi_stop(){
  if(WIFI_NORMAL){
  	esp_wifi_stop();
    is_setup = 0;
  }
}

void modem_sleep(){
  wifi_mode = WIFI_ALWAYSUP;
  esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
}

#endif
