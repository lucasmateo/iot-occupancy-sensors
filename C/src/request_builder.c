#include "http_answer.h"
#include <stdlib.h>
#include <string.h>


void build_request(char* request,const char* method,const char* path,const char* webserver,const char* content){
	request[0] = 0;
	strcpy(request,method);
	strcat(request," ");
	strcat(request,path);
	strcat(request, " HTTP/1.0\r\n"
		"Host: ");
	strcat(request,webserver);
	strcat(request,"\r\n"
		"User-Agent: esp-idf/1.0 esp32\r\n");

	int content_length = strlen(content);
	if(content_length == 0){
		strcat(request,SEPARATOR);
		return;
	}

	strcat(request,CONTENT_LENGTH);

	char contentL[5];

	strcat(request,itoa(content_length, contentL, 10));
	strcat(request,SEPARATOR);
	strcat(request,SEPARATOR);
	strcat(request,content);
}
