# 设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(mycjson)

# 设置目录-以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录 
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}) 
# 设置编译器 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") 
# 生成gdb的调试信息和不进行代码优化 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g") 
# 设置输出目标
set(TARGET "my_cjson")

# 添加头文件搜索路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/code/ 
)

# 包含源文件
aux_source_directory(
    ${CMAKE_CURRENT_SOURCE_DIR}/code/  SOURCE_COMMON
) 

# 生成可执行文件
add_executable(${TARGET} 
    ${CMAKE_CURRENT_SOURCE_DIR}/cjson_main.c
    ${SOURCE_COMMON} 
) 

message(STATUS "Custom binary directory: ${BIN_OUTPUT_PATH}")

# 设置输出路径
set_target_properties(
    ${TARGET} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH}
)







