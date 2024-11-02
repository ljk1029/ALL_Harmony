#!/usr/bin/env bash  
  
# 获取系统架构  
ARCH="$(uname -m)"  
  
# 定义颜色变量  
BOLD='\033[1m'  
RED='\033[0;31m'  
WHITE='\033[37m'  # 修改为更通用的白色，原34m是蓝色  
NO_COLOR='\033[0m'  
  
# 打印信息函数  
function info() {  
    echo -e "[${WHITE}${BOLD}INFO${NO_COLOR}] $*" >&2  
}  
  
# 打印错误函数  
function error() {  
    echo -e "[${RED}ERROR${NO_COLOR}] $*" >&2  
}  
  
# 打印红色文本函数  
function red_print() {  
    echo -e "${RED}[RED] $* ${NO_COLOR}" >&2  
}  
  
# 打印系统信息和测试颜色输出  
function debug_log() {  
    local kernel_version="$(uname -r)"  
      
    # 使用 info 函数输出信息  
    info "Realtime kernel version: ${kernel_version}"  
      
    # 使用 error 函数输出错误信息（这里仅为演示，通常不会将相同信息作为错误输出）  
    error "This is not an error, but demonstrating error output with kernel version: ${kernel_version}"  
      
    # 使用 red_print 函数输出红色文本  
    red_print 'This is a red print message.'  
}  
  
# 调用测试函数  
debug_log