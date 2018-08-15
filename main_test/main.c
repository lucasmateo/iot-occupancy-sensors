#include "unity.h"
#include "test.h"
#include "storage.h"

int app_main(void)
{
  UNITY_BEGIN();
	RUN_TEST(test_init_struct);
	RUN_TEST(test_http_parse);
	RUN_TEST(test_http_parse_nocontent);
	RUN_TEST(setup_connection_test);
	RUN_TEST(connection_test);
	RUN_TEST(storage_test);
	RUN_TEST(storage_writing_test);
	RUN_TEST(build_GET_test);
	RUN_TEST(build_POST_test);
  RUN_TEST(test_http_parse_withid);
  RUN_TEST(id_request_test);
  RUN_TEST(sensor_msg_test);
  RUN_TEST(config_test);
	RUN_TEST(send_GET_request_test);
	RUN_TEST(send_POST_request_test);
  RUN_TEST(test_print_command);
  RUN_TEST(test_no_command);
  RUN_TEST(command_list_test);
  RUN_TEST(wrong_command_list_test);
  RUN_TEST(storage_writing_int_test);
  RUN_TEST(storage_writing_max_data_val_test);
  RUN_TEST(storage_writing_actual_data_val_test);
  RUN_TEST(storage_incr_actual_data_val_test);
  RUN_TEST(storage_data_test);
  RUN_TEST(storage_full_test);
  RUN_TEST(value_array_test);
  RUN_TEST(storing_test);
  RUN_TEST(check_id_test);
  erase_all();
  return UNITY_END();
}
