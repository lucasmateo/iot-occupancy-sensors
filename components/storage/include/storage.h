
// return value available 
#define STORAGE_NOT_SET 2
#define STORAGE_OK 1
#define STORAGE_ERROR 0
#define STORAGE_FULL 4
#define STORAGE_TOCLEAR 5

/*
 * return the id if set
 * the value of status will indicate the result of the querry
 */
char* get_id(int* status);

/*
 * set the id in db
 * if the id was already set overwrite it
 * return the status
 */
int set_id(char* id);

/*
 * remove all the stored data
 */
int erase_all();

int get_sleep_time(int* status);

int set_sleep_time(int sleep_time);

int get_max_data(int* status);

int set_max_data(int max_data);

int get_actual_data(int* status);

int set_actual_data(int actual_data);

/*
increment the actual data value by 1
same action could be done using get and set
thus method avoid opening and closing the storage 2 times
*/
int incr_actual_data(int *status);

/*
return the state of the operation
if the STORAGE_FULL is returned it mean that the value max_data and actual_data are equal
the data then sould be sent to the server and thememory cleared
data is 1 or 0
*/
int add_data(int data);

/*
return the status
populate the data array with the stored data and then clear the memory
the array size must the be the same as max_data
*/
int get_data(int* data);
