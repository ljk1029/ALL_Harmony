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
 * 锁离开作用域自动释放
 * std::lock_guard 没有提供释放锁的操作
 * unique_lock可以手动加解锁，
 * 1、注意wait执行是会释放所有锁，直到返回值为true才重新获取锁
 * 2、std::lock_guard<std::mutex> lock(mtx); 会获取锁保护作用区，
 *    但特例是和wait一起使用时，不管锁是释放还是使用状态，都会执行到wait
 *    (1)
 * 锁被其他线程占用，返回false(一般全局变量，用来做状态)，wait会阻塞，等待notify_all通知后或者使用wait_for超时，再次返回true，执行后续
 *    (2) 锁被释放，返回true，执行后续
 */
namespace my_lock {
// 锁
std::mutex mtx;
std::condition_variable cv;
bool is_sata_ready = false;
int shared_data = 0;
constexpr int loop_cnt = 10;

// 同步 线程函数
void thread_lock(int n) {
    mtx.lock();
    std::cout << "Hello from the thread:" << n << "\n";
    mtx.unlock();
}

// 生产者lock
void produce_lock() {
    while (shared_data < loop_cnt) {
        std::lock_guard<std::mutex> lock(mtx);
        if (is_sata_ready == false) {
            shared_data++;
            std::cout << "Producer data: " << shared_data << ", lock: " << is_sata_ready << std::endl;
            is_sata_ready = true;
            // std::this_thread::sleep_for(std::chrono::seconds(1)); //
            // 模拟生产数据的耗时操作
        }
    }
    std::cout << "---produce_lock exit---" << std::endl;
}

// 消费者lock
void consumer_lock() {
    while (shared_data < loop_cnt) {
        std::unique_lock<std::mutex> lock(mtx);
        if (is_sata_ready == true) {
            std::cout << "Consumed data: " << shared_data << ", lock: " << is_sata_ready << std::endl;
            is_sata_ready = false;
        } else {
            // std::this_thread::sleep_for(std::chrono::milliseconds(10)); //
            // 模拟生产数据的耗时操作
        }
    }
    std::cout << "***consumer_lock exit***" << std::endl;
}

// 生产者wait
void producer_wait() {
    while (shared_data < loop_cnt * 2) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock(mtx);
        if (is_sata_ready == false)
            shared_data++;
        std::cout << "Producer data: " << shared_data << ", lock: " << is_sata_ready << std::endl;
        is_sata_ready = true;
        // cv.notify_one(); // 通知消费者线程，数据已准备好
        cv.notify_all();
        // cv.native_handle();
    }
    std::cout << "producer_wait exit" << std::endl;
}

// 消费者wait
void consumer_wait() {
    while (shared_data < loop_cnt * 2) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock,
                [] { // 等待时释放所有锁, 一旦条件满足（本例中是is_sata_ready ==
                     // true），条件变量会唤醒等待的线程，然后再次尝试获得互斥锁。
                    std::cout << "Consumed lock ...: " << is_sata_ready << std::endl;
                    return is_sata_ready;
                }); // 等待数据准备好的通知
        std::cout << "Consumed data: " << shared_data << ", lock: " << is_sata_ready << std::endl;
        is_sata_ready = false;
    }
    std::cout << "consumer_wait exit" << std::endl;
}

// 消费者wait_for
void consumer_waitFor() {
    while (shared_data < loop_cnt * 2) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait_for(lock, std::chrono::milliseconds(30),
                    [] { return is_sata_ready; }); // 等待数据准备好的通知或超过固定时间
        std::cout << "Consumed for data: " << shared_data << ", lock: " << is_sata_ready << std::endl;
        is_sata_ready = false;
    }
    std::cout << "consumer_waitFor exit" << std::endl;
}
} // namespace my_lock
}

// 锁同步线程创建
int main_lock() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(
            std::thread(my_thread::my_lock::thread_lock, i + 1)
        );
    }
    for (auto &t : threads) {
        t.join();
    }
    return 0;
}


void main_auto_lock() {
    std::thread t1(my_thread::my_lock::produce_lock);
    std::thread t2(my_thread::my_lock::consumer_lock);
    t1.detach();         // 分离式
    if (t2.joinable()) { // 判断线程是否可被合并或分离
        t2.join();       // 等待线程结束
    }
}

void main_wait() {
    std::thread t3(my_thread::my_lock::producer_wait);
    // std::thread t4(my_thread::my_lock::consumer_waitFor);
    std::thread t4(my_thread::my_lock::consumer_wait);
    t3.join();
    t4.join();
}

// 测试
#ifndef MY_MODULES_TEST
int main(int argc, char *argv[])
#else
int thread_main(int argc, char *argv[])
#endif
{
    main_lock();
    main_auto_lock();
    main_wait();
    return 0;
}