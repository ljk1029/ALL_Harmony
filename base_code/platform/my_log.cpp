#include <iostream>
#include "my_log_run.h"
#include "my_log.h"


using namespace my_base::my_log;

// 回调函数
int callback_log() {
    int a = 5;
    int* b = nullptr;
    double c = 3.14;
    print(a, b, c); 
    return false;
}

int callback_bug() {
    print_debug("ss:", 1, "123");
    return false;
}

int log_test() {
     // 使用默认配置打印日志  
    log(LogLevel::INFO, "This is an info log message using default config.");  
  
    // 初始化 LogConfig 后打印日志  
    LogConfig::instance().init("custom.log", true, true);  
    log(LogLevel::WARN, "This is a warning log message using custom config.");  
  
    // 继续使用自定义配置打印日志  
    log(LogLevel::ERROR, "This is an error log message using custom config.");
    log_console_yellow_test();
    log_console_red_test();
    log_console_bg_test();
    return false;
}

/**
 * 测试用例
 * ./a.out -all
 * ./a.out -case int
 * ./a.out -case void
 */
int main(int argc, char *argv[]) {
    // 测试无参数
    test_runner test;  

    log_test();

    // 参数正常
    my_base::my_log::test_runner test_run(argc, argv);
    if (test_run.get_run_status("void")) {
        test_run.func_profile(
            "void", 
            []()->int{
                std::cout << "void fun" << std::endl;
                sleep(1);
                return false;
            } 
        );
    }


    // 永无bug
    // print_buddha();
    test_run.add_task("log", callback_log);
    test_run.add_task("bug", callback_bug);
    test_run.run_tasks();
    return 0;
}