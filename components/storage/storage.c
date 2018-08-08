#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>
#include "storage.h"
#include <stdlib.h>
#include "config.h"

#define NAMESPACE "str"
#define ID_KEY "id"
#define SLEEP_KEY "sleep"
#define MAX_DATA_KEY "maxdata"
#define ACTUAL_DATA_KEY "actualdata"


char* get(int* status, char* key){
	nvs_handle my_handle;
	esp_err_t err;

	char* target;

	// Open
	err = nvs_open(NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK){
		*status = STORAGE_ERROR;
		return NULL;
	}

	// Read the size of memory space required for blob
	size_t required_size = 0;  // value will default to 0, if not set yet in NVS
	err = nvs_get_blob(my_handle, key, NULL, &required_size);
	if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND){
		*status = STORAGE_NOT_SET;
		return NULL;
	}

	if(required_size == 0){
		*status = STORAGE_NOT_SET;
		return NULL;
	}
	// Read previously saved blob if available

	if (required_size > 0) {
		target = (char*) malloc(required_size);
		err = nvs_get_blob(my_handle, key, target, &required_size);
		if (err != ESP_OK) {
			*status = STORAGE_ERROR;
			return NULL;
		}
		*status = STORAGE_OK;
		return target;
	}

	*status = STORAGE_ERROR;
	return NULL;
}

int set(char* id,char* key){
	nvs_handle my_handle;
	esp_err_t err;

	err = nvs_open(NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) return 0;

	err = nvs_set_blob(my_handle, key, id, sizeof(char) * (strlen(id)+1));
	if (err != ESP_OK) return 0;

	err = nvs_commit(my_handle);
	if (err != ESP_OK) return 0;

	nvs_close(my_handle);

	return 1;
}

int erase_all(){
	nvs_handle my_handle;
	esp_err_t err;

	err = nvs_open(NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) return 0;

	err = nvs_erase_all(my_handle);
	if (err != ESP_OK) return 0;

	err = nvs_commit(my_handle);
	if (err != ESP_OK) return 0;

	nvs_close(my_handle);

	return 1;
}

int get_int(int* status, char* key,esp_err_t (*func)(nvs_handle,const char*,int*)){
	nvs_handle my_handle;
	esp_err_t err;

	int target;

	// Open
	err = nvs_open(NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK){
		*status = STORAGE_ERROR;
		return NULL;
	}

	target = 0;
	err = func(my_handle, key, &target);
	if (err != ESP_OK) {
		*status = STORAGE_ERROR;
		return NULL;
	}
	*status = STORAGE_OK;
	return target;
}

int set_int(int id,char* key, esp_err_t (*func)(nvs_handle,const char*,int)){
	nvs_handle my_handle;
	esp_err_t err;

	err = nvs_open(NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) return 0;

	err = func(my_handle, key, id);
	if (err != ESP_OK) return 0;

	err = nvs_commit(my_handle);
	if (err != ESP_OK) return 0;

	nvs_close(my_handle);

	return 1;
}

int incr_int(int*status,char* key, esp_err_t (*setter)(nvs_handle,const char*,int), esp_err_t (*getter)(nvs_handle,const char*,int*)){
	nvs_handle my_handle;
	esp_err_t err;
	int target = 0;

	err = nvs_open(NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) return 0;

	err = getter(my_handle, key, &target);
	if (err != ESP_OK) {
		*status = STORAGE_ERROR;
		return 0;
	}

	err = setter(my_handle, key, target+1);
	if (err != ESP_OK) return 0;

	err = nvs_commit(my_handle);
	if (err != ESP_OK) return 0;

	nvs_close(my_handle);
	*status = STORAGE_OK;
	return 1;
}

esp_err_t int_set_i8(nvs_handle handle, const char* key, int val){
	return nvs_set_i8(handle,key,val);
}

esp_err_t int_get_i8(nvs_handle handle, const char* key, int* val){
	int8_t res;
	esp_err_t err = nvs_get_i8(handle,key,&res);
	*val = (int) res;
	return err;
}


char* get_id(int* status){
	return get(status,ID_KEY);
}


int set_id(char* id){
	return set(id,ID_KEY);
}

int get_sleep_time(int* status){
	return get_int(status,SLEEP_KEY,nvs_get_i32);
}

int set_sleep_time(int sleep_time){
	return set_int(sleep_time,SLEEP_KEY,nvs_set_i32);
}

int get_max_data(int* status){
	return get_int(status,MAX_DATA_KEY,nvs_get_i32);
}

int set_max_data(int max_data){
	return set_int(max_data,MAX_DATA_KEY,nvs_set_i32);
}

int get_actual_data(int* status){
	return get_int(status,ACTUAL_DATA_KEY,nvs_get_i32);
}

int set_actual_data(int actual_data){
	return set_int(actual_data,ACTUAL_DATA_KEY,nvs_set_i32);
}

int incr_actual_data(int *status){
	return incr_int(status,ACTUAL_DATA_KEY,nvs_set_i32,nvs_get_i32);
}

int add_data(int data){
	int status = 0;
	int actualdata = get_actual_data(&status);
	if(status != STORAGE_OK){
		actualdata = 0;
		set_actual_data(actualdata);
	}
	int maxdata = get_max_data(&status);
	if(status != STORAGE_OK){
		maxdata = MAX_STORAGE;
		set_max_data(maxdata);
	}

	if(actualdata >= maxdata){
		return STORAGE_FULL;
	}

	char key[5];
	itoa(actualdata, key, 10);
	set_int(data,key,int_set_i8);

	incr_actual_data(&status);

	if(actualdata+1 >= maxdata){
		return STORAGE_TOCLEAR;
	}



	return status;

}

int get_data(int* data){
	int status = 0;
	int actualdata = get_actual_data(&status);
	if(status != STORAGE_OK){
		return STORAGE_ERROR;
	}

	char key[5];

	for(int i = 0; i < actualdata;i++ ){
		itoa(i,key,10);
		data[i] = get_int(&status,key,int_get_i8);
	}
	set_actual_data(0);
	return STORAGE_OK;
}
