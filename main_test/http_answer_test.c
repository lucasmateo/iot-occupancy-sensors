#include "http_answer.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "unity.h"


void test_init_struct(void)
{
	http_answer* ans = init_http_answer();
    TEST_ASSERT_EQUAL(0,ans->success);
    TEST_ASSERT_EQUAL('\0',*(ans->answer));

    free_http_answer(ans);
}

void test_http_parse(void){
	http_answer* ans;

	char* req = "HTTP/1.1 200 OK \r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: 59\r\n"
			"Accept-Language: en-us\r\n"
			"Accept-Encoding: gzip, deflate\r\n"
			"Connection: Keep-Alive\r\n\r\n"
			"licenseID=string&content=string&/paramsXML=string";

	ans = parse_http_answer(req);
	TEST_ASSERT_EQUAL(1,ans->success);
	TEST_ASSERT_EQUAL_STRING(ans->answer,"licenseID=string&content=string&/paramsXML=string");
	free_http_answer(ans);
}

void test_http_parse_nocontent(void){
	http_answer* ans;

	char* req = "HTTP/1.1 200 OK \r\n"
			"User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
			"Host: www.tutorialspoint.com\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Accept-Language: en-us\r\n"
			"Accept-Encoding: gzip, deflate\r\n"
			"Connection: Keep-Alive\r\n\r\n"
			"licenseID=string&content=string&/paramsXML=string";

	ans = parse_http_answer(req);
	TEST_ASSERT_EQUAL(1,ans->success);
	TEST_ASSERT_EQUAL(*(ans->answer),0);
	free_http_answer(ans);
}

void test_http_parse_withid(void){
	http_answer* ans;

	char* req = "HTTP/1.1 200 OK \r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: 59\r\n"
			"Accept-Language: en-us\r\n"
			"Accept-Encoding: gzip, deflate\r\n"
			"Connection: Keep-Alive\r\n\r\n"
			"{\"status\": \"OK\",\"id\": \"qwedfgt\"}";

	ans = parse_http_answer(req);
	TEST_ASSERT_EQUAL(1,ans->success);
	char* id = get_id_body(ans);

	TEST_ASSERT_EQUAL_STRING("qwedfgt",id);

	free(id);
	free_http_answer(ans);
}
