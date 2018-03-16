#pragma once
#include <chrono>
#include <Windows.h>

class A
{
	public:
		~A()
		{
			printf("Object of type A destructor called\n");
		}
};

class B
{
	public:
		~B()
		{
			printf("Object of type B destructor called\n");
		}
};

class ScopedTimer
{
public:
	ScopedTimer();
	~ScopedTimer();
protected:
	std::chrono::steady_clock m_clock;
	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
	A m_A;
};

class ScopedTimerWithExtraMember : ScopedTimer
{
public:
	~ScopedTimerWithExtraMember()
	{
		std::chrono::duration<double, std::milli> dur = this->m_clock.now() - this->m_startTime;
		printf("Derived object destructor called after: %4.2fms\n", dur);
	}
private:
	B m_B;
};

