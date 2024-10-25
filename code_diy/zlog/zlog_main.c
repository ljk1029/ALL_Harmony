#include <stdio.h> 
#include "zlog.h"

#define LOG_FILE "./zlog.conf"  //指定配置文件路径，若当前文件夹直接写名字



int main(int argc, char** argv) {
	int rc;
	zlog_category_t *c;

	rc = zlog_init(LOG_FILE);
	if (rc) {
		printf("init failed\n");
		return -1;
	}

	c = zlog_get_category("my_cat");
	if (!c) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

    zlog_debug(c,  "hello, zlog - debug");
    zlog_info(c,   "hello, zlog - info");
    zlog_notice(c, "hello, zlog - notice");
    zlog_warn(c,   "hello, zlog - warn");
    zlog_error(c,  "hello, zlog - error");
    zlog_fatal(c,  "hello, zlog - fatal");

    char hex_buf[32];
    for (int i = 0; i < sizeof(hex_buf); i++) {
        hex_buf[i] = i;
    }
    hzlog_debug(c, hex_buf, sizeof(hex_buf));

	zlog_fini();

	return 0;
} 
