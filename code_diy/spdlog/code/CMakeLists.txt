#cmake_minimum_required(VERSION 3.12)
cmake_minimum_required(VERSION 3.4.1)
project(Spdloglib)

set(CMAKE_CXX_STANDARD 11)

# 添加编译选项，启用调试信息和生成调试符号
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 添加链接选项，生成调试信息
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")

include_directories(
    include
    include/adapter
)

add_library(
    spdlog
    STATIC
    spdloglib.cpp
    adapter/BussinessLogger.cpp
    adapter/LoggerContainer.cpp
    adapter/ManageLogger.cpp
    adapter/ModelLogger.cpp
    adapter/ConsoleLoggerFactory.cpp
    adapter/FileLoggerFactory.cpp
)

