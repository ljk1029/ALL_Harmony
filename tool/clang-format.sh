#!/usr/bin/env bash

# 定义要使用的样式
CLANG_FORMAT_STYLE="
BasedOnStyle: llvm
IndentWidth:   4
TabWidth:      4
UseTab:        Never

# 对于访问修饰符的偏移量
AccessModifierOffset: -4

# 设置了每行最大字符个数
ColumnLimit: 120

# 不对头文件进行自动排序
SortIncludes: false"

# 将样式写入 .clang-format 文件
echo "$CLANG_FORMAT_STYLE" > .clang-format

# 循环查找并格式化每个源文件
for file in $(find . -type f \( -iname '*.cpp' -o -iname '*.h' -o -iname '*.cc' \)); 
do
    echo "正在格式化: $file"
    clang-format -i -style=file "$file"
    if [ $? -eq 0 ]; then
        echo "成功格式化: $file"
    else
        echo "格式化失败: $file"
    fi
done

# 打印完成消息
echo "所有文件格式化完成。"