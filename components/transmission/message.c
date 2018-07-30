#include "http_answer.h"
#include <stdlib.h>
#include "config.h"
#include "request.h"
#include "storage.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"


int check_id(){
  int status =0;
	get_id(&status);
	if(status == STORAGE_OK){
		return 1;
	}

	http_answer* ans = get_request(GET_PATH,WEB_SERVER);

	char* id = get_id_body(ans);

	set_id(id);
	free(id);
	return 1;
}


void send_readings(int state){
  http_answer* ans = post_request(POST_PATH,WEB_SERVER,state);

  free_http_answer(ans);

}
