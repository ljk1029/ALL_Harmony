#ifndef _MY_LOG_PRINT_H__
#define _MY_LOG_PRINT_H__

#include <iostream>
#include <functional>
#include <string>
#include <thread>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <map>
#include <vector>
#include <atomic>
#include <sys/resource.h>
#include <sys/times.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include "my_log.h"

/**
 * print：格式化参数打印， 如 print(a, "123", 54);
 * print_dbg: 格式化打印带， 比print多了调试信息
 * test_runner test_runner(argc, argv)： 根据输入选择测试项目
 */
namespace my_base {
namespace my_log{

void print_buddha();

// 1通用打印
template <typename T, typename... Args>
void print(const T &first, const Args &...args) {
    // 检查是否是空指针
    if constexpr (std::is_pointer_v<T>) {
        if (first == nullptr) {
            std::cout << "nullptr";
        } else {
            std::cout << *first; // 打印指针指向的值
        }
    } else {
        std::cout << first; // 打印非指针类型的值
    }
    
    // 如果还有其他参数，则打印一个空格，然后递归调用
    if constexpr (sizeof...(args) > 0) {
        std::cout << " ";
        print(args...); // 继续递归打印其他参数
    } else {
        std::cout << std::endl; // 没有更多参数，打印换行
    }
}


// 2调试打印
// 一个跨平台模板
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#define GET_PID() static_cast<long>(GetCurrentProcessId())
#elif defined(__unix__) || defined(__unix) ||  \
    defined(__APPLE__) || defined(__MACH__) || \
    defined(__linux__) || defined(__linux)
#include <unistd.h>
#define GET_PID() static_cast<long>(getpid())
#else
#error "Unsupported platform"
#endif

// 定义一个宏来简化 print 函数调用
#define print_debug(...)  \
    do {  \
        std::cout << "[" << __FILE__ << ":" << __LINE__ << " " << __func__ << "]" \
            <<" pid: " << GET_PID()  \
            << ", tid: " << std::this_thread::get_id() << ", ";  \
        print(__VA_ARGS__);  \
    } while (0)


// 任务测量
class TaskProfiler {
public:
    // 启动计时器
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    // 停止计时器并计算运行时间
    double stop() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        return duration / 1000000.0; // 返回秒数
    }

    // 获取当前任务的内存使用情况
    size_t getMemoryUsage() {
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        return usage.ru_maxrss; // 返回最大常驻集大小（单位为 KB）
    }

    // 获取当前任务的 CPU 使用率
    double getCpuUsage() {
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        return calculateCpuUsage(usage.ru_utime, usage.ru_stime);
    }

    // 获取各个 CPU 核心的使用率（这需要特定的系统支持，以下仅为示例）
    std::vector<double> getCoreCpuUsage() {
        std::vector<double> coreUsage;
        std::ifstream file("/proc/stat");
        std::string line;

        // 读取文件直到文件结束
        while (std::getline(file, line)) {
            // 查找以 "cpu" 开头且后面跟着数字的行
            if (line.find("cpu") == 0 && std::isdigit(line[3])) {
                std::istringstream iss(line);
                std::string cpuLabel;
                long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
                
                // 读取 CPU 标签和各个时间统计
                iss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

                // 计算总的非空闲时间
                long total = user + nice + system + irq + softirq + steal;

                // 计算总的 CPU 时间
                long totalCpuTime = total + idle;

                // 计算使用率
                double usage = static_cast<double>(total) / totalCpuTime;

                // 添加到核心使用率向量
                coreUsage.push_back(usage);
            }
        }

        file.close();
        return coreUsage;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

    // 计算 CPU 使用率
    double calculateCpuUsage(struct timeval user_time, struct timeval sys_time) {
        return (user_time.tv_sec + sys_time.tv_sec) + (user_time.tv_usec + sys_time.tv_usec) / 1000000.0;
    }
};

// 3、运行测试类
// 父类，用于解析main函数的参数
class command_line_parser {
public:
    command_line_parser(int argc, char* argv[]) 
    : argc_(argc)
    , argv_(argv) {
        parse_options();
    }

    virtual ~command_line_parser() {}

    // 虚函数，用于打印使用说明
    virtual void print_usage() const = 0;

    // 检查是否运行所有测试用例
    bool get_run_all() const {
        return run_all_cases_;
    }

    // 获取特定的测试用例名称
    std::string get_run_cases() const {
        return run_cases_;
    }

protected:
    // 解析命令行参数
    void parse_options() {
        run_all_cases_ = cmd_option_exists(argv_, argv_ + argc_, "-all");
        run_cases_ = get_cmd_option(argv_, argv_ + argc_, "-case");
    }

    // 获取命令行参数
    std::string get_cmd_option(char** begin, char** end, const std::string& option) {
        char** itr = std::find(begin, end, option);
        if (itr != end && ++itr != end) {
            return *itr;
        }
        return "";
    }

