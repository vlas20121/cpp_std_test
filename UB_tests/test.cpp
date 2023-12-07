//https://godbolt.org
#include <iostream>

int foo(bool c)
{
	int x,y;
	y=c?x:42;//c==true => UB
	return y;
}

void ub1()
{
	std::cout << foo(true) << std::endl;
}

void ub2()
{
	for(int i=0;i<10;++i)
		std::cout << 1'000'000'000 * i << std::endl;
}

int main()
{
	ub1();
	ub2();
}
