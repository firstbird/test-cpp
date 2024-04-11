#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // 定义一个互斥锁

void worker(int* ptr) {
    for (int i = 0; i < 100000; i++) {
        // 使用互斥锁保护共享变量
        mtx.lock();
        (*ptr)++;
        mtx.unlock();
    }
}

int main() {
    int shared_var = 0;
    std::thread t1(worker, &shared_var);
    std::thread t2(worker, &shared_var);
    t1.join();
    t2.join();
    std::cout << "共享变量的值为：" << shared_var << std::endl;
    return 0;
}