#include "unity.h"
#include "test.h"


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
	RUN_TEST(send_GET_request_test);
	RUN_TEST(send_POST_request_test);
    return UNITY_END();
}
