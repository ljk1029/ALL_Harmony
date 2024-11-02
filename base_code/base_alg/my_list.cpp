#include "alg_list.h"

using namespace my_list;

// 链表测试
void test_list_init() {
    my_list::linked_list<int> list;
    list.print_list("test1-1");
    list.clear_list();
    list.print_list("test1-2");
}

void test_list_add() {
    my_list::linked_list<int> list;
    int data = 42;
    int key  = 1;

    list.add_list(key, data);
    list.print_list("test2-1, Add");

    list.add_list(key, data); // Adding the same key again should fail

    list.del_list(key);
    list.print_list("test2-2, Del");

    list.del_list(key); // Deleting a non-existent key should fail
    list.print_list("test2-3, Del");
}

void test_list_find() {
    my_list::linked_list<std::string> list;
    std::string data1 = "42";
    std::string data2 = "100";
    int key1 = 1;
    int key2 = 2;

    list.add_list(key1, data1);
    list.add_list(key2, data2);

    std::string foundData1;
    std::string foundData2;

    list.find_list(key1, foundData1);
    list.find_list(key2, foundData2);

    std::cout << foundData1 << std::endl;
    std::cout << foundData2 << std::endl;
}

void test_list_thread() {
    my_list::linked_list<std::string> list;
    std::vector<std::thread> threads;
    const int num_threads = 10;
    const int num_adds    = 100;

    // 启动多个线程进行添加操作
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([&list]() {
            for (int j = 0; j < num_adds; j++) {
                std::string data = "String_" + std::to_string(j);
                list.add_list(j, data);
            }
        });
    }

    // list.print();

    // 等待所有线程完成
    for (auto &thread : threads) {
        thread.join();
    }

    std::cout << list.get_list_size() << std::endl;

    // 启动多个线程进行删除操作
    threads.clear();
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([&list, &i]() {
            for (int j = 0; j < num_adds; j++) {
                list.del_list(j);
            }
        });
    }

    // 等待所有线程完成
    for (auto &thread : threads) {
        thread.join();
    }

    std::cout << list.get_list_size() << std::endl;
}

void test_list_clear() {
    my_list::linked_list<std::string> list(10, true);
    const int num_adds = 12;
    for (int i = 0; i < num_adds; i++) {
        std::string data = "String_" + std::to_string(i);
        list.add_list(i, data);
    }
    list.print_list("-");

    list.clear_list();
    list.print_list("clear");

    for (int i = 0; i < num_adds; i++) {
        std::string data = "String_" + std::to_string(i);
        list.add_list(i, data);
    }
    list.print_list("add");
    std::cout << list.get_list_size() << std::endl;

    for (int i = 0; i < num_adds; i++) {
        if (i % 2) {
            list.del_list(i);
        }
        std::string data = "String_" + std::to_string(i);
        list.add_list(i + 8, data);
    }
    list.print_list("change");
}

static int idx = 0;
// 测试回调
#define print_func(callback) do { \
    std::puts("\033[1;32m"); \
    std::cout << "======[" << #callback << " function]======"; \
    std::puts("\033[0m"); \
    callback(); \
    std::cout << "**[" << idx++ << "-" << #callback << " function]**********\n\n"; \
} while(0)


// 测试函数入口
int main(int argc, char *argv[]) {
    print_func(test_list_init);
    print_func(test_list_add);
    print_func(test_list_find);
    print_func(test_list_thread);
    print_func(test_list_clear);
    return 0;
}
