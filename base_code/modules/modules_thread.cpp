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
// 进程ID、线程ID
#define GET_PID() std::cout << "Process ID: " << getpid() << std::endl
#define GET_TID() std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl
#define PRINT_FUNC_NAME() std::cout << "\n[" << __func__ << " test]" << std::endl


// 不带参数 做为线程函数
void thread_function() { 
    std::cout << "Hello from the thread!\n"; 
}

// 带参数 做为线程函数
void thread_function_arg(const char *message) { 
    std::cout << "Hello from the thread: " << message << "\n"; 
}

// 类 做为线程函数
class threadClass {
public:
    void operator()() const { 
        std::cout << "Hello from the thread class operator!\n"; 
    }

    void thread_function_arg() const { 
        std::cout << "Hello from the thread member function!\n"; 
    }
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
    std::thread t(
        []() { 
            std::cout << "Hello from the lambda thread!\n"; 
        }
    );
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
    threadClass hello;
    // 使用函数对象创建线程
    std::thread t1(hello);
    // 使用成员函数创建线程
    std::thread t2(&threadClass::thread_function_arg, &hello);
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
} // namespace my_thread

int main_thread() {
    my_thread::my_tc::thread_create_fun_1();
    my_thread::my_tc::thread_create_fun_2();
    my_thread::my_tc::thread_create_fun_3();
    my_thread::my_tc::thread_create_fun_4();
    my_thread::my_tc::thread_create_fun_5();
    my_thread::my_tc::thread_create_fun_6();
    my_thread::my_tc::thread_create_fun_8();
    for (int i = 0; i < 10; ++i)
        my_thread::my_tc::thread_create_fun_9(i);
    return 0;
}

// 测试
#ifndef MY_MODULES_TEST
int main(int argc, char *argv[])
#else
int thread_main(int argc, char *argv[])
#endif
{
    main_thread();
    return 0;
}