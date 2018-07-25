#define STORAGE_NOT_SET 2
#define STORAGE_OK 1
#define STORAGE_ERROR 0


/*
 * return the id if set
 * the value of status will indicate the result of the querry
 */
char* get_id(int* status);

/*
 * set the id in db
 * if the id was already set overwrite it
 */
int set_id(char* id);

/*
 * remove all the stored data
 */
int erase_all();

