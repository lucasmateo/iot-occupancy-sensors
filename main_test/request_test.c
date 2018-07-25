#include "unity.h"
#include "http_answer.h"
#include "config.h"
#include "request.h"
#include "wifi_connection.h"

void send_GET_request_test(){
	while(!is_connected()){
		connect();
	}
	http_answer* ans = get_request(GET_PATH,WEB_SERVER);

	TEST_ASSERT_EQUAL(1,ans->success);

	free_http_answer(ans);
	wifi_stop();
}

void send_POST_request_test(){
	while(!is_connected()){
		connect();
	}
	http_answer* ans = post_request(POST_PATH,WEB_SERVER,"");

	TEST_ASSERT_EQUAL(1,ans->success);

	free_http_answer(ans);
	wifi_stop();
}


