#include <iostream>
int main()
{
	class Array
	{public:
		int a[10][10]={};
		int& operator[](int i1,int i2) 
		{
			return a[i1][i2];
		}
	};
	Array a;
	a[0,0]=1;
	std::cout << a[0,0] << "\n";
}
