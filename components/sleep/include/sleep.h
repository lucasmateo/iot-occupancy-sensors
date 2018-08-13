
// different sleep mode 
#define DEEP_SLEEP 0
#define MODEM_SLEEP 1
#define NO_SLEEP 2

/*
 * enter sleep for the specified time in ms
 * do not assume that the program will resume from this position after wakeup
 * waking up may reboot the module
 */
void enter_sleep();

/*
switch sleep mode
*/
void switch_sleepmode(int mode);
