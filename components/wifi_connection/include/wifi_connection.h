


/*
return if the wifi is connected
*/
int is_connected();


/*
connect to the wifi
if the function end with TRUE, is_connect should return true
else the wifi is not connected
*/
int connect();

/*
 * setup all needed element for connection
 */
void setup_connection();

/*
 * disconnect from the connected wifi
 */
void wifi_stop();
