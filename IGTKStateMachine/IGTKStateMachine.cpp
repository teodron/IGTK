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

class A
{
	~A()
	{}
};



int main()
{
	A* a = new A();
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
