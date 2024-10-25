# 设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(mysqlite)

# 设置目录-以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录 
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}) 
# 设置编译器 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") 
# 生成gdb的调试信息和不进行代码优化 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g") 
# 设置输出目标
set(TARGET "my_sqlite")

# 添加头文件搜索路径
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/code/include/ 
)

# 包含源文件
aux_source_directory(
    ${CMAKE_CURRENT_SOURCE_DIR}/code/src  SOURCE_COMMON
) 

# 生成可执行文件
add_executable(${TARGET} 
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3_main.c
    ${SOURCE_COMMON} 
) 

# 链接库，确保链接了 pthread
target_link_libraries(${TARGET} PRIVATE pthread dl)

# 编译静态库
add_library( 
    sqlite3
    STATIC
    #SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/sqlite3_main.c
    ${SOURCE_COMMON}
)

target_link_libraries(sqlite3 PRIVATE pthread dl)

message(STATUS "Custom binary directory: ${BIN_OUTPUT_PATH}")

# 设置输出路径
set_target_properties(
    ${TARGET} sqlite3
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH} # 设置动态库运行时的输出目录。
    LIBRARY_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH} # 设置动态库本身的输出目录
    ARCHIVE_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH} # 设置静态库的输出目录
)










