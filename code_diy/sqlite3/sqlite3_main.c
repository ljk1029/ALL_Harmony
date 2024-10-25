/*
 * 文件名: component.c
 * 作者: ljk
 * 创建时间: 2023-07-20
 * 文件描述: 开源小组件操作
 */
#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>  
#include "mysqlite.h"
#include "common.h"

// 数据库目录
#define LOG_PATH  "./data.db"



// 创建表格
// 创建一个表名为ip_table，列名id 类型INTEGER，AUTOINCREMENT插入数据自增，long储存较大的数 TEXT字符串 INTEGER整数
const char *SQL_CREATE_TABLE_IP_DATA  = "CREATE TABLE IF NOT EXISTS ip_table (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp long, process TEXT, version INTEGER)";
const char *SQL_CREATE_TABLE_INSERT   = "CREATE TABLE IF NOT EXISTS ins_test (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp long)";
const char *SQL_CREATE_TABLE_DELETE   = "CREATE TABLE IF NOT EXISTS del_test (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp long)";
const char *SQL_CREATE_TABLE_UPDATE   = "CREATE TABLE IF NOT EXISTS upd_test (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp long)";
const char *SQL_CREATE_TABLE_SELECT   = "CREATE TABLE IF NOT EXISTS sel_test (id INTEGER PRIMARY KEY AUTOINCREMENT, timestamp long)";
int api_sqlite_createTable() {
    // 添加二次,结果只有一个表
    createTable(SQL_CREATE_TABLE_IP_DATA);
    createTable(SQL_CREATE_TABLE_IP_DATA);

    createTable(SQL_CREATE_TABLE_INSERT);
    createTable(SQL_CREATE_TABLE_DELETE);
    createTable(SQL_CREATE_TABLE_UPDATE);
    createTable(SQL_CREATE_TABLE_SELECT);
    return 0;
}

// 增
// 增加新记录(timestamp, process, version)三个变量对应值 VALUES(12, 'abc', 2)
const char *SQL_INSERT_IP_DATA   = "INSERT INTO ip_table (timestamp, process, version) VALUES(12, 'abc', 2)";
const char *SQL_INSERT_IP_DATA_0 = "INSERT INTO ip_table (timestamp, process, version) VALUES(12, 'bcd', 1)";
const char *SQL_INSERT_IP_DATA_1 = "INSERT INTO ip_table (timestamp, version) VALUES(12, 3)";
const char *SQL_INSERT_INSERT    = "INSERT INTO ins_test (timestamp) VALUES(12)";
const char *SQL_INSERT_DELETE    = "INSERT INTO del_test (timestamp) VALUES(12)";
const char *SQL_INSERT_UPDATE    = "INSERT INTO upd_test (timestamp) VALUES(12)";
int api_sqlite_insert() {
    // 添加二次,出现二条记录
    add(SQL_INSERT_IP_DATA);
    add(SQL_INSERT_IP_DATA);
    add(SQL_INSERT_IP_DATA_0);
    
    // 允许少一部分插入
    add(SQL_INSERT_IP_DATA_1);
    add(SQL_INSERT_INSERT);
    add(SQL_INSERT_DELETE);
    add(SQL_INSERT_UPDATE);
    return 0;
}

// 删
// 按照process = 'abc' 所有的process为'abc'都会删除
const char *SQL_DELETE_IP_DATA    = "DELETE FROM ip_table where process = 'abc'";
const char *SQL_DELETE_IP_DATA_1  = "DELETE FROM ip_table where id = 1";
const char *SQL_DELETE_DELETE     = "DELETE FROM del_test where timestamp = 12";
int api_sqlite_delete() {
    del(SQL_DELETE_IP_DATA);
    del(SQL_DELETE_IP_DATA_1);
    del(SQL_DELETE_DELETE);
    return 0;
}

// 改
// 改 where id = 2当id为2时，将SET id = 101, process ='13',将id改为101，process改为'13'
const char *SQL_UPDATE_IP_DATA   = "UPDATE ip_table SET id = 101, process ='13' where id = 3 ";
const char *SQL_UPDATE_UPDATE    = "UPDATE upd_test SET timestamp =31 where id = 1";
const char *SQL_UPDATE_UPDATE_0  = "UPDATE upd_test SET id = 100 where id = 2 ";
int api_sqlite_update() {
    update(SQL_UPDATE_IP_DATA);
    update(SQL_UPDATE_UPDATE);
    // 重复更改id，id相同会自动递增
    update(SQL_UPDATE_UPDATE_0);
    return 0;
}

// 查
const char *SQL_SELECT_IP_DATA = "SELECT * FROM ip_table";
int api_sqlite_select() {
    sqlite3_stmt *l_stmt = query(SQL_SELECT_IP_DATA);
	
    int i =1;
    while (next(l_stmt)) {
		int index = getColumnIndex(l_stmt, "process");
		const char* ret = getString(l_stmt, index);
        if(ret){
            printf("%d sel:%s\n", i++, ret);
        }
        else{
            printf("%d selnull\n", i++);
        } 
	}

    while (next(l_stmt)) {
		int index = getColumnIndex(l_stmt, "id");
        long ret = getLong(l_stmt, index);
        printf("sel:%ld\n", ret);
	}
    finalize(l_stmt);
    return 0;
}

int fun_sqlite3() {
    printf("建立数据库...\n");
	initDataBase(LOG_PATH);

    printf("创建表...\n");
    api_sqlite_createTable();

    printf("增加记录...\n");
    api_sqlite_insert();
    api_sqlite_insert();

    printf("删除记录...\n");
    api_sqlite_delete();

    printf("更改记录\n");
    api_sqlite_update();

    printf("查找记录...\n");
    api_sqlite_select();
	return 0;
}

// test函数
int main_test(int argc, char* argv[]) {
    PRINT_CMD_ARGS(argc, argv);
    FUNCTION_PRINT_API(fun_sqlite3);
    return 0;
}

// main函数
int main(int argc, char* argv[]) {
    main_test(argc, argv);
    return 0;
}