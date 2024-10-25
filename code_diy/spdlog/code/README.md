## 日志修改说明
### (1)日志格式修改
./Spdloglib/include/adapter/ManageLogger.h下  
#define LOG_PRINT_COMMON_FORMATTING "%Y-%m-%d %H:%M:%S.%e %P-%t/%n %L/%v"  

%Y-%m-%d %H:%M:%S.%e  日期时间  
%P-%t/%n  进程 线程 日志模块名  
%L/%v  日志等级和日志全部内容  


./Spdloglib/include/spdlog/details/pattern_formatter-inl.h下  
都有什么格式解释  
SPDLOG_INLINE void pattern_formatter::handle_flag_(char flag, details::padding_info padding)  

### (2) 内容修改  
./Spdloglib/adapter/ModelLogger.cpp下  
设置log内容格式  
std::string ModelLogger::formatMsg(const std::string &tag, const std::string &msg){  
    return tag + ": " + msg;  
}  

### (3) 日志默认名称修改
./Spdloglib/scr/adapter/LoggerContainer.cpp下  
ModelLogger* LoggerContainer::getLogger() {  
    std::string modelName = "IDPS";  

## 接口说明  
### （1）设置是否打印    
void set_console_logger(bool consoleFlag);  
设置是否写文件，  
void set_file_write_logger(bool fileWriteFlag);  
设置文件路径，单个日志文件大小，文件滚动大小，  
void set_file_logger(const char *filePath, int max_file_size, int max_files);  
设置文件路径，  
void set_file_write_path(const char *filePath);  
设置日志等级，  
void set_level(int level);  
写入日志模块名，日志内容，  
void log_v(const char *tag, const char *msg);  


### （2）子模块日志等级设置，  
void set_model_level(const char *modelName, int level);  
void set_model_logger(const char *modelName, bool flag);  
子模块写入文件名，模块名，日志内容，  
void model_log_v(const char *modelName, const char *tag, const char *msg);  