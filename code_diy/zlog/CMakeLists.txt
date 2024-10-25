#设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(myzlog)

#设置目录-以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录 
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}) 
#设置编译器 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") 
#生成gdb的调试信息和不进行代码优化 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g") 

set(TARGET "my_zlog")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/code/src/
)

#包含源文件 ，aux_source_directory将目录所有源文件自动加入 
aux_source_directory(
    ${CMAKE_CURRENT_SOURCE_DIR}/code/src/ SOURCE_COMMON
) 


#生成可执行文件
add_executable(${TARGET} 
    ${CMAKE_CURRENT_SOURCE_DIR}/zlog_main.c
    ${SOURCE_COMMON}  
) 

# 链接库，确保链接了 pthread
target_link_libraries(
    ${TARGET} 
    PRIVATE 
    pthread
)

# 设置输出路径
set_target_properties(
    ${TARGET} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH}
)

# 防止bin被zlog.conf拷贝成文件
if(NOT EXISTS ${BIN_OUTPUT_PATH})
    file(MAKE_DIRECTORY ${BIN_OUTPUT_PATH})
endif()

set(zlog_BINARY_DIR ${BIN_OUTPUT_PATH})

# 将头文件复制到输出目录
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/zlog.conf 
    ${BIN_OUTPUT_PATH}/zlog.conf COPYONLY
)







