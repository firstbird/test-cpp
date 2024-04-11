#include <iostream>
#include <thread>
#include <chrono>

void timer_callback() {
    std::cout << "定时器触发了！" << std::endl;
}

void timer_thread() {
    while (true) {
        auto start_time = std::chrono::high_resolution_clock::now();
        timer_callback();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        auto sleep_time = std::chrono::milliseconds(10) - elapsed_time;
        if (sleep_time > std::chrono::milliseconds(0)) {
            std::this_thread::sleep_for(sleep_time);
        }
    }
}

void timer_thread() {
    while (true) {
        timer_callback();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

int main() {
    std::thread t(timer_thread);
    t.join();
    return 0;
}