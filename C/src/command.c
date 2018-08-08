#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sleep_command.h"

struct command{
  char* command_name;
  void (*func)();
};

typedef struct command command;

command* command_list;
int nb_command = 6;

int is_init = 0;

command* init_command(char* name){
  command* comm = (command*) malloc(sizeof(command));

  comm->command_name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(comm->command_name,name);

  return comm;
}


void print(){
  printf("test\n");
}


void init(){
  command_list = (command*)malloc(sizeof(command) * nb_command);

  command* print_command = init_command("print");
  print_command->func = print;

  command* sleep3000_command = init_command("sleep_default");
  sleep3000_command->func = sleep_time3000ms;

  command* sleepdefault_command = init_command("sleep_3000");
  sleepdefault_command->func = reset_sleeptime;

  command* nosleep_command = init_command("nosleep");
  nosleep_command->func = nosleep_switch;

  command* modemsleep_command = init_command("modemsleep");
  modemsleep_command->func = modemsleep_switch;

  command* deepsleep_command = init_command("deepsleep");
  deepsleep_command->func = deepsleep_switch;

  command_list[0] = *print_command;
  command_list[1] = *sleep3000_command;
  command_list[2] = *sleepdefault_command;
  command_list[3] = *nosleep_command;
  command_list[4] = *modemsleep_command;
  command_list[5] = *deepsleep_command;

}

int process_command(char* command){
  if(!is_init){
    init();
  }

  for(int i = 0; i < nb_command ; i++){
    if(strcmp(command_list[i].command_name,command) == 0){
      command_list[i].func();
      return 1;
    }
  }
  return 0;
}
