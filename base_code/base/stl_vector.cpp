#include <iostream>
#include <vector>


// 打印
void printVector(std::vector<int> numbers, std::string title) {
    std::cout << "(" << title << ")" << std::endl;
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// 重载打印
void printVector(std::vector<int> numbers, std::string title, char bracket) {
    if (bracket == '(' || bracket == ')') {
        std::cout << "(" << title << ")" << std::endl;
    } else if (bracket == '[' || bracket == ']') {
        std::cout << "[" << title << "]" << std::endl;
    } else {
        std::cout << title << std::endl;
    }

    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// verctor 添加删除
int verctor_make() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 添加
    numbers.push_back(6);
    printVector(numbers, "push_back test", '(');

    // 删除
    numbers.pop_back();
    printVector(numbers, "pop_back test", '(');

    return 0;
}

// vector 访问
int verctor_at() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 获取 vector 的大小
    std::cout << "size: " << numbers.size() << std::endl;

    // 访问 vector 中的元素
    std::cout << "element: " << numbers[0] << std::endl;
    std::cout << "element: " << numbers.at(1) << std::endl;
    std::cout << "element: " << numbers.back() << std::endl;
    return 0;
}

// 删除
int verctor_erase() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 删除指定位置的元素,第2个
    numbers.erase(numbers.begin() + 1);
    printVector(numbers, "erase test", '(');

    // 插入 在第3个元素前面插入10;
    numbers.insert(numbers.begin() + 2, 10);
    printVector(numbers, "insert test", '(');

    // 清空
    numbers.clear();
    printVector(numbers, "clear test", '(');
    std::cout << "size: " << numbers.size() << std::endl;

    // 检查是否为空
    if (numbers.empty()) {
        std::cout << "Vector is empty." << std::endl;
    }
    return 0;
}

// 遍历
int verctor_iterator() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用迭代器遍历 vector
    std::cout << "Vector iterator: ";
    for (std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    verctor_make();
    verctor_at();
    verctor_erase();
    verctor_iterator();
    return 0;
}
