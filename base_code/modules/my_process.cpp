/**
 * 文件名: Xxx.c
 * 作者: ljk
 * 创建时间: 2023-12-01
 * 文件描述:
 * 版本: V 1.0.0
 */
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>


namespace my_thread {
// 锁
std::mutex mtx;
std::condition_variable cv;
bool is_data_ready = false;
int shared_data = 0;

// 生产者
void producer(const char *name) {
    while (shared_data < 10) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟生产数据的耗时操作

        std::lock_guard<std::mutex> lock(mtx);
        shared_data++;
        is_data_ready = true;

        std::cout << name << "producer data: " << shared_data << std::endl;

        cv.notify_one(); // 通知消费者线程，数据已准备好
    }
    std::cout << "producer exit" << std::endl;
}

// 消费者
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return is_data_ready; }); // 等待数据准备好的通知

        std::cout << "Consumed data: " << shared_data << std::endl;
        is_data_ready = false;

        if (shared_data >= 10) {
            break; // 当 shared_data 达到 10 时退出循环
        }
    }
    std::cout << "consumer exit" << std::endl;
}

// 创建
void create_thread() {
    std::thread t1(producer, "thread_");
    std::thread t2(consumer);
    t1.detach();         // 分离式
    if (t2.joinable()) { // 判断线程是否可被合并或分离
        t2.join();       // 等待线程结束
    }
    std::cout << "Shared data: " << shared_data << std::endl;
}

} // namespace my_thread

#ifndef MY_MODULES_TEST
int main(int argc, char *argv[])
#else
int process_main(int argc, char *argv[])
#endif
{
    my_thread::create_thread();
    return 0;
}