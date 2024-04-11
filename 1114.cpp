#include <mutex>
#include <functional>
#include <thread>
#include <iostream>

using namespace std;
class Foo {
mutex mtx1, mtx2;
public:
    Foo() {
	// 在主线程锁
        mtx1.lock(), mtx2.lock();
    }

    void first(function<void()> printFirst) {
	//mtx1.lock();但是在子线程不能获取还未释放的锁
	printFirst();
	// 可以在子线程解锁
        mtx1.unlock();
    }

	// first --second: mtx1相连
    void second(function<void()> printSecond) {
        mtx1.lock();
        printSecond();
        mtx1.unlock();

        mtx2.unlock();
    }

	// second -- third: mtx2相连
    void third(function<void()> printThird) {
        mtx2.lock();
        printThird();
        mtx2.unlock();
    }

    // void first(function<void()> printA) {
    //     printA();
    //     mtx1.unlock();
    // }
    // void second(function<void()> printB) {
    //     mtx1.lock();
    //     printB();
    //     mtx1.unlock();
    //     mtx2.unlock();
    // }
    // void third(function<void()> printC) {
    //     mtx2.lock();
    //     printC();
    //     mtx2.unlock();
    // }

};

int main() {
    Foo foo;
    std::thread t1(&Foo::first, &foo, []()
		   { std::cout << "first" << std::endl; });
    std::thread t2(&Foo::second, &foo, []()
		   { std::cout << "second" << std::endl; });
    std::thread t3(&Foo::third, &foo, []()
		   { std::cout << "thrid" << std::endl; });
    t1.join();
    t2.join();
    t3.join();
}