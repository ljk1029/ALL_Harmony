# Makefile

# 定义编译器
CXX := g++

# 定义编译器标志
CXXFLAGS := -std=gnu++17 -Wall

# 定义目标可执行文件名
TARGET := main

# 定义编译的源文件列表
SRCS := log_main.cpp

# 定义对象文件列表，由源文件列表 SRCS 导出（替换 .cpp 为 .o）
OBJS := $(SRCS:.cpp=.o)

# 默认目标：链接所有的对象文件并生成最终可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 定义伪目标；不对应文件名
.PHONY: clean

# 清理构建文件的目标
clean:
	rm -f $(TARGET) $(OBJS)