#include <iostream>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>
// unix
#include <unistd.h>
#include <vector>


namespace my_thread {
/**
 * atomic 原子操作
 */
namespace my_atomic {
// 原子布尔变量，用于指示数据是否已准备好
std::atomic_bool data_ready(false);
int shared_data = 0;
// 生产者线程
void producer_atomic() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟生产数据的耗时操作
    shared_data = 42;                                     // 生产数据
    std::cout << "Producer: Data produced.\n";
    data_ready.store(true); // 设置数据已准备好
}

// 消费者线程
void consumer_atomic() {
    while (!data_ready.load()) {                                     // 等待数据准备好
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 休眠以避免忙等
    }
    std::cout << "Consumer: Data consumed: " << shared_data << "\n";
}
} // namespace my_atomic
} // namespace my_thread


void main_atomic() {
    std::thread producer_thread(my_thread::my_atomic::producer_atomic);
    std::thread consumer_thread(my_thread::my_atomic::consumer_atomic);
    producer_thread.join();
    consumer_thread.join();
}

// 测试
#ifndef MY_MODULES_TEST
int main(int argc, char *argv[])
#else
int thread_main(int argc, char *argv[])
#endif
{
    main_atomic();
    return 0;
}