#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int c = 0;
mutex m;

// https://stackoverflow.com/questions/14641134/printing-odd-and-even-number-printing-alternately-using-threads-in-c
void printEven() {
	while (c <= 100) {
		m.lock();
		if (c % 2 == 0) {
			cout << "even: " << c++ << endl;
		}
		m.unlock();
	}
};

void printOdd() {
	while (c <= 100) {
		m.lock();
		if (c % 2 != 0) {
			cout << "odd: " << c++ << endl;
		}
		m.unlock();
	}
}

// atomic方式
// atomic<int> count(1);

// void printOdd()
// {
//     while(count <= 100)
//     {
//         if(count % 2 != 0)
//         {
//             cout << "Odd Thread: " << count << endl;
//             count++;
//         }
//     }
// }

// void printEven()
// {
//     while(count <= 100)
//     {
//         if(count % 2 == 0)
//         {
//             cout << "Even Thread: " << count << endl;
//             count++;
//         }
//     }
// }


int main() {
	thread t1(printEven);
	thread t2(printOdd);
	cout << "main begin, c: " << c<< endl;
	t1.join();

	cout << "t1 join done, c: " << c<< endl;
	t2.join();
	cout << "t2 join done, c: " << c<< endl;
	return 0;
}