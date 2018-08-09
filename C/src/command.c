#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sleep_command.h"
#include "hashmap.h"
#include "message_command.h"

int is_init = 0;

map_t mymap;

void print(){
  printf("test\n");
}


void init(){

  mymap = hashmap_new();

  hashmap_put(mymap,"print",print);
  hashmap_put(mymap,"sleep_default",reset_sleeptime);
  hashmap_put(mymap,"sleep_3000",sleep_time3000ms);
  hashmap_put(mymap,"nosleep",nosleep_switch);
  hashmap_put(mymap,"modem",modemsleep_switch);
  hashmap_put(mymap,"deepsleep",deepsleep_switch);
  hashmap_put(mymap,"switch_send",switch_send);
  hashmap_put(mymap,"switch_store",switch_store);
  hashmap_put(mymap,"max_data64",set_maxdata_64);
  hashmap_put(mymap,"maxdata_128",set_maxdata_128);
  hashmap_put(mymap,"max_data512",set_maxdata_512);

}

int process_command(char* command){
  if(!is_init){
    init();
  }
  void (*func)();
  int error = hashmap_get(mymap,command,(void**)(&func));
  if(error == MAP_OK){
    func();
    return 1;
  }

  return 0;
}
