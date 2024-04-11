#include <iostream>

#include <cstring>
using namespace std;
typedef int (*fun_p)(int , int);

class CBase { 
public:
//	虚函数必须实现
// 纯虚函数是要求它的子类必须实现
	virtual void print() {}
	// {
	// 	std::cout << "Im base" << std::endl;
	// }
};
class CDerived: public CBase {
public:	
	void print() {
		std::cout << "Im derived" << std::endl;
	}	
};
class A
{
public:

	A(int n = 1) : p_size(1){

	}
	A(const A& temp){
		p = new char[temp.p_size];
		p_size = temp.p_size;
	}
	~A() {
		(*p_count)--;
		if (*p_count == 0) {
			if (p != nullptr) {
				delete[] p;
				p = nullptr;
				if (p_count != nullptr) {
					delete p_count;
					p_count = nullptr;
				}
			}

		}
	}
	A &operator=(const A &) = delete;
	void f(std::initializer_list<int> list) {
		std::cout << "list: " << std::endl;
		for (auto l : list) {
			std::cout << "element: " << l << std::endl;
		}
	}

private:
	char *p;
	unsigned int p_size;
	int *p_count;
};

int main() {
	// A ex(100);
	// A b = 10;
	// b.f({1,12});
	// A ex3;
    	// ex3 = b;

	CBase* b = new CDerived();
	CBase* pb;
	CDerived d;
	CDerived* pd;
	pb = dynamic_cast<CBase*>(&d); // ok: derived-to-base【引用转指针】
	pd = dynamic_cast<CDerived*>(b); // error: base-to-derived
	if (pd)
	pd->print();
	else {
		std::cout << "pd null ----" << std::endl;
	}
}