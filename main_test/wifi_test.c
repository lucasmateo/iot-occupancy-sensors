#include "wifi_connection.h"
#include "unity.h"

void setup_connection_test(){
	setup_connection();
	TEST_ASSERT_EQUAL(0,is_connected());

}

void connection_test(){
	setup_connection();
	TEST_ASSERT_EQUAL(0,is_connected());
	wifi_connect();
	TEST_ASSERT_EQUAL(1,is_connected());
	wifi_stop();
	TEST_ASSERT_EQUAL(0,is_connected());
}
