#include "unity.h"
#include "http_answer.h"
#include "config.h"
#include "request.h"
#include "wifi_connection.h"

void send_GET_request_test(){
	while(!is_connected()){
		connect();
	}
	http_answer* ans = request_id(WEB_SERVER);

	TEST_ASSERT_EQUAL(1,ans->success);

	free_http_answer(ans);
	wifi_stop();
}

void send_POST_request_test(){
	while(!is_connected()){
		connect();
	}
	http_answer* ans = send_data(WEB_SERVER,0);

	TEST_ASSERT_EQUAL(1,ans->success);

	free_http_answer(ans);
	wifi_stop();
}
