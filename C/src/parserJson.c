#include "cJSON.h"
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char* parse_id(char* toParse){
  cJSON *json = cJSON_Parse(toParse);
  char* id_temp = cJSON_GetObjectItemCaseSensitive(json, PARSER_ID)->valuestring;
  char* id = (char*)malloc(sizeof(char) * (strlen(id_temp) + 1));

  strcpy(id,id_temp);

  cJSON_Delete(json);
  return id;
}

char* build_sensor_message(const char* id,int value){
  cJSON* json_message = cJSON_CreateObject();

  if(value !=0){
    cJSON_AddTrueToObject(json_message,PARSER_VALUE);
  } else {
    cJSON_AddFalseToObject(json_message,PARSER_VALUE);
  }

  cJSON_AddStringToObject(json_message,PARSER_ID, id);

  char* message = cJSON_Print(json_message);

  char* res = (char*)malloc(sizeof(char) * (strlen(message) + 1));
  strcpy(res,message);

  cJSON_Delete(json_message);

  return res;
}
