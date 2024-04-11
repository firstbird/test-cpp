#include<iostream>
#include<mutex>
#include<thread>
using namespace std;

template<class T>
class Shared_Ptr {
private:
	int *p_Count;
	T *rawPtr;
	mutex *mtx;

	void Release() {
		bool isDeleted = false;
		mtx->lock();
		if (--(*p_Count) == 0) {
			delete rawPtr;
			rawPtr = nullptr;
			isDeleted = true;
		}
		mtx->unlock();
		if (isDeleted) {
			delete mtx;
			mtx = nullptr;
		}
	}
public:
	Shared_Ptr() {}
	Shared_Ptr(T* ptr) : rawPtr(ptr), p_Count(new int(1)), mtx(new mutex) {
	}
	Shared_Ptr(const Shared_Ptr<T>& sp)
		:rawPtr(sp.rawPtr)
		, p_Count(sp.p_Count) // count指针
		, mtx(sp.mtx)
	{
		cout << " = copy constructor = " << endl;
		addRefCount();
	}
	~Shared_Ptr() {
		Release();
	}
	Shared_Ptr<T>& operator=(const Shared_Ptr<T>& sp) {
		if (sp.rawPtr != rawPtr) {
			Release();
			p_Count = sp.p_Count;
			rawPtr = sp.rawPtr;
			mtx = sp.mtx;
		}
		return *this;
	}

	void addRefCount() {
		mtx->lock();
		++(*p_Count);
		mtx->unlock();
	}

	T& operator*(){
		return *rawPtr;
	}
	T* operator->(){
		return rawPtr;
	}
	T* get() {
		return rawPtr;
	}
	int UseCount() {
		return *p_Count;
	}
};

class Person
{
public:
	Person(){}
	Person(const Person& p)
	{
		cout << "Copy Constructor" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Assign" << endl;
		return *this;
	}

private:
	int age;
	string name;
};

void f(Person p)
{
	return;
}

Person f1()
{
	Person p;
	return p;
}


int main() {
	cout << "main 1 begin" << endl;
	Shared_Ptr<int> p1 = Shared_Ptr<int>(new int(1));
	cout << "main 1 end" << endl;
	//{
	cout << "main 2 begin" << endl;
	Shared_Ptr<int> p2(p1);
	cout << "main 2 end" << endl;
	cout << "main 3 begin" << endl;
	Shared_Ptr<int> p3;
	cout << "main 3 end" << endl;
	cout << "main 3-1 begin" << endl;
	p3 = p1;
	cout << "main 3-1 end" << endl;
	//}
	cout << p1.UseCount() << endl;

	// Person p;
	// cout << "main 1 begin" << endl;
	// Person p1 = p;    // 1 未有对象进行拷贝
	// cout << "main 1 end" << endl;
	// Person p2;
	// cout << "main 2 begin" << endl;
	// p2 = p;  // 2 已有对象进行赋值
	// cout << "main 2 end" << endl;
	// f(p2);            // 3

	// p2 = f1();        // 4

	// Person p3 = f1(); // 5

	getchar();
	return 0;
}