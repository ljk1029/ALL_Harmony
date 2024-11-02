# 设置版本 
cmake_minimum_required(VERSION 3.4.1) 
project(myapp)

# 设置目录-以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录 
set(CURRENT_DIR ${CMAKE_SOURCE_DIR}) 
# 设置编译器 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99") 
# 生成gdb的调试信息和不进行代码优化 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g") 

set(TARGET1 "dpfp")
set(TARGET2 "fxload")
set(TARGET3 "listdevs")
set(TARGET4 "sam3u_benchmark")
set(TARGET5 "testlibusb")
set(TARGET6 "init_context")
set(TARGET7 "macos")
set(TARGET8 "set_option")
set(TARGET9 "stress_mt")
set(TARGET10 "stress")
set(TARGET11 "testlib")
set(TARGET12 "umockdev")


# 添加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libusb/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libusb/os/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libusb/tests)

# 包含源文件，aux_source_directory将目录所有源文件自动加入 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/libusb/    SOURCE_COMMON) 
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/libusb/os/ SOURCE_COMMON_OS) 


# 生成可执行文件，
add_executable(${TARGET1} 
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/${TARGET1}.c 
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 

# 链接我们需要的库，
target_link_libraries(${TARGET1} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET2} 
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/${TARGET2}.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/ezusb.c 
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 

target_link_libraries(${TARGET2} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET3} 
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/${TARGET3}.c 
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 

target_link_libraries(${TARGET3} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET4} 
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/${TARGET4}.c 
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 

target_link_libraries(${TARGET4} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET5} 
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/${TARGET5}.c 
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 

target_link_libraries(${TARGET5} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET6} 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TARGET6}.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/testlib.c 
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 
target_link_libraries(${TARGET6} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET8} 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TARGET8}.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/testlib.c
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 
target_link_libraries(${TARGET8} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET9} 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TARGET9}.c 
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 
target_link_libraries(${TARGET9} 
    -lpthread
    -ludev 
) 

add_executable(${TARGET10} 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TARGET10}.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/testlib.c
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
) 
target_link_libraries(${TARGET10} 
    -lpthread
    -ludev 
) 

add_library(usb
    STATIC  
    ${SOURCE_COMMON}
    ${SOURCE_COMMON_OS}
)

# 设置输出路径
set_target_properties(
    usb
    ${TARGET1} ${TARGET2} ${TARGET3} ${TARGET4} ${TARGET5} 
    ${TARGET6} ${TARGET8} ${TARGET9} ${TARGET10}    
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
)





