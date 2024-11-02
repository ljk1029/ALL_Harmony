/**
 * 文件名: my_file.cpp
 * 作者: ljk
 * 创建时间: 2023-12-01
 * 文件描述:
 * 版本: V 1.0.0
 */
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * c++ 17 filesystem
std::filesystem::path：          表示文件系统中的路径。
std::filesystem::current_path()：获取当前工作目录的路径。
std::filesystem::exists(const std::filesystem::path&)：检查文件或目录是否存在。
std::filesystem::is_directory(const path&)：           检查路径是否为目录。
std::filesystem::is_regular_file(const std::filesystem::path&)： 检查路径是否为普通文件。
std::filesystem::create_directory(const std::filesystem::path&)：创建目录。
std::filesystem::create_directories(const path&)：               创建目录，包括中间目录。
std::filesystem::re_move(const path&)：                           删除文件或目录。
std::filesystem::rename(const path&, const std::filesystem::path&)：重命名文件或目录。
std::filesystem::directory_iterator：          用于遍历目录中的文件项。
std::filesystem::recursive_directory_iterator：递归遍历目录中的文件项。
*/

namespace my_file {
using ConstPath = const std::filesystem::path;

/**
 * filesystem
 * 文件夹、路径操作
 */
// 获取当前路径
ConstPath get_path() {
    ConstPath ret = std::filesystem::current_path();
    std::cout << "当前目录为:" << ret << std::endl;
    return ret;
}

bool is_exist(ConstPath path) {
    bool ret = std::filesystem::exists(path);
    std::cout << "目录存在 " << path << ":" << ret << std::endl;
    return ret;
}

bool is_dir(ConstPath path) {
    bool ret = std::filesystem::is_directory(path);
    std::cout << "是目录 " << path << ":" << ret << std::endl;
    return ret;
}

// 是否普通文件，非目录，软连接，设备文件
bool is_file(ConstPath path) {
    bool ret = std::filesystem::is_regular_file(path);
    std::cout << "是文件 " << path << ":" << ret << std::endl;
    return ret;
}

bool create_dir(ConstPath path) {
    bool ret = std::filesystem::create_directory(path);
    std::cout << "创建目录 " << path << ":" << ret << std::endl;
    return ret;
}

bool create_dirs(ConstPath path) {
    bool ret = std::filesystem::create_directories(path);
    std::cout << "创建子目录 " << path << ":" << ret << std::endl;
    return ret;
}

// 只能删除空文件夹
bool re_move(ConstPath path) {
    bool ret = true;
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (std::filesystem::is_directory(entry)) {
            ret = re_move(entry) && ret; // 递归删除子文件夹
        } else {
            ret = std::filesystem::remove(entry) && ret; // 删除文件
        }
    }
    ret = std::filesystem::remove(path) && ret;
    std::cout << "删除目录 " << path << ": " << std::boolalpha << ret << std::endl;
    return ret;
}

// 只能修改单级命名
bool re_name(ConstPath path, ConstPath new_path) {
    bool ret = true;
    try {
        std::filesystem::rename(path, new_path);
    } catch (const std::filesystem::filesystem_error &e) {
        ret = false;
        std::cerr << "重命名或移动文件或目录错误:" << e.what() << std::endl;
    }
    std::cout << "重命名或移动文件或目录 " << path << "->" << new_path << std::endl;
    return ret;
}

// 文件夹遍历
void iterator_dir(ConstPath path) {
    // 遍历本文件夹下文件
    for (const auto &file : std::filesystem::directory_iterator(path)) {
        std::cout << "dir:" << file.path() << std::endl;
    }

    // 遍历本文件下文件和所有子目录下文件夹
    for (const auto &file : std::filesystem::recursive_directory_iterator(path)) {
        std::cout << "file:" << file.path() << std::endl;
    }
}

/**
 * fstream
 * 文件读写操作
 */
// 写
void file_write(const char *&file, const char *text) {
    std::ofstream outputFile(file); // 打开文件，如果不存在则创建新文件
    if (outputFile.is_open()) {     // 检查文件是否成功打开
        outputFile << text;         // 写入内容
        outputFile.close();         // 关闭文件
    }
}

// 读
void file_read(const char *&file) {
    std::ifstream inputFile(file);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::cout << line << std::endl;
        }
        inputFile.close();
    }
}

// 追加
void file_append(const char *&file, const char *text) {
    std::ofstream outputFile(file, std::ios::app);
    if (outputFile.is_open()) { // 检查文件是否成功打开
        outputFile << text;     // 追加内容
        outputFile.close();     // 关闭文件
    }
}

} // namespace my_file



void test_dir() {
    my_file::ConstPath dir_path{"mydir"};
    my_file::ConstPath dirs_path{"mydir/dir1"};
    my_file::ConstPath new_path{"mydir/mk1"};

    my_file::get_path();
    my_file::create_dir(dir_path);
    my_file::create_dirs(dirs_path);
    my_file::is_exist(dir_path);
    my_file::is_file(dir_path);
    my_file::is_dir(dir_path);
    if (my_file::is_exist(dir_path)) {
        std::cout << "重命名目录测试" << dirs_path << "->" << new_path << std::endl;
        my_file::re_name(dirs_path, new_path);
        std::cout << "目录迭代测试" << std::endl;
        my_file::iterator_dir(dir_path);
        std::cout << "目录删除测试" << std::endl;
        my_file::re_move(dir_path);
    }
    my_file::is_exist(dir_path);
}

void test_RW() {
    const char *file{"file.txt"};
    my_file::file_write(file, "123");
    my_file::file_read(file);
    my_file::file_append(file, "456");
    my_file::file_read(file);
}

#ifndef MY_MODULES_TEST
int main(int argc, char *argv[])
#else
int file_main(int argc, char *argv[])
#endif
{
    test_dir();
    test_RW();
    return 0;
}