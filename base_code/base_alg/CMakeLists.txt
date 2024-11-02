cmake_minimum_required(VERSION 3.16)
project(mytool)

# 添加编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 设置C++版本为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET1 "my_list")
set(TARGET2 "my_tree")
set(TARGET3 "my_search")
set(TARGET4 "my_sort")


# 添加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

# 生成可执行文件
add_executable(${TARGET1} ${TARGET1}.cpp)
add_executable(${TARGET2} ${TARGET2}.cpp)
add_executable(${TARGET3} ${TARGET3}.cpp)
add_executable(${TARGET4} ${TARGET4}.cpp)

# 设置输出路径
set_target_properties(
    ${TARGET1} 
    ${TARGET2} 
    ${TARGET3} 
    ${TARGET4} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

