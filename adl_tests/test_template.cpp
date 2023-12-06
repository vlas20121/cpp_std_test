#include <iostream>

namespace tns1{
	class A{};
	template<class A>
	void f(const A& v)
	{
		std::cout << "ns1::f" << "\n";
	}
};

namespace tns2{
	class A{};
	template<class A>
	void f(const A& v)
	{
		std::cout << "ns2::f" << "\n";
	}
};

template<class T>
void f1(const T& t)
{
	std::cout << "::f" << "\n";
}

void geom_test();

//using namespace tns1;
//using namespace tns2;

int main_template()
{
	f1(10);
	f(tns1::A());
	f(tns2::A());
	return 0;
}
