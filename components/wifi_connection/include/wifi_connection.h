
#define WIFI_ALWAYSUP 0
#define WIFI_NORMAL 1

/*
return if the wifi is connected
*/
int is_connected();


/*
connect to the wifi
if the function end with TRUE, is_connect should return true
else the wifi is not connected
*/
int wifi_connect();

/*
 * setup all needed element for connection
 */
void setup_connection();

/*
 * disconnect from the connected wifi
 */
void wifi_stop();

/*
goes into modem sleep mode
*/
void modem_sleep();

void set_mode(int mode);
