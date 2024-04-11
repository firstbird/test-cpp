#include<iostream>
 
using namespace std;
 
#define DELETE(pointer) delete pointer; pointer=nullptr
 
class IProduct //抽象产品
{
public:
	IProduct() {}
	virtual ~IProduct() {}
 
	virtual void show() = 0;
};
 
class ProductA : public IProduct //具体产品A
{
public:
	ProductA() {}
	~ProductA() {}
 
	virtual void show() { cout << "ProductA" << endl; }
};
 
class ProductB : public IProduct //具体产品B
{
public:
	ProductB() {}
	~ProductB() {}
 
	virtual void show() { cout << "ProductB" << endl; }
};
 
class IFactory //抽象工厂
{
public:
	IFactory() {}
	virtual ~IFactory() {}
 
	virtual IProduct* createProduct() = 0;
};
 
class FactoryA : public IFactory //具体工厂
{
public:
	FactoryA() {}
	virtual ~FactoryA() {}
 
	IProduct* createProduct() override{	return new ProductA;}
};
 
class FactoryB : public IFactory //具体工厂
{
public:
	FactoryB() {}
	virtual ~FactoryB() {}
 
	IProduct* createProduct() override{	return new ProductB;}
};
 
void doFactoryMethod()
{
	//生产产品A
	IFactory *factory = new FactoryA();
	IProduct *product = factory->createProduct();
	product->show();
	DELETE(product);
	DELETE(factory);
 
	//生产产品B
	factory = new FactoryB();
	product = factory->createProduct();
	product->show();
	DELETE(product);
	DELETE(factory);
}

#include <iostream>
 
extern void doFactoryMethod();
 
int main()
{
	doFactoryMethod();
 
	system("pause");
	return 1;
}