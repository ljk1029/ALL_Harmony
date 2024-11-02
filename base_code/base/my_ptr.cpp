/*
 * 文件名: my_ptr.cpp
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


// 智能指针
int smart_ptr() {
    // 使用 std::shared_ptr
    std::shared_ptr<int> shared_ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> shared_ptr2 = shared_ptr1; // 共享所有权

    std::cout << "shared_ptr:" << *shared_ptr1 << std::endl;
    std::cout << "shared_ptr:" << *shared_ptr2 << std::endl;

    // 使用 std::unique_ptr
    std::unique_ptr<int> unique_ptr = std::make_unique<int>(99);
    // std::unique_ptr<int> unique_ptr2 = unique_ptr; //
    // 试图复制会引发编译错误，因为它是独占所有权的

    std::cout << "unique_ptr:" << *unique_ptr << std::endl;

    // 在作用域结束时，智能指针会自动释放资源，不需要手动调用 delete
    return 0;
}

// 多维智能指针
int smart_ptr_get() {
    const size_t n = 10;
    std::shared_ptr<int[]> shared_ptr1(new int[n]);

    // 初始化数组
    for (size_t i = 0; i < n; ++i) {
        shared_ptr1.get()[i] = static_cast<int>(i); // 或者 *(shared_ptr1.get() + i)
    }

    // 打印测试
    for (size_t i = 0; i < n; ++i) {
        std::cout << shared_ptr1[i] << " ";
        std::cout << shared_ptr1.get()[i] << " ";
    }
    std::cout << std::endl; // Should
    return 0;
}


int main() {
    smart_ptr();
    smart_ptr_get();
    return 0;
}


