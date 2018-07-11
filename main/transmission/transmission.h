
/*
configure the transmission before launching
*/
void transmission_config();

/*
send the message
if state is 0 sensor is not active
if state is 1 sensor is active
*/
void send_message(int state);