    // 检查命令行参数是否存在
    bool cmd_option_exists(char** begin, char** end, const std::string& option) {
        return std::find(begin, end, option) != end;
    }

private:
    int argc_;
    char** argv_;
    bool run_all_cases_ = false;
    std::string run_cases_;
};

// 子类 test_runner，继承自 command_line_parser
class test_runner 
: public command_line_parser 
, public TaskProfiler
{
#define PRINT_ARGV() \
    std::cout << "- Run all cases: " << (get_run_all() ? "yes" : "no") << std::endl; \
    std::cout << "- Run cases:     " << get_run_cases() << std::endl;

public:
    using CallbackFunc = std::function<int()>;
    test_runner() 
    : command_line_parser(0, nullptr){
        print_buddha();
        print_usage();
    }

    test_runner(int argc, char* argv[])
    : command_line_parser(argc, argv){
        print_buddha();
        PRINT_ARGV();
    }

    // 运行函数
    void func_print(const std::string& title, CallbackFunc callback) {
        print_fun_title(title, true);
        int ret = callback();
        print_fun_title(title, false, ret);
    }

    void func_profile(const std::string& title, CallbackFunc callback) {
        print_fun_title(title, true);
        start(); 
        int ret = callback(); 
        double duration = stop(); // 任务计时
        size_t memoryUsage = getMemoryUsage(); // 获取内存使用
        double cpuUsage    = getCpuUsage();    // 获取 CPU 使用率
        std::vector<double> coreCpuUsage = getCoreCpuUsage(); // 获取核心使用率

        // 打印结果
        std::cout << "Task:         " << title << "\n";
        std::cout << "Duration:     " << duration << " seconds\n";
        std::cout << "Memory Usage: " << memoryUsage << " KB\n";
        std::cout << "CPU Usage:    " << cpuUsage << " seconds\n";
        // 打印核心使用率
        for (size_t i = 0; i < coreCpuUsage.size(); ++i) {
            std::cout << "Core " << i << " CPU Usage: " << coreCpuUsage[i] << "\n";
        }
        print_fun_title(title, false, ret);
    }

    // 获取运行状态
    bool get_run_status(const std::string &option) { 
        bool run_all_cases = get_run_all();
        std::string run_cases = get_run_cases();
        return run_all_cases || run_cases.find(option) != std::string::npos; 
    }

    bool get_run_status(char option) {
        std::string str_option(1, option);
        return get_run_status(str_option);
    }

    // 添加任务
    void add_task(const std::string& key, CallbackFunc callback) {
        task_list_map[key] = callback;
    }

    // 运行所有任务
    void run_tasks() {
        for (const auto& pair : task_list_map) {
            if (stop_task_flag.load()) {
                std::cout << "Task execution stopped." << std::endl;
                break;
            }
            func_print(pair.first, pair.second);
        }
    }

    // 清空任务列表
    void clear_tasks() {
        task_list_map.clear();
    }

    // 删除特定任务
    void delete_task(const std::string& key) {
        task_list_map.erase(key);
    }

    // 停止运行任务
    void stop_tasks() {
        stop_task_flag.store(true); 
    }

    // 重置停止标志
    void reset_stop_flag() {
        stop_task_flag.store(false);
    }

    // 重写虚函数，打印使用说明
    void print_usage() const override {
        std::cout << "Usage: ./a.out [options]" << std::endl
            << "Options:" << std::endl
            << "  -all             Run all test cases" << std::endl
            << "  -case <name>     Run specific test case" << std::endl
            << "Examples:" << std::endl;

        // 使用循环结构来打印示例
        const std::vector<std::string> examples = {
            "./a.out -all",
            "./a.out -case case_name",
        };

        for (const auto& example : examples) {
            std::cout << "  " << example << std::endl;
        }
    }

private:
    static void print_fun_title(const std::string& title, bool start_mode, int ret = -1) {
        const std::string::size_type TOTAL_PRINT_LENGTH = 64; // 总打印长度，计算边框长度
        const std::string::size_type title_length = title.length();
        const std::string::size_type max_title_length = TOTAL_PRINT_LENGTH - 22; 
        std::map<std::string, std::string> title_map = {
            {"test",  "[TEST for"},
            {"start", "function start]"},
            {"end",   " function  end]"}
        };
        char border_char = start_mode ? '~':'*';

        // 确保边框长度为正数
        std::string::size_type border_len = (max_title_length - title_length - 10) / 2;
        std::string border = std::string(border_len, border_char);

        // 打印返回值
        if (!start_mode && ret != -1) {
            std::string output = "[TEST callback return: " + std::to_string(ret) + " ]\n";
            std::cout << output;
        }

        // 打印标题和边框
        log_set_console_colour(SET_CLR_GREEN);
        // std::cout << border;
        std::cout << title_map.at("test") << title << (start_mode ? title_map.at("start") : title_map.at("end"));
        std::cout << border << std::endl;
        log_set_console_colour(SET_CLR_RESET);

        // 如果是结束
        if (!start_mode) {
            std::cout << std::endl;
        }
    }

private:
    // 任务列表，使用 map 存储 key 和对应的回调函数
    std::map<std::string, CallbackFunc> task_list_map;
    // 标记任务是否应该停止
    std::atomic<bool> stop_task_flag{false};

};

void print_buddha() {
    std::cout << "                _oo0oo_" << std::endl;
    std::cout << "               o8888888o" << std::endl;
    std::cout << "               88\" . \"88" << std::endl;
    std::cout << "               (| -_- |)" << std::endl;
    std::cout << "               0\\  =  /0" << std::endl;
    std::cout << "           ___/`---'\\___" << std::endl;
    std::cout << "         .' \\|       |# /`." << std::endl;
    std::cout << "        /  \\|||     |||//  \\" << std::endl;
    std::cout << "       /\\   \\|||    |||//   \\" << std::endl;
    std::cout << "       \\ `-.   \\|||  |||//   /" << std::endl;
    std::cout << "        `-.__`-.__\\|||//___.-'" << std::endl;
    std::cout << "                 `=---='" << std::endl;
    std::cout << "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "               佛祖保佑       永无bug" << std::endl;
}

}
} // namespace my_base

#endif