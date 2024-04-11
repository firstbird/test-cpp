#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <deque>
#include <queue>
#include <condition_variable>
using namespace std;

class FooBar {
private:
    int n;
    std::mutex lock1;
    std::mutex lock2;

public:
    FooBar(int n) {
        this->n = n;
	lock2.lock();
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
		lock1.lock();
		// std::lock_guard<std::mutex> guard(lock2);
		// printFoo() outputs "foo". Do not change or remove this line.
		printFoo();
		lock2.unlock();
	}
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
		lock2.lock();
		// std::lock_guard<std::mutex> guard(lock1);
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
		lock1.unlock();
	}
    }
};

class ZeroEvenOdd {
private:
    int n;
    std::atomic<int> atomicInt{1};
    std::mutex mtx1;
    std::mutex mtx2;
    std::mutex mtx3;

public:
    ZeroEvenOdd(int n) {
        this->n = n;
	mtx2.lock();
	mtx3.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
	    while (atomicInt <= n) {
		mtx1.lock();
		if (atomicInt > n) {
			mtx1.unlock();
			mtx2.unlock();
			mtx3.unlock();
			break;
		}
		// cout << "zero, i: " << atomicInt << endl;
		printNumber(0);
		// i++;
		//atomicInt.fetch_add(1);
		if (atomicInt % 2 == 0 && atomicInt != 0) {
			mtx2.unlock();
		} else if (atomicInt % 2 != 0) {
			mtx3.unlock();
		}
	    }
    }

    void even(function<void(int)> printNumber) {
	    while (atomicInt <= n) {
		mtx2.lock();
		if (atomicInt > n) {
			mtx1.unlock();
			mtx2.unlock();
			mtx3.unlock();
			break;
		}
		// cout << "even, i: " << atomicInt << endl;
		printNumber(atomicInt);
		atomicInt.fetch_add(1);
		mtx1.unlock();
	    }
    }

    void odd(function<void(int)> printNumber) {
	    while (atomicInt <= n) {
		mtx3.lock();
		if (atomicInt > n) {
			mtx1.unlock();
			mtx2.unlock();
			mtx3.unlock();
			break;
		}
		// cout << "odd, i: " << atomicInt << endl;
		printNumber(atomicInt);
		atomicInt.fetch_add(1);
		atomicInt.fetch_sub(1);
		mtx1.unlock();
		// cout << "odd unlock, i: " << atomicInt << endl;
	    }
    }
};

class EvenOdd {
private:
    int n;
    std::atomic<int> atomicInt{1};
    std::mutex mtx1;
    std::mutex mtx2;

public:
    EvenOdd(int n) {
        this->n = n;
	mtx2.lock();
    }

    void even(function<void(int)> printNumber) {
	    while (atomicInt <= n) {
		mtx1.lock();
		if (atomicInt > n) {
			mtx1.unlock();
			mtx2.unlock();
			break;
		}
		// cout << "even, i: " << atomicInt << endl;
		printNumber(atomicInt);
		atomicInt.fetch_add(1);
		mtx2.unlock();
	    }
    }

    void odd(function<void(int)> printNumber) {
	    while (atomicInt <= n) {
		mtx2.lock();
		if (atomicInt > n) {
			mtx1.unlock();
			mtx2.unlock();
			break;
		}
		// cout << "odd, i: " << atomicInt << endl;
		printNumber(atomicInt);
		atomicInt.fetch_add(1);
		mtx1.unlock();
		// cout << "odd unlock, i: " << atomicInt << endl;
	    }
    }
};


class BoundedBlockingQueue {
private:
	queue<int> queue;
	std::mutex mtx;
	std::condition_variable cv;
	int cap;

public:
    BoundedBlockingQueue(int capacity) {
	    cap = capacity;
    }
    
    void enqueue(int element) {
	    std::unique_lock<std::mutex> lock(mtx);
	    cv.wait(lock, [&]()
		    { queue.size() < cap; });
	    queue.push(element);
	    lock.unlock();
	    cv.notify_all();
    }
    
    int dequeue() {
	    int res = 0;
	    std::unique_lock<std::mutex> lock(mtx);
	    cv.wait(lock, [&]()
		    { queue.size() > 0; });
	    res = queue.front();
	    queue.pop();
	    lock.unlock();
	    cv.notify_all();
	    return res;
    }
    
    int size() {
	    int res = 0;
	    std::unique_lock<std::mutex> lock(mtx);
	    res = queue.size();
	    lock.unlock();
	    cv.notify_all();
	    return res;
    }
};


int main() {
	// 1115
	// FooBar fooBar(4);
	// function<void()> f1;
	// function<void()> f2;
	// f1 = std::bind(&FooBar::foo, &fooBar, []()
	// 	      { cout << "foo";});
	// f2 = std::bind(&FooBar::bar, &fooBar, []()
	// 	      { cout << "bar";});
	// std::thread t1(f1);
	// std::thread t2(f2);

    // t1.join();
    // cout << "t1 join done" << endl;
    // t2.join();
    // cout << "t2 join done" << endl;

    // ZeroEvenOdd foo(30);
    // auto f1 = std::bind(&ZeroEvenOdd::zero, &foo, [](int a)
    // 	      {
    // 		      cout << a;
    // 	      });
    // auto f2 = std::bind(&ZeroEvenOdd::even, &foo, [](int a)
    // 	      {
    // 		      cout << a;
    // 	      });
    // auto f3 = std::bind(&ZeroEvenOdd::odd, &foo, [](int a)
    // 	      {
    // 		      cout << a;
    // 	      });
    // std::thread t1(f1);
    // std::thread t2(f2);
    // std::thread t3(f3);
    // t1.join();
    // t2.join();
    // t3.join();

    EvenOdd foo(30);
    auto f1 = std::bind(&EvenOdd::even, &foo, [](int a)
			{ cout << " thread1: " << a << endl; });
    auto f2 = std::bind(&EvenOdd::odd, &foo, [](int a)
			{ cout << " thread2: " << a << endl; });
    std::thread t1(f1);
    std::thread t2(f2);
    t1.join();
    t2.join();
}