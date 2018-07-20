#include "unity.h"
#include "http_answer.h"
#include <string.h>
#include <stdio.h>

void test_init_struct(void)
{
	http_answer* ans = init_http_answer();
    TEST_ASSERT_EQUAL(0,ans->success);
    TEST_ASSERT_EQUAL('\0',*(ans->answer));

    free_http_answer(ans);
}

void test_empty_struct(void){
	http_answer* ans = init_http_answer();
	ans->success = 1;
	*(ans->answer)=10;

	TEST_ASSERT_EQUAL(1,ans->success);
	TEST_ASSERT_EQUAL(10,*(ans->answer));

	empty_http_answer(ans);

	TEST_ASSERT_EQUAL(0,ans->success);
	TEST_ASSERT_EQUAL('\0',*(ans->answer));
    free_http_answer(ans);
}

void test_http_parse(void){
	http_answer* ans = init_http_answer();

	char* req = "HTTP/1.1 200 OK \r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: 59\r\n"
			"Accept-Language: en-us\r\n"
			"Accept-Encoding: gzip, deflate\r\n"
			"Connection: Keep-Alive\r\n\r\n"
			"licenseID=string&content=string&/paramsXML=string";

	parse_http_answer(ans,req);
	TEST_ASSERT_EQUAL(1,ans->success);
	TEST_ASSERT_EQUAL_STRING(ans->answer,"licenseID=string&content=string&/paramsXML=string");
}

void test_http_parse_nocontent(void){
	http_answer* ans = init_http_answer();

	char* req = "HTTP/1.1 200 OK \r\n"
			"User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
			"Host: www.tutorialspoint.com\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Accept-Language: en-us\r\n"
			"Accept-Encoding: gzip, deflate\r\n"
			"Connection: Keep-Alive\r\n\r\n"
			"licenseID=string&content=string&/paramsXML=string";

	parse_http_answer(ans,req);
	TEST_ASSERT_EQUAL(1,ans->success);
	TEST_ASSERT_EQUAL(*(ans->answer),0);
}

int main(void)
{
    UNITY_BEGIN();
	RUN_TEST(test_init_struct);
	RUN_TEST(test_empty_struct);
	RUN_TEST(test_http_parse);
	RUN_TEST(test_http_parse_nocontent);
    return UNITY_END();
}
