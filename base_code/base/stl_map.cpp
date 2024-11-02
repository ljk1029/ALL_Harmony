#include <iostream>
#include <map>
#include <string>


// 初始化
int map_make() {
    // 创建一个字符串到整数的映射
    std::map<std::string, int> studentScores;

    // 插入键值对
    studentScores["Alice"] = 95;
    studentScores["Bob"] = 87;
    studentScores["Charlie"] = 92;

    // 使用 insert 方法插入键值对
    studentScores.insert(std::make_pair("David", 88));

    // 访问 map 中的元素
    std::cout << "make map: " << studentScores["Alice"] << std::endl;
    return 0;
}

// 遍历
int map_iterator() {
    std::map<std::string, int> studentScores;
    studentScores["Alice"] = 95;
    studentScores["Bob"] = 87;
    studentScores["Charlie"] = 92;

    // 使用迭代器遍历 map
    std::cout << "iterator map:" << std::endl;
    for (std::map<std::string, int>::iterator it = studentScores.begin(); it != studentScores.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    return 0;
}

// 查找
int map_find() {
    std::map<std::string, int> studentScores;
    studentScores["Alice"] = 95;
    studentScores["Bob"] = 87;
    studentScores["Charlie"] = 92;

    // 查找元素
    std::map<std::string, int>::iterator it = studentScores.find("Bob");
    if (it != studentScores.end()) {
        std::cout << "find map: " << it->second << std::endl;
    } else {
        std::cout << "Bob not found." << std::endl;
    }
    return 0;
}

// 删除
int map_erase() {
    std::map<std::string, int> studentScores;
    studentScores["Alice"] = 95;
    studentScores["Bob"] = 87;
    studentScores["Charlie"] = 92;

    // 删除元素
    studentScores.erase("Bob");

    // 遍历 map 并输出剩余元素
    std::cout << "erase:" << std::endl;
    for (const auto &pair : studentScores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    return 0;
}

int main() {
    map_make();
    map_iterator();
    map_find();
    map_erase();
    return 0;
}