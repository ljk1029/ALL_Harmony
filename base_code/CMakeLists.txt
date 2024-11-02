cmake_minimum_required(VERSION 3.16)
project(mybase)

# 添加编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 设置C++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将配置文件内容读取到一个变量中
file(READ config.ini configContents)

# 定义一个函数，用于从配置内容中解析特定节下的设置
function(parse_ini_section section key var)
    string(REGEX MATCH "\\[${section}\\][^\[]*" sectionContent "${configContents}")
    string(REGEX MATCH "${key}=([A-Za-z0-9]+)" keyValue "${sectionContent}")
    if(NOT "${keyValue}" STREQUAL "")
        string(REPLACE "${key}=" "" value "${keyValue}")
        set(${var} ${value} PARENT_SCOPE)
    endif()
endfunction()

# 解析配置文件下参数
parse_ini_section("Build" "Debug" BUILD_DEBUG)
parse_ini_section("Function" "USE_TEST" FUNCTION_USE_TEST)
parse_ini_section("Function" "USE_FUN"  FUNCTION_USE_FUN)

# 打印解析结果验证
message("BUILD_DEBUG: ${BUILD_DEBUG}")
message("FUNCTION_USE_TES: ${FUNCTION_USE_TEST}")
message("FUNCTION_USE_FUN: ${FUNCTION_USE_FUN}")

# 设置编译选项, 与CMAKE_CXX_FLAGS是重复的
if (BUILD_DEBUG)
    message("Debug mode enabled")
    set(CMAKE_BUILD_TYPE Debug)
else()
    message("Release mode enabled")
    set(CMAKE_BUILD_TYPE Release)
endif()

# 功能模块编译开关
if(FUNCTION_USE_FUN)    
add_subdirectory(modules)
add_subdirectory(base_alg)
endif()
