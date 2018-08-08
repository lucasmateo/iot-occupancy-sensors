#include "unity.h"
#include "parser.h"
#include "stdlib.h"
#include <string.h>

void id_request_test(void){
    char* id = parse_id("{\"status\": \"OK\",\"id\": \"qwedfgt\"}");

    TEST_ASSERT_EQUAL_STRING("qwedfgt",id);

    free(id);
}

void sensor_msg_test(){
  char* message = build_sensor_message("rtrtrt",1);

  TEST_ASSERT_TRUE(*message);

  free(message);
}

void command_list_test(){
  char* str = "[\"test\",\"print\"]";

  int len = 0;
  char** arr = get_command_list(str,&len);

  TEST_ASSERT_EQUAL(2,len);
  TEST_ASSERT_EQUAL(0,strcmp(arr[0],"test"));
  TEST_ASSERT_EQUAL(0,strcmp(arr[1],"print"));

  for(int i = 0;i<len;i++){
    free(arr[i]);
  }
  free(arr);

}

void wrong_command_list_test(){
  char* str = "{}";

  int len = 0;
  char** arr = get_command_list(str,&len);

  TEST_ASSERT_EQUAL(0,len);

  free(arr);

}

void value_array_test(){
  int arr[] = {0,1,1,1,1,1,1,1,1,1,1,0};

  char* str = build_sensor_array_message("eest",arr,12);

  TEST_ASSERT_EQUAL_STRING("{\n\x09\"val\":\x09[0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],\n\x09\"id\":\x09\"eest\"\n}",str);

  free(str);
}
