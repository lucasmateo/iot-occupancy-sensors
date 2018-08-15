#define SEND 1
#define STORE 2

/*
check if id present in storage if it is do nothing else
get new id from server and write it to the storage so itcan be fetched later
*/
int check_id();

/*
send data to the server
*/
void send_readings(int state);

/*
change the data sending mode to send or store
*/
void switch_mode(int mode);
