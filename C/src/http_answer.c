#include "http_answer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


http_answer* init_http_answer(){
	http_answer* ans = (http_answer*)malloc(sizeof(http_answer));

	ans->answer = (char*)malloc(sizeof(char));
	*(ans->answer) = '\0';
	ans->success = 0;

	return ans;
}

http_answer* empty_http_answer(http_answer* answer){
	free(answer->answer);

	answer->answer = (char*)malloc(sizeof(char));
	*(answer->answer) = '\0';
	answer->success = 0;

	return answer;
}

http_answer* parse_http_answer(http_answer* answer, char* to_parse){
	empty_http_answer(answer);

	char* find = strstr(to_parse,CONTENT_LENGTH);

	if(find == NULL){
		answer->success = 1;
		return answer;
	}

	char length_arr[10];

	find += strlen(CONTENT_LENGTH);
	int i =0;
	while(find[i] != '\r'){
		length_arr[i] = find[i];
		i++;
	}

	if(i==0){
		answer->success = 1;
		return answer;
	}
	length_arr[i+1] = 0;

	int length = atoi(length_arr);

	answer->answer = (char*)malloc(sizeof(char) * length+1);

	find = strstr(to_parse,SEPARATOR SEPARATOR);

	find += strlen(SEPARATOR SEPARATOR);

	strcpy(answer->answer,find);
	answer->success = 1;

	return answer;
}




void free_http_answer(http_answer* answer){
	free(answer->answer);
	free(answer);
}