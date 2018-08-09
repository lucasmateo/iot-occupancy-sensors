#include "command.h"
#include "unity.h"

void test_print_command(){
  int result = process_command("print");
  TEST_ASSERT_EQUAL(1,result);
  result = process_command("sleep_default");
  TEST_ASSERT_EQUAL(1,result);
  result = process_command("sleep_3000");
  TEST_ASSERT_EQUAL(1,result);
  result = process_command("nosleep");
  TEST_ASSERT_EQUAL(1,result);
  result = process_command("modem");
  TEST_ASSERT_EQUAL(1,result);
  result = process_command("deepsleep");
  TEST_ASSERT_EQUAL(1,result);
  result = process_command("switch_send");
  TEST_ASSERT_EQUAL(1,result);
}

void test_no_command(){
  int result = process_command("sllll");
  TEST_ASSERT_EQUAL(0,result);
}
