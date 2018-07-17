

#include <driver/adc.h>
#include "esp_adc_cal.h"

#include "config.h"

static const adc_atten_t atten = ADC_ATTEN_DB_11;


void sensor_config(){
  gpio_pad_select_gpio(ON_GPIO);
  gpio_set_direction(ON_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_level(ON_GPIO, 1);

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(READ, atten);
}


int sensor_mesure(){
  int val = adc1_get_raw(READ);

  if(val > THRESHOLD){
    return 1;
  }
  return 0;

}
