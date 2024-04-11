#include <iostream>
#include <thread>
using namespace std;

void foo(int N)
{
	for (int i = 0; i < N; i++) {
        	cout << "线程使用函数指针作为可调用参数111\n";
        }
}

class thread_obj {
public:
	void operator()(int x) {
		for (int i = 0; i < x; i++)
            cout << "线程使用函数对象作为可调用参数222\n";
	}
};

int main() 
{
	thread th1(foo, 3);

	thread th2(thread_obj(), 3);

	auto f = [](int x)
	{
		for (int i = 0; i < x; i++)
		{
			cout << "线程使用 lambda 表达式作为可调用参数\n";
		}
	};
	thread th3(f, 3);

	th1.detach();

	th2.detach();

	th3.detach();
	int i = 100;
	while (i > 0) {
		cout << " i: " << i << endl;
		--i;
	}
}