#include <iostream>

namespace ns1{
	class A{};
	void f(const A& v)
	{
		std::cout << "ns1::f" << "\n";
	}
};

namespace ns2{
	class A{};
	void f(const A& v)
	{
		std::cout << "ns2::f" << "\n";
	}
};

template<class T>
void f(const T& t)
{
	std::cout << "::f" << "\n";
}

void geom_test();

int main()
{
	f(10);
	f(ns1::A());
	f(ns2::A());
	geom_test();
}
