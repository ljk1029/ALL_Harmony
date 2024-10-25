# 设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(myspdlog)

# 设置目录-以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录 
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}) 
# 设置编译器 
set(CMAKE_CXX_STANDARD 11)
# 添加编译选项，启用调试信息和生成调试符号
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# 添加链接选项，生成调试信息
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")
# 设置输出目标
set(TARGET "my_spdlog")
set(CODE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/code")

include_directories(
    ${CODE_PATH}/
    ${CODE_PATH}/include/
    ${CODE_PATH}/include/adapter/
)

add_library(
    spdlog
    STATIC
    ${CODE_PATH}/spdloglib.cpp
    ${CODE_PATH}/adapter/BussinessLogger.cpp
    ${CODE_PATH}/adapter/LoggerContainer.cpp
    ${CODE_PATH}/adapter/ManageLogger.cpp
    ${CODE_PATH}/adapter/ModelLogger.cpp
    ${CODE_PATH}/adapter/ConsoleLoggerFactory.cpp
    ${CODE_PATH}/adapter/FileLoggerFactory.cpp
)

# 生成可执行文件
add_executable(
    ${TARGET} 
    ${CMAKE_CURRENT_SOURCE_DIR}/spdlog_main.c
    ${CODE_PATH}/spdloglib.cpp
    ${CODE_PATH}/adapter/BussinessLogger.cpp
    ${CODE_PATH}/adapter/LoggerContainer.cpp
    ${CODE_PATH}/adapter/ManageLogger.cpp
    ${CODE_PATH}/adapter/ModelLogger.cpp
    ${CODE_PATH}/adapter/ConsoleLoggerFactory.cpp
    ${CODE_PATH}/adapter/FileLoggerFactory.cpp 
) 

message(STATUS "Custom binary directory: ${BIN_OUTPUT_PATH}")

# 设置输出路径
set_target_properties(
    ${TARGET} spdlog
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH} # 设置动态库运行时的输出目录。
    LIBRARY_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH} # 设置动态库本身的输出目录
    ARCHIVE_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH} # 设置静态库的输出目录
)







