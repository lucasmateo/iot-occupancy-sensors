#include "unity.h"
#include "storage.h"
#include <stdlib.h>

void storage_test(){
	erase_all();
	int status = 0;

	free(get_id(&status));

	TEST_ASSERT_EQUAL(STORAGE_NOT_SET,status);
}


void storage_writing_test(){
	char* setid = "salut";
	erase_all();
	int status = 0;
	set_id(setid);
	char* id = get_id(&status);

	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL_STRING(setid,id);

	erase_all();

	free(id);
}
