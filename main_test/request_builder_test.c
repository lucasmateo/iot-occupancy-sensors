#include "request_builder.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "config.h"

void build_GET_test(){
	char *REQUEST = "GET " "/test" " HTTP/1.0\r\n"
	    "Host: ""www.google.com""\r\n"
	    "User-Agent: esp-idf/1.0 esp32\r\n"
	    "\r\n";

	char request[512];

	build_request(request, "GET", "/test", "www.google.com", "");

	TEST_ASSERT_EQUAL_STRING(REQUEST,request);

}

void build_POST_test(){
	char *REQUEST = "POST " "/test" " HTTP/1.0\r\n"
	    "Host: ""www.google.com""\r\n"
	    "User-Agent: esp-idf/1.0 esp32\r\n"
		"Content-Length: 8"
		"\r\n"
	    "\r\n"
		"teststst";

	char request[512];

	build_request(request, "POST", "/test", "www.google.com", "teststst");

	TEST_ASSERT_EQUAL_STRING(REQUEST,request);


}
