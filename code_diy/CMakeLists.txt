# 设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(common)

# 默认的输出路径
set(DEFAULT_BIN_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../bin")

# 从命令行参数设置输出路径，如果没有提供参数，则使用默认值
# cmake .. -DBUILD_PATH=/path/bin
if(DEFINED BUILD_PATH)
    set(BIN_OUTPUT_PATH ${BUILD_PATH})
else()
    set(BIN_OUTPUT_PATH ${DEFAULT_BIN_OUTPUT_PATH})
endif()

add_subdirectory(base64)
add_subdirectory(cjson)
add_subdirectory(sqlite3)
add_subdirectory(spdlog)
add_subdirectory(gtest)
#add_subdirectory(protobuf)
add_subdirectory(zlog)






