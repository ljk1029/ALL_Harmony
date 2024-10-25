# 设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(myspdlog)

# 设置目录-以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录 
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}) 

set(CMAKE_CXX_STANDARD 14)
# 添加编译选项，启用调试信息和生成调试符号
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
# 添加链接选项，生成调试信息
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")

set(TARGET "my_protobuf")

# 添加头文件
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

# 添加源文件 
aux_source_directory(
    ${CMAKE_CURRENT_SOURCE_DIR}/  SOURCE_API
) 

# 生成可执行文件
add_executable(
    ${TARGET}  
    ${SOURCE_API}
) 

# 链接我们需要的库，如lpthread系统库 
target_link_libraries(${TARGET} 
    -lprotobuf
    -lpthread 
) 

message(STATUS "Custom binary directory: ${BIN_OUTPUT_PATH}")

# 设置输出路径
set_target_properties(
    ${TARGET} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_PATH}
)






