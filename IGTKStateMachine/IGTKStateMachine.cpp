// IGTKStateMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void f(int* const p)
{
	std::cout << p << std::endl;
	std::cout << *p << std::endl;
}

void g(int& i)
{
	std::cout << &i << std::endl;
	std::cout << i << std::endl;
	i = 10;
}

int k()
{
	return 0;
}

class Interface
{
public:
	virtual void Go() = 0;
	virtual ~Interface() = default;
};
template <class T>
class Wrapper : public Interface
{
public:
	void Go() override 
	{
		static_cast<T*>(this);
		dynamic_cast<T*>(this)->Do();
	}
};

class Base
{
	size_t x;
};

class A :public Base, public Wrapper<A>
{
public:
	void Do() { std::cout << "A"; }
	~A()
	{}
};

class B : public Base, public Wrapper<B>
{
public:
	void Do() { std::cout << "B"; }
};


int main()
{
	Interface* a = new A();
	Interface* b = new B();
	a->Go();
	b->Go();
	//delete a;
	int k(int c);

	k(2);
	int* p = new int;
	*p = 5;
	f(p);
	g(*p);



    return 0;
}

int k(int c);
int gigi()
{
	return k(3);
	
}

int k(int c)
{
	return c;
}
