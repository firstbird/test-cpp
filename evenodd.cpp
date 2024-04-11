#include <mutex>
#include <functional>
#include <thread>
#include <iostream>
#include <atomic>
using namespace std;
class EventOdd {
private:
    int n;
    mutex mu1;
    mutex mu2;
//     std::atomic<int> atm;

    public:
    EventOdd(int n) {
        this->n = n;
        // mu1.lock();不能加，因为foo不能重复上锁,这会导致无法开始
        mu2.lock();
    }

    void odd(function<void(int)> print) {
        
        for (int i = 1; i <= n; i += 2) {

        	// printFoo() outputs "foo". Do not change or remove this line.
            // mu.lock();一个锁时两个线程一个加一个不加锁时，只能确保【单次运行1114】的顺序，都加的话，这样配合不了交替顺序，谁都想要锁谁都不让，运行不了
            mu1.lock();
            print(i);
            mu2.unlock();
        }
    }

    void even(function<void(int)> print) {
        
        for (int i = 2; i <= n; i += 2) {
        	// printBar() outputs "bar". Do not change or remove this line.
            mu2.lock();
            print(i);
            mu1.unlock();
        }
    }
};

int main() {
    EventOdd eventOdd(10);
    std::thread t1(&EventOdd::odd, &eventOdd, [](int a)
		   { std::cout << "thread1: " << a << std::endl; });
    std::thread t2(&EventOdd::even, &eventOdd, [](int a)
		   { std::cout << "thread2: " << a << std::endl; });
    t1.join();
    t2.join();
}