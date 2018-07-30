#define PARSER_ID "id"
#define PARSER_VALUE "val"

/*
parse the string to get the id
return value must be freed afterward
*/
char* parse_id(char* toParse);

/*
parse the string to get the id
return value must be freed afterward
*/
char* build_sensor_message(const char* id,int value);
