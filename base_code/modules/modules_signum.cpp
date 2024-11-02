#include <csignal>  
#include <iostream>  
#include <cstring>  
#include <unistd.h>  

void signalHandler(int signum) {  
    std::cout << "Interrupt signal (" << signum << ") received.\n";  
    exit(signum);  
}  

int main_signalHandler() {  
    struct sigaction sa;  
    memset(&sa, 0, sizeof(sa));  
    sa.sa_handler = signalHandler;  

    // 注册信号处理函数  
    sigaction(SIGINT, &sa, NULL);  

    while (true) {  
        std::cout << "Waiting for signal...\n";  
        sleep(1);  
    }  

    return 0;  
}

int main_signal() {  
    // 注册信号处理函数  
    signal(SIGINT, signalHandler);  

    while (true) {  
        std::cout << "Waiting for signal...\n";  
        sleep(1);  
    }  

    return 0;  
}

int main() {
    main_signal();
    main_signalHandler();
    return 0;
}