cmake_minimum_required(VERSION 3.16)
project(mygtest)

set(TARGET "my_gtest")

# 添加头文件搜索路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/code
) 

# 添加源文件
file(GLOB_RECURSE GTEST_SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest_main.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/code/gtest-all.cc
)

# 生成可执行文件
add_executable(
    ${TARGET}
    ${GTEST_SRC_FILES}
)

target_link_libraries(
    ${TARGET} 
    -lpthread
)    

# 设置输出路径
set_target_properties(
    ${TARGET} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH}
)