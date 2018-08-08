#include "unity.h"
#include "storage.h"
#include <stdlib.h>
#include "nvs_flash.h"


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

void storage_writing_int_test(){

	int val = 35;
	erase_all();
	int status = 0;
	set_sleep_time(val);

	int read = get_sleep_time(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL(val,read);

	erase_all();

}

void storage_writing_max_data_val_test(){

	int val = 1005;
	erase_all();
	int status = 0;
	set_max_data(val);

	int read = get_max_data(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL(val,read);

	erase_all();

}

void storage_writing_actual_data_val_test(){

	int val = 800;
	erase_all();
	int status = 0;
	set_actual_data(val);

	int read = get_actual_data(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL(val,read);

	erase_all();

}

void storage_incr_actual_data_val_test(){

	int val = 800;
	erase_all();
	int status = 0;
	set_actual_data(val);

	incr_actual_data(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);

	int read = get_actual_data(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL(val+1,read);

	erase_all();

}

void storage_data_test(){
	int status = 0;

	int arr[] = {0,0,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1};
	set_max_data(100);

	for(int i = 0;i<18;i++){
		add_data(arr[i]);
	}

	int data_len = get_actual_data(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL(18,data_len);

	int res[18];
	get_data(res);
	TEST_ASSERT_EQUAL_INT_ARRAY(arr,res,18);

	data_len = get_actual_data(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL(0,data_len);
}

void storage_full_test(){
	set_max_data(1);
	int status = 0;
	TEST_ASSERT_EQUAL(STORAGE_TOCLEAR,add_data(0));
	
	int data_len = get_actual_data(&status);
	TEST_ASSERT_EQUAL(STORAGE_OK,status);
	TEST_ASSERT_EQUAL(1,data_len);

	TEST_ASSERT_EQUAL(STORAGE_FULL,add_data(0));
}
