#include "cJSON.h"
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//handle all the parsing operation using JSON format

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

  cJSON_AddNumberToObject(json_message,PARSER_VALUE,value);

  cJSON_AddStringToObject(json_message,PARSER_ID, id);

  char* message = cJSON_Print(json_message);

  char* res = (char*)malloc(sizeof(char) * (strlen(message) + 1));
  strcpy(res,message);

  cJSON_Delete(json_message);

  return res;
}

char* build_sensor_array_message(const char* id,int* value,int length){
  cJSON* json_message = cJSON_CreateObject();
  cJSON* arr = cJSON_AddArrayToObject(json_message,PARSER_VALUE);

  for(int i = 0;i<length;i++){
    cJSON_AddItemToArray(arr,cJSON_CreateNumber(value[i]));
  }



  cJSON_AddStringToObject(json_message,PARSER_ID, id);

  char* message = cJSON_Print(json_message);

  char* res = (char*)malloc(sizeof(char) * (strlen(message) + 1));
  strcpy(res,message);

  cJSON_Delete(json_message);

  return res;
}

char** get_command_list(char* to_parse,int* len){
  cJSON *json = cJSON_GetObjectItemCaseSensitive(cJSON_Parse(to_parse),ARRAY_LABEL);

  *len = cJSON_GetArraySize(json);
  if(*len == 0){
    return NULL;
  }
  char** arr = (char**) malloc(sizeof(char*)*(*len));
  int i = 0;
  cJSON* obj;
  cJSON_ArrayForEach(obj, json){
    int item_len = strlen(obj->valuestring);

    arr[i] = (char*) malloc(sizeof(char) * (item_len+ 1));

    strcpy(arr[i],obj->valuestring);
    i++;
  }
  cJSON_Delete(json);
  return arr;
}
