/*
 说明：程序是在 64 位编译器下测试的
 */
#include <iostream>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <chrono>
//#include <chrono_literals>
using namespace std::chrono_literals;

#include <iostream>
#include <cstring>
 using namespace std;
#define offset(TYPE,MEMBER) ((long long)&((TYPE *)0)->MEMBER)//这里得改 long long

 struct A
 {
     short var; // 偏移 0 字节 （内存对齐原则 : short 2 字节 + 填充 2 个字节）
     int var1;  // 偏移 4 字节 （内存对齐原则：int 占用 4 个字节）
     long var2; // 偏移 8 字节 （内存对齐原则：long 占用 8 个字节）
     char var3; // 偏移 16 字节 （内存对齐原则：char 占用 1 个字节 + 填充 7 个字节）
     string s;  // 偏移 24 字节 （string 占用 32 个字节）
 };

class B 
{
public:
    virtual void fun1() {
	    
    }
};

std::condition_variable cv;
std::mutex cv_m;
int i;
void waits(int idx)
{
    std::unique_lock<std::mutex> lk(cv_m);
    // 【有两种返回情况，超时返回；满足条件返回】
    if (cv.wait_for(lk, idx*100ms, []{return i == 1;})) {
        // 满足条件返回 true
        std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
    } else {
        std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
    }
}

void signals()
{
    std::this_thread::sleep_for(120ms);
    std::cerr << "Notifying...\n";
    cv.notify_all();
    std::this_thread::sleep_for(100ms);
    {
        std::lock_guard<std::mutex> lk(cv_m);
        i = 1;
    }
    std::cerr << "Notifying again...\n";
    cv.notify_all();
}

int main()
{
    //      string s;
    //      A ex1;
    //      cout << offset(A, var) <<endl;// 0
    //      cout << offset(A, var1) <<endl; // 4
    //      cout << offset(A, var2) <<endl; // 8
    //      cout << offset(A, var3) <<endl; // 12
    //      cout << offset(A, s) <<endl; // 16
    //      cout << sizeof(ex1) << endl;  // 48 struct

	// size_t t = 9;
	// auto f = [t]() mutable{
	// 	t++;
	// 	return t; 
	// };
	// cout << f() << endl; // 10
	// cout << t << endl;
	// t = 100;
	// cout << f() << endl; // 11
	// cout << "t:" << t << endl; // t: 100



    // char arr[10] = "hello";
    // cout << strlen(arr) << endl; // 5
    // cout << sizeof(arr) << endl; // 10
    // B *b = new B();
    // b->fun1();


    std::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(signals);
    t1.join(); // t1 等待 100ms 后未被唤醒，自动超时；
    t2.join(); // t2 在 120 ms 处被唤醒【唤醒就是notify】，但 condition 未满足【这是自己的原因,2就没有机会了】，再此进入阻塞，200ms 时由于超时返回
    t3.join(); // t3 在 120 ms 处被唤醒，但 condition 未满足，再此进入阻塞，220ms 时被 notify【再次被唤醒，又获得一次机会】 ，正常返回【判定条件成功】。
    t4.join();

    return 0;
 }