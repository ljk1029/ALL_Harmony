/*
 * 文件名: component.c
 * 作者: ljk
 * 创建时间: 2023-07-20
 * 文件描述: 开源小组件操作
 */
#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>  
#include "base64.h"
#include "common.h"



// base64编码
unsigned char* api_base64_encode(const char* input) {
    size_t len = 0;
    char* output_en = base64_encode(input, strlen(input), &len);
    if(output_en) {
        printf("输入源码:%s\n", input);
        printf("输出编码:%s\n", output_en);
        free(output_en);
    }
    return 0;
}

// base64解码
unsigned char* api_base64_decode(const char* input) {
    size_t len = 0;   
    char* output_de = base64_decode(input, strlen(input), &len);
    if(output_de) {
        printf("输入编码:%s\n",input);
        printf("输出解码:%s\n",output_de);
        free(output_de);
    }  
    return 0;
}

int fun_base64() {
    unsigned char* input  = "ljk, hello!";
    unsigned char* output = "bGprLCBoZWxsbyE=";
    api_base64_encode(input);
    api_base64_decode(output);
}

// test函数
int main_test(int argc, char* argv[]) {
    PRINT_CMD_ARGS(argc, argv);
    FUNCTION_PRINT_API(fun_base64);
    return 0;
}

// main函数
int main(int argc, char* argv[]) {
    main_test(argc, argv);
    return 0;
}