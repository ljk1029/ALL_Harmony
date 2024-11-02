#设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(myapp)

#设置目录-以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录 
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}) 
#设置编译器 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") 
#生成gdb的调试信息和不进行代码优化 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g") 

set(TARGET1 "hid_linux")
set(TARGET2 "hid_libusb")

# 添加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/hidapi)

# 生成hid linux
add_executable(
    ${TARGET1}   
    ${CMAKE_CURRENT_SOURCE_DIR}/hidtest.c
    ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET1}.c
)

# 链接我们需要的库，
target_link_libraries(
    ${TARGET1}
    -lpthread
    -ludev 
) 

# 生成hid libusb
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libusb-1.0.27/libusb)
add_executable(
    ${TARGET2}
    ${CMAKE_CURRENT_SOURCE_DIR}/hidtest.c   
    ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET2}.c
)

# 链接我们需要的库，
target_link_libraries(${TARGET2}
    -lpthread
    ${CMAKE_CURRENT_SOURCE_DIR}/../bin/libusb.a
    -ludev 
) 

# 注册
install(
    TARGETS ${TARGET1} ${TARGET2}
    RUNTIME 
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin
)

# 生成路径
set_target_properties(
    ${TARGET1} ${TARGET2} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
)



