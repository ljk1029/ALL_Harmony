#include "alg_sort.h"

// test switch
void test_sort_algorithm(int args) {
    int num_len = 13;
    int *number;
    if (sort_tool::genrate_sort(number, num_len)) {
        switch (args) {
        case 1:
            std::cout << "冒泡排序\n";
            sort_tool::bubble_sort(number, num_len);
            break;
        case 2:
            std::cout << "插入排序\n";
            sort_tool::insert_sort(number, num_len);
            break;
        case 3:
            std::cout << "快排序\n";
            sort_tool::quick_sort(number, 0, num_len - 1);
            break;
        case 4:
            std::cout << "选择排序\n";
            sort_tool::select_sort(number, num_len);
            break;
        case 5:
            std::cout << "希尔排序\n";
            sort_tool::shell_sort(number, num_len, 3);
            break;
        case 6:
            std::cout << "并归排序\n";
            sort_tool::merge_sort(number, 0, num_len - 1);
            break;
        case 7:
            std::cout << "堆排序\n";
            sort_tool::heap_sort(number, num_len);
            break;
        case 8:
            std::cout << "基排序\n";
            sort_tool::radix_sort(number, num_len);
            break;

        default:
            break;
        }
        sort_tool::print_sort(number, num_len, 1);
        delete[] number;
    }
}

// 获取参数
char *get_cmd_option(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return nullptr;
}

bool cmd_option_exists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

#define RUN_SORT_3(task_number)                                                                                        \
    if (cases_run == nullptr ||                                                                                        \
        (cases_string.find("f" #task_number) != std::string::npos && cases_string.size() == 3)) {                      \
        std::cout << "sort" #task_number << std::endl;                                                                 \
        test_sort_algorithm(task_number);                                                                                \
    }

// 测试函数入口
int main(int argc, char *argv[]) {
    char *cases_run = get_cmd_option(argv, argv + argc, "-case");
    std::string cases_string;
    if (cases_run) {
        cases_string = cases_run;
    }
    RUN_SORT_3(1)
    RUN_SORT_3(2)
    RUN_SORT_3(3)
    RUN_SORT_3(4)
    RUN_SORT_3(5)
    RUN_SORT_3(6)
    RUN_SORT_3(7)
    RUN_SORT_3(8)
    return 0;
}