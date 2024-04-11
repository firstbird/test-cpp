#include <mutex>
#include <functional>
#include <thread>
#include <iostream>
#include <atomic>
#include <condition_variable>

using namespace std;
class ZeroEvenOdd {
private:
    int n;
    // mutex的作用是做时序控制,不要把atomic和mutex一起用
    mutex mu1;
    mutex mu2;
    mutex mu3;
//     std::atomic<int> atm;
//     int i;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
	// mu1.lock();不能加，因为foo不能重复上锁,这会导致无法开始
	mu2.lock();
	mu3.lock();
    }

    void zero(function<void(int)> print) {
	// 表示要打印n个0
	for (int i = 0; i < n; ++i)
	{

		// printFoo() outputs "foo". Do not change or remove this line.
		// mu.lock();一个锁时两个线程一个加一个不加锁时，只能确保【单次运行1114】的顺序，都加的话，这样配合不了交替顺序，谁都想要锁谁都不让，运行不了
		mu1.lock();
		print(0);
		if (i % 2 == 0)
		{
			mu2.unlock();
		} else {
			mu3.unlock();
		}
	}
    }

    void odd(function<void(int)> print) {
        
        for (int i = 1; i <= n; i += 2) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
		// mu.lock();一个锁时两个线程一个加一个不加锁时，只能确保【单次运行1114】的顺序，都加的话，这样配合不了交替顺序，谁都想要锁谁都不让，运行不了
		mu2.lock();
		print(i);
		mu1.unlock();
	}
    }

    void even(function<void(int)> print) {

	for (int i = 2; i <= n; i += 2)
	{

		// printBar() outputs "bar". Do not change or remove this line.
		mu3.lock();
		print(i);
		mu1.unlock();
	}
    }
};

int main() {
    ZeroEvenOdd eventOdd(4);
    std::thread t1(&ZeroEvenOdd::zero, &eventOdd, [](int a)
		   { std::cout << "thread1: " << a << std::endl; });
    std::thread t2(&ZeroEvenOdd::odd, &eventOdd, [](int a)
		   { std::cout << "thread2: " << a << std::endl; });
    std::thread t3(&ZeroEvenOdd::even, &eventOdd, [](int a)
		   { std::cout << "thread3: " << a << std::endl; });
    t1.join();
    t2.join();
    t3.join();
}
