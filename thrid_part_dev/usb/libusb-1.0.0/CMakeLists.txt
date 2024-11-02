# 设置版本
cmake_minimum_required(VERSION 3.4.1)
project(myapp)

# 设置目录 - 以此目录为基准设置下面编译的头，源，库位置、CMakeLists.txt所在目录
set(CURRENT_DIR ${CMAKE_SOURCE_DIR})

# 设置编译器
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -O0 -g")

# 设置目标名称
set(TARGETS "lsusb" "dpfp" "dpfp_threaded")

# 添加头文件搜索路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libusb/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libusb/os/)

# 包含源文件，aux_source_directory将目录所有源文件自动加入
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/libusb/    SOURCE_COMMON)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/libusb/os/ SOURCE_COMMON_OS)

# 查找线程库
find_package(Threads REQUIRED)

# 定义一个函数来简化可执行文件和库的添加
function(add_my_executable target)
    add_executable(${target}
        ${CMAKE_CURRENT_SOURCE_DIR}/examples/${target}.c
        ${SOURCE_COMMON}
        ${SOURCE_COMMON_OS}
    )
    target_link_libraries(${target}
        Threads::Threads
        # -ludev  # 如果需要链接udev库，可以取消注释
    )
    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
    )
endfunction()

# 为每个目标调用函数
foreach(target ${TARGETS})
    add_my_executable(${target})
endforeach()