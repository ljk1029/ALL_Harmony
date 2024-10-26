/*
 * 文件名: component.c
 * 作者: ljk
 * 创建时间: 2023-07-20
 * 文件描述: 开源小组件操作
 */
#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>  
#include "cJSON.h"
#include "common.h"



#define CJSON_STR   \
    "{\"name\":\"John Doe\"," \
    "\"age\":30," \
    "\"is_student\":true," \
    "\"address\":{" \
        "\"city\":\"New York\"," \
        "\"zip_code\":\"10001\"" \
    "}," \
    "\"hobbies\":[\"reading\",\"gaming\",\"cooking\"]}"


// 解析cjson数据
int api_get_cJSON() {
    const char *json_data = CJSON_STR;
    printf("字符输入:%s\n", json_data);

    cJSON* root = cJSON_Parse(json_data);
    if (root == NULL) {
        printf("Error while parsing JSON data.\n");
        return 1;
    }

    cJSON* name = cJSON_GetObjectItem(root, "name");
    cJSON* age = cJSON_GetObjectItem(root, "age");
    cJSON* is_student = cJSON_GetObjectItem(root, "is_student");
    cJSON* address = cJSON_GetObjectItem(root, "address");
    cJSON* hobbies = cJSON_GetObjectItem(root, "hobbies");

    printf("Name: %s\n", name->valuestring);
    printf("Age:  %d\n", age->valueint);
    printf("Is Student: %s\n", is_student->type == cJSON_True ? "true" : "false");
    printf("City: %s\n", cJSON_GetObjectItem(address, "city")->valuestring);
    printf("Zip Code: %s\n", cJSON_GetObjectItem(address, "zip_code")->valuestring);

    printf("Hobbies:\n");
    for (int i = 0; i < cJSON_GetArraySize(hobbies); i++) {
        cJSON* hobby = cJSON_GetArrayItem(hobbies, i);
        printf("- %s\n", hobby->valuestring);
    }

    char* json_data_p = cJSON_Print(root);
    if(json_data_p){
        printf("格式输出:%s\n", json_data_p);
        free(json_data_p);
    }

    cJSON_Delete(root);
    return 0;
}

// 组建cjson数据
int api_put_cJSON() {
    cJSON* root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", "John Doe");
    cJSON_AddNumberToObject(root, "age", 30);
    cJSON_AddBoolToObject(root, "is_student", 1);

    cJSON* address = cJSON_CreateObject();
    cJSON_AddStringToObject(address, "city", "New York");
    cJSON_AddStringToObject(address, "zip_code", "10001");
    cJSON_AddItemToObject(root, "address", address);

    cJSON* hobbies = cJSON_CreateArray();
    cJSON_AddItemToArray(hobbies, cJSON_CreateString("reading"));
    cJSON_AddItemToArray(hobbies, cJSON_CreateString("gaming"));
    cJSON_AddItemToArray(hobbies, cJSON_CreateString("cooking"));
    cJSON_AddItemToObject(root, "hobbies", hobbies);

    char* json_data = cJSON_Print(root);
    if(json_data){
        printf("格式输出:%s\n", json_data);
        free(json_data);
    }
    
    char *json_data_s = cJSON_PrintUnformatted(root);
    if(json_data_s){
        printf("字符输出:%s\n", json_data_s);
        free(json_data_s);
    }
    
    cJSON_Delete(root);
    return 0;
}

// test函数
int main_test(int argc, char* argv[]) {
    PRINT_CMD_ARGS(argc, argv);
    FUNCTION_PRINT_API(api_get_cJSON);
    FUNCTION_PRINT_API(api_put_cJSON);
    return 0;
}

// main函数
int main(int argc, char* argv[]) {
    main_test(argc, argv);
    return 0;
}