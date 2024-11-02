#ifndef _LOG_TOOL_H__
#define _LOG_TOOL_H__
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <mutex>  

namespace my_base{
namespace my_log {

// 字体颜色
#define SET_CLR_BLACK   "\033[1;30m"
#define SET_CLR_RED     "\033[1;31m"
#define SET_CLR_GREEN   "\033[1;32m"
#define SET_CLR_YELLOW  "\033[1;33m"
#define SET_CLR_BLUE    "\033[1;34m"
#define SET_CLR_MAGENTA "\033[1;35m"
#define SET_CLR_CYAN    "\033[1;36m"
#define SET_CLR_WHITE   "\033[1;37m"
#define SET_CLR_RESET   "\033[0m"

// 背景颜色
#define SET_CLR_RED_BG   "\033[1;41m"
#define SET_CLR_GREEN_BG "\033[1;42m"

// 设置输出窗口颜色
int log_set_console_colour(const char* colour) {
    return std::puts(colour);
}

// 设置黄色
int log_console_yellow_test() {
    log_set_console_colour(SET_CLR_YELLOW);
    std::puts("HelloWorld:yellow");
    log_set_console_colour(SET_CLR_RESET);
    return false;
}

// 设置红色
int log_console_red_test() {
    log_set_console_colour(SET_CLR_RED);
    std::puts("HelloWorld:red");
    log_set_console_colour(SET_CLR_RESET);
    return false;
}

// 设置背景色
int log_console_bg_test() {
    log_set_console_colour(SET_CLR_RED_BG);
    std::puts("HelloWorld:red");
    log_set_console_colour(SET_CLR_RESET); 
    return false;
}



// log定义等级
enum class LogLevel {  
    INFO,  
    WARN,  
    ERROR,  
    DEBUG  
};  

// log等级转换字符
std::string LogLevelToString(LogLevel level) {  
    switch (level) {  
        case LogLevel::INFO: return "INFO";  
        case LogLevel::WARN: return "WARN";  
        case LogLevel::ERROR: return "ERROR";  
        case LogLevel::DEBUG: return "DEBUG";  
        default: return "UNKNOWN";  
    }  
}  
  
// 获取当前时间字符串  
std::string GetTimeNow() {  
    auto now = std::chrono::system_clock::now();  
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);  
    std::tm tm_now = *std::localtime(&time_now);  
    char buffer[20]; // 大小足够存储 "YYYY-MM-DD HH:MM:SS"
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_now);

    return std::string(buffer);  
}  
  
// 获取当前线程ID字符串  
std::string GetThreadId() {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    return ss.str();
}
  
// 获取当前进程ID  
pid_t GetProcessId() {  
    return getpid();  
}  
  
// LogConfig 结构体，包含日志配置  
struct LogConfig {  
    std::string log_file_path = "default.log";  
    bool log_to_console = true;  
    bool log_to_file = false;  
  
    // 静态 LogConfig 实例，用于全局访问  
    static LogConfig& instance() {  
        static LogConfig config; // 静态局部变量，保证只初始化一次  
        return config;  
    }  
  
    // 初始化函数，用于设置自定义配置  
    void init(
        const std::string& log_file_path_ = "", 
        bool log_to_console_ = true, 
        bool log_to_file_ = false) {  
        if (!log_file_path_.empty()) {  
            log_file_path = log_file_path_;  
        }  
        log_to_console = log_to_console_;  
        log_to_file = log_to_file_;  
    }  
}; 

// 全局互斥锁，用于保护日志输出
std::mutex global_log_mutex;  

// 多参数日志  
template <typename... Args>  
void log(LogLevel level, const Args&... args) {  
    const std::string time_now  = GetTimeNow();  
    const std::string thread_id = GetThreadId();  
    const pid_t process_id = GetProcessId();  
    LogConfig& config = LogConfig::instance();  
  
    std::lock_guard<std::mutex> lock(global_log_mutex);
    std::ostringstream oss;
    oss << time_now 
        << " Process ID: " << process_id 
        << " Thread ID: " << thread_id << " " 
        << LogLevelToString(level) << ": ";
    // 使用折叠表达式来展开参数包
    (oss << ... << args);
    std::string log_message = oss.str();

    // 打印日志到控制台  
    if (config.log_to_console) {  
        std::cout << log_message << std::endl;  
    }  
  
    // 写入日志到文件  
    if (config.log_to_file) {  
        std::ofstream file;  
        try {  
            file.open(config.log_file_path, std::ios::app);  
            if (file.is_open()) {  
                file << log_message << std::endl;  
                file.close();  
            } else {  
                throw std::runtime_error("无法打开日志文件");  
            }  
        } catch (const std::exception& e) {  
            std::cerr << e.what() << std::endl;  
        } catch (...) {  
            std::cerr << "未知错误" << std::endl;  
        }  
    }  
}  

} // namespace log_tool
}

#endif