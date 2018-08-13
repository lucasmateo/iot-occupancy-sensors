#include "http_answer.h"
#include <stdlib.h>
#include "config.h"
#include "request.h"
#include "storage.h"
#include "parser.h"
#include "command.h"
#include "message.h"

int send_mode = SEND;

void process_answer(http_answer* ans){
  int len = 0;

  char** arr = get_command_list(ans->answer,&len);

  for(int i = 0;i<len;i++){
    process_command(arr[i]);
    free(arr[i]);
  }
  free(arr);
}

int check_id(){
  int status =0;
	get_id(&status);
	if(status == STORAGE_OK){
		return 1;
	}

	http_answer* ans = request_id(WEB_SERVER);

	char* id = get_id_body(ans);

	set_id(id);
	free(id);
	return 1;
}

void send_readings(int state){
  http_answer* ans;
  int status;
  switch (send_mode) {
    case SEND:
      ans = send_data(WEB_SERVER,state);
      process_answer(ans);
      free_http_answer(ans);
      break;
    case STORE:
      status = add_data(state);

      if(status == STORAGE_TOCLEAR){
        int length = get_actual_data(&status);
        int data[length];
        status = get_data(data);
        ans = send_data_array(WEB_SERVER,data,length);
        process_answer(ans);
        free(ans);
      }
      break;
  }
}

void switch_mode(int mode){
  send_mode = mode;
}
