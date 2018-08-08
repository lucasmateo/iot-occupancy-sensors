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

/*
return an array of string containing the name of the command
to parse is the string to parse
len is an integer where the length of the array will be stored
*/
char** get_command_list(char* to_parse,int* len);

char* build_sensor_array_message(const char* id,int* value,int length);
