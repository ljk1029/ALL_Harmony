/*
 * 文件名: memory.cpp
 * 作者: ljk
 * 创建时间: 2023-09-09
 * 文件描述: 内存操作例程
 *
 * new 和 delete 必须成对使用，new[] 和 delete[] 也必须成对使用
 *
 * std::shared_ptr：允许多个智能指针共享同一块内存，使用引用计数来管理资源的释放。
 * std::unique_ptr：
 * 独占所指向的对象的所有权，确保只有一个智能指针可以访问资源。 std::weak_ptr：
 * 用于协助 std::shared_ptr，不会增加引用计数，避免循环引用。
 */
#include <iostream>
#include <memory>


// 开辟单维数组
int memory_new() {
    int *p1 = new int;
    int *p2 = new int(2);  // 初始化2
    int *p3 = new int[10]; // 开辟10个int
    std::cout << "new int:" << *p1 << std::endl;
    std::cout << "new int(2):" << *p2 << std::endl;
    std::cout << "new int[10]:" << *p3 << std::endl;
    delete p1;
    delete p2;
    delete[] p3;
    return 0;
}

// 开辟多维数组
int memory_news() {
    int n = 3;
    int *arr = new int[n]; // 创建指向 int* 的指针数组

    std::cout << "int[3]:";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}

int main () {
    memory_new();
    memory_news();
    return 0;
}