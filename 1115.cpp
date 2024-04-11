#include <mutex>
#include <functional>
#include <thread>
#include <iostream>
using namespace std;
class FooBar {
private:
    int n;
    mutex mu1;
    mutex mu2;

    public:
    FooBar(int n) {
        this->n = n;
        // mu1.lock();不能加，因为foo不能重复上锁,这会导致无法开始
        mu2.lock();
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
            // mu.lock();一个锁时两个线程一个加一个不加锁时，只能确保【单次运行1114】的顺序，都加的话，这样配合不了交替顺序，谁都想要锁谁都不让，运行不了
            mu1.lock();
            printFoo();
            mu2.unlock();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            
            // printBar() outputs "bar". Do not change or remove this line.
            mu2.lock();
            printBar();
            mu1.unlock();
        }
    }
};

int main() {
    FooBar foobar(10);
    std::thread t1(&FooBar::foo, &foobar, []()
		   { std::cout << "Foo" << std::endl; });
    std::thread t2(&FooBar::bar, &foobar, []()
		   { std::cout << "Bar" << std::endl; });
    t1.join();
    t2.join();
}