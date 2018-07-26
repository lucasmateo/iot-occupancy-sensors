#include "unity.h"
#include "parser.h"
#include "stdlib.h"

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
