cmake_minimum_required(VERSION 3.16)
project(my_module)

# 添加编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 设置C++版本
#set(CMAKE_CXX_STANDARD 11)
# 设置C++版本为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGETS 
    modules_atomic 
    modules_file 
    modules_mutex 
    modules_signum 
    modules_thread 
    modules_time
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

foreach(TARGET ${TARGETS})
    add_executable(
        ${TARGET} 
        ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET}.cpp
    )
    set_target_properties(
        ${TARGET} 
        PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/../bin
    )
endforeach()

target_link_libraries(modules_thread -lpthread)


