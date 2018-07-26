
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
 * parse the given char array into the http answer
 */
http_answer* parse_http_answer( char* to_parse);

/*
 * print the answers
 */
void print_http_answer(http_answer* ans);

/*
 * get the id fromthe json body of the answer
 */
char* get_id_body(http_answer* ans);



#endif /* COMPONENTS_HTTP_INCLUDE_HTTP_ANSWER_H_ */
