#include "transmission.h"
#include "unity.h"
#include "wifi_connection.h"
#include "storage.h"
#include "message.h"

void config_test(void){
  erase_all();

  transmission_config();

  int status = 0;
  get_id(&status);
  TEST_ASSERT_EQUAL(STORAGE_OK,status);

  erase_all();
}

void check_id_test(){
  erase_all();

  transmission_config();

  int status = 0;
  status = set_id("test");
  TEST_ASSERT_EQUAL(STORAGE_OK,status);
  check_id();
  char* id = get_id(&status);
  TEST_ASSERT_EQUAL(STORAGE_OK,status);
  TEST_ASSERT_EQUAL_STRING("test",id);

  erase_all();
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
