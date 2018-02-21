#pragma once

constexpr inline int FactFunc(const int n)
{
	if (n == 0)
		return 1;
	return n * FactFunc(n - 1);
}

template <int TN>
struct IntStruct
{
	enum
	{
		eValue = TN
	};
};

template <int TN>
struct FactStruct
{
	enum
	{
		eValue = FactStruct<TN - 1>::eValue * TN
	};
};

template<>
struct FactStruct<0>
{
	enum
	{
		eValue = 1
	};
};


struct DummyWithMember
{
private:
	int member;
};

struct DummyWithData
{
private:
	void* data;
};


template<typename T>
class HasMember {
private:
	typedef char ByteType;
	typedef struct { char a[2]; } ShortType;
	template<typename C> static ByteType Overloadable(decltype(C::member)*);
	// Will be chosen if T is anything except a class.
	template<typename C> static ShortType Overloadable(...);
public:
	enum { Yes = sizeof(HasMember<T>::Overloadable<T>(nullptr)) == 1 };
	enum { No = !Yes };
};

template<typename T>
constexpr bool FuncHasMember(decltype(T::member)*)
{
	return true;
}

template<typename T>
constexpr bool FuncHasMember(...)
{
	return false;
}

template<typename T>
constexpr bool CheckHasMember()
{
	return FuncHasMember<T>(nullptr);
}
