#include "http_answer.h"

http_answer* request_id(const char* webserver);

http_answer* send_data(const char* webserver, int state);

http_answer* send_data_array(const char* webserver,int* state,int length);
