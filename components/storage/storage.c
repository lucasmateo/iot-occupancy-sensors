#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>
#include "storage.h"

#define NAMESPACE "str"
#define ID_KEY "id"


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


char* get_id(int* status){
	return get(status,ID_KEY);
}


int set_id(char* id){
	return set(id,ID_KEY);
}
