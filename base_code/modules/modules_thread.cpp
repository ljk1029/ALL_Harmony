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
 * 线程创建使用方式
 */
namespace my_tc {
#define GET_PID() std::cout << "Process ID: " << getpid() << std::endl
#define GET_TID() std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl
#define PRINT_FUNC_NAME() std::cout << "\n[" << __func__ << " test]" << std::endl
// 锁
std::mutex mtx;

// 不带参数 做为线程函数
void thread_function() { 
    std::cout << "Hello from the thread!\n"; 
}

// 带参数 做为线程函数
void thread_function_arg(const char *message) { 
    std::cout << "Hello from the thread: " << message << "\n"; 
}

// 同步 线程函数
void thread_function_lock(int n) {
    mtx.lock();
    std::cout << "Hello from the thread:" << n << "\n";
    mtx.unlock();
}

// 类 做为线程函数
class ThreadClass {
public:
    void operator()() const { std::cout << "Hello from the thread class operator!\n"; }

    void thread_function_arg() const { std::cout << "Hello from the thread member function!\n"; }
};

// 不带参数线程创建
int thread_create_fun_1() {
    PRINT_FUNC_NAME();
    std::thread t(thread_function);
    t.join();
    return 0;
}

// 使用lambda表达式线程创建
int thread_create_fun_2() {
    PRINT_FUNC_NAME();
    std::thread t([]() { std::cout << "Hello from the lambda thread!\n"; });
    t.join();
    return 0;
}

// 参数线程创建
int thread_create_fun_3() {
    PRINT_FUNC_NAME();
    const char *message = "with parameters!";
    std::thread t(thread_function_arg, message);
    t.join();
    return 0;
}

// 分离式detach线程创建
int thread_create_fun_4() {
    PRINT_FUNC_NAME();
    std::thread t(thread_function_arg, "with detach!");
    t.detach();
    std::cout << "Main thread is done with detach!\n";
    // 延迟，以便看到分离线程的输出
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}

// 类线程函数线程创建
int thread_create_fun_5() {
    PRINT_FUNC_NAME();
    ThreadClass hello;
    // 使用函数对象创建线程
    std::thread t1(hello);
    // 使用成员函数创建线程
    std::thread t2(&ThreadClass::thread_function_arg, &hello);
    t1.join();
    t2.join();
    return 0;
}

// 获取ID线程创建
int thread_create_fun_6() {
    PRINT_FUNC_NAME();
    GET_PID();
    GET_TID();
    std::thread t([]() {
        std::thread::id id = std::this_thread::get_id();
        GET_TID();
        // std::this_thread::sleep_for(std::chrono::seconds(10));
    });
    t.join();
    return 0;
}

// 锁同步线程创建
int thread_create_fun_7() {
    PRINT_FUNC_NAME();
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(std::thread(thread_function_lock, i + 1));
    }
    for (auto &t : threads) {
        t.join();
    }
    return 0;
}

// 线程转移
int thread_create_fun_8() {
    PRINT_FUNC_NAME();
    const char *message = "with move!";
#if 1
    std::thread t1(thread_function_arg, message);
    std::thread t2 = std::move(t1);
    t2.join();
#else
    std::thread t1(thread_function_arg, "move 1");
    std::thread t2(thread_function_arg, "move 2");
    t2 = std::move(t1); // t1已关联一个线程，再赋值会调用std::terminate()终止程序
    t1.join();
    t2.join();
#endif
    return 0;
}

/**
 * 函数只会执行一次
 * 多线程下也是只执行一次
 */
std::once_flag onceFlag;

// 函数只会执行一次
void initialize() { 
    std::cout << "Initialize function called once" << std::endl; 
}

void thread_create_fun_9(int index) {
    PRINT_FUNC_NAME();
    std::cout << "Hello from the process:" << index << std::endl;
    std::call_once(onceFlag, initialize);
    std::cout << "Hello from the process after:" << index << std::endl;
}

} // namespace my_tc

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

int main_thread() {
    my_thread::my_tc::thread_create_fun_1();
    my_thread::my_tc::thread_create_fun_2();
    my_thread::my_tc::thread_create_fun_3();
    my_thread::my_tc::thread_create_fun_4();
    my_thread::my_tc::thread_create_fun_5();
    my_thread::my_tc::thread_create_fun_6();
    my_thread::my_tc::thread_create_fun_7();
    my_thread::my_tc::thread_create_fun_8();
    for (int i = 0; i < 10; ++i)
        my_thread::my_tc::thread_create_fun_9(i);
    return 0;
}

void main_lock() {
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
#if 0
    main_thread();
#endif
#if 1
    main_lock();
#endif
#if 1
    main_wait();
#endif
#if 1
    main_atomic();
#endif
    return 0;
}