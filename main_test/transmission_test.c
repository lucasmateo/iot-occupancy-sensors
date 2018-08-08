#include "transmission.h"
#include "unity.h"
#include "wifi_connection.h"
#include "storage.h"
#include "message.h"

void config_test(void){
  erase_all();

  transmission_config();

  TEST_ASSERT_EQUAL(1,is_connected());

  int status = 0;
  get_id(&status);
  TEST_ASSERT_EQUAL(STORAGE_OK,status);

  erase_all();
  wifi_stop();
}

void storing_test(){
  transmission_config();
  erase_all();
  int status = 0;
  status = set_max_data(3);

  switch_mode(STORE);

  send_readings(0);

  int data_length = get_actual_data(&status);

  TEST_ASSERT_EQUAL(1,data_length);

  send_readings(0);

  data_length = get_actual_data(&status);

  TEST_ASSERT_EQUAL(2,data_length);

  send_readings(0);

  data_length = get_actual_data(&status);

  TEST_ASSERT_EQUAL(0,data_length);

  switch_mode(SEND);

  erase_all();
  wifi_stop();

}
