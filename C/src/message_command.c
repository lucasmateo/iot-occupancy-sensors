#include "message.h"
#include "storage.h"

void switch_store(){
  switch_mode(STORE);
}

void switch_send(){
  switch_mode(SEND);
}

void set_maxdata_128(){
  set_max_data(128);
}

void set_maxdata_64(){
  set_max_data(64);
}

void set_maxdata_512(){
  set_max_data(512);
}
