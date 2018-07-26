#include "transmission.h"
#include "unity.h"
#include "wifi_connection.h"
#include "storage.h"

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
