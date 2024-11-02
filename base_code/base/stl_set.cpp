#include <iostream>
#include <set>


int set_all() {
    std::set<int> numbers = {3, 1, 4, 1, 5, 9, 2, 6, 5};

    // 获取集合的大小
    std::cout << "size: " << numbers.size() << std::endl;

    // 查找元素是否存在
    if (numbers.find(4) != numbers.end()) {
        std::cout << "4 found in the set." << std::endl;
    } else {
        std::cout << "4 not found in the set." << std::endl;
    }

    // 删除元素
    numbers.erase(4);

    // 使用迭代器遍历 set
    std::cout << "Set elements: ";
    for (std::set<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 清空 set
    numbers.clear();

    // 检查 set 是否为空
    if (numbers.empty()) {
        std::cout << "Set is empty." << std::endl;
    }
    return 0;
}

int main() {
    set_all();
    return 0;
}