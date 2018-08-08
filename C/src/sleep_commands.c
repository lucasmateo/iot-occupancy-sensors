#include "storage.h"
#include "config.h"
#include "sleep.h"

void sleep_time3000ms(){
  set_sleep_time(3000);
}

void reset_sleeptime(){
  set_sleep_time(MESURE_FREQUENCY);
}

void nosleep_switch(){
  switch_sleepmode(NO_SLEEP);
}

void modemsleep_switch(){
  switch_sleepmode(MODEM_SLEEP);
}

void deepsleep_switch(){
  switch_sleepmode(DEEP_SLEEP);
}
