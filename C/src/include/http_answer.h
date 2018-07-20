
#ifndef COMPONENTS_HTTP_INCLUDE_HTTP_ANSWER_H_
#define COMPONENTS_HTTP_INCLUDE_HTTP_ANSWER_H_

#define CONTENT_LENGTH "Content-Length: "
#define SEPARATOR "\r\n"

/*
 * represent a http answer
 * success indicate if the char array is readable
 * if 1 it is
 * else it is not
 */

struct http_answer {
	int success;
	char* answer;
};

typedef struct http_answer http_answer;

/*
 * init the http answer
 * return a pointer on the initialized struct
 */
http_answer* init_http_answer();

/*
 * free the struct memory
 * parameter must not be null
 */
void free_http_answer(http_answer* answer);

/*
 * make the given struct empty
 * set the integer success to 0
 */
http_answer* empty_http_answer(http_answer* answer);

/*
 * parse the given char array into the http answer
 */
http_answer* parse_http_answer(http_answer* answer, char* to_parse);



#endif /* COMPONENTS_HTTP_INCLUDE_HTTP_ANSWER_H_ */
