#include <iostream>
using namespace std;
template <typename T>
T add(T x, T y)
{
	// return (x > y) ? x : y;
	return x + y;
}

template <typename T>
class A {
public:
	T a;
	static T b;
	T add(T c, T d) {
		return b + c + d;
	}
};

template<typename T>
T A<T>::b = 2;

template <typename T1, typename T2>
class B {
public:
	B(){};
	void h();
};

template <typename T1, typename T2>
void B<T1, T2>::h(){
	cout << "B -- h() " << endl;
};

int main()
{
	// cout << add<int>(3, 7) << endl;
	// cout << add<double>(3.8, 7.1) << endl;
	// cout << add<char>('g', 'a') << endl;
	A<int> aa;
	cout << aa.add(2, 5) << endl;

	B<int, int> bb;
	bb.h();
}