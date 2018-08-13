#include "http_answer.h"

/*
send an id request to the server
return an http_answer struct containing the body of the response containing the id
take the webserver to be queried as a string as parameter
*/
http_answer* request_id(const char* webserver);

/*
send the state value to the given webserver
return an http_answer struct that may contain command to be executed
*/
http_answer* send_data(const char* webserver, int state);

/*
send the state value to the given webserver
return an http_answer struct that may contain command to be executed
*/
http_answer* send_data_array(const char* webserver,int* state,int length);
