/*
 * 文件名: my_io.cpp
 * 作者: ljk
 * 创建时间: 2023-09-09
 * 文件描述: 调试例程
 */
#include <iostream>
#include <fstream>
#include <string>



// 输出测试
int io_cout() {
    int number = 18;
    std::string name = "lmy";
    std::cout << "Hello World\n";
    std::cout << "Hello World" << std::endl;
    std::cout << number << "," << name << std::endl;
    return 0;
}

// 输入测试
int io_cin() {
    int number;
    std::string name;

    std::cout << "请输入一个整数:";
    std::cin >> number;
    std::cout << "请输入一个字符串:";
    std::cin.ignore(); //忽略回车
    getline(std::cin, name);

    std::cout << "你输入的整数是: " << number << std::endl;
    std::cout << "你输入的字符串是: " << name << std::endl;
    return 0;
}

// 引用测试
int value_quote() {
    std::cout << "[引用测试]" << std::endl;

    int my_value = 42;
    int &my_quote = my_value;

    std::cout << "value: " << my_value << " & " << &my_value << std::endl;
    std::cout << "quote: " << my_quote << " & " << &my_quote << std::endl;
    return 0;
}

int io_getline() {
    std::string line;

    // 从标准输入读取一行文本
    std::cout << "请输入一个字符串:";
    std::getline(std::cin, line);
    // 输出读取的行
    std::cout << "读取的行是：" << line << std::endl;

    char delimiter = '#'; // 指定分隔符
    std::cout << "请输入文本，使用 '#' 作为分隔符：" << std::endl;
    while (std::getline(std::cin, line, delimiter)) {
        std::cout << "读取的文本是：" << line << std::endl;
        break;
    }
    return 0;
}

int io_fstream() {
    {
        // 打开文件用于写入，并清空文件内容
        std::ofstream file("example.txt", std::ios::out | std::ios::trunc); 
        if (file.is_open()) {
            file << "ASCII 文本数据\n"; // 写入一行文本
            file.close(); // 关闭文件
        } else {
            std::cerr << "无法打开文件进行写入" << std::endl;
            return 1;
        }
    }

    {
        // 打开文件用于读取
        std::ifstream file("example.txt", std::ios::in); 
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::cout << "读取的文本行：" << line << std::endl;
            }
            file.close(); // 关闭文件
        } else {
            std::cerr << "无法打开文件进行读取" << std::endl;
            return 1;
        }
    }
    return 0;
}

int io_fstream_bin() {
    {
        int number = 12345; // 打开文件用于二进制写入，并清空文件内容
        std::ofstream file("example.bin", std::ios::out | std::ios::binary | std::ios::trunc); 
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&number), sizeof(number)); // 写入二进制数据
            file.close(); // 关闭文件
        } else {
            std::cerr << "无法打开文件进行二进制写入" << std::endl;
            return 1;
        }
    }

    {
        int number;// 打开文件用于二进制读取
        std::ifstream file("example.bin", std::ios::in | std::ios::binary); 
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&number), sizeof(number)); // 读取二进制数据
            std::cout << "读取的二进制数据：" << number << std::endl;
            file.close(); // 关闭文件
        } else {
            std::cerr << "无法打开文件进行二进制读取" << std::endl;
            return 1;
        }
    }
    return 0;
}

int main() {
    io_cout();
    io_cin();
    io_getline();

    value_quote();

    io_fstream();
    io_fstream_bin();
    return 0;
}


