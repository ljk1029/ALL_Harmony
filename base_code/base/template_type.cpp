#include <iostream>

/**
 * 下列typename 和 class一样
 */
// 定义一个函数模板，用于比较两个值的大小
// 通用比较函数模板
template <typename T> 
int template_max(const T &a, const T &b) {
    std::cout << a << " compare " << b << std::endl;
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

// 字符串专用比较函数模板
template <> int 
template_max(const std::string &a, const std::string &b) {
    std::cout << a << " compare " << b << std::endl;
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

// 递归终止函数
void template_print() {
    std::cout << std::endl;// 换行
}

// 变参模板函数，用于打印不定数量参数
template <typename T, typename... Args> 
void template_print(const T &first_arg, const Args &...args) {
    std::cout << first_arg << ", "; // 打印当前参数
    template_print(args...);         // 递归调用，打印剩余的参数
}

int type_test() {
    int a = template_max(1, 1);
    int b = template_max(2.1, 2.0);
    int c = template_max(std::string("apple"), std::string("banana"));
    template_print("templateMax result:", a, b, c);
    return true;
}

// 测试用例
int main(int argc, char *argv[]) {
    type_test();
    return 0;
}
