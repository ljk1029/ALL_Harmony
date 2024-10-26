# 设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(common)

# 默认的输出路径
set(DEFAULT_BIN_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../bin")

# 与1.0.27版本的生成物重名了
#add_subdirectory(libusb-1.0.0) 
add_subdirectory(libusb-1.0.27)
add_subdirectory(hidapi)








