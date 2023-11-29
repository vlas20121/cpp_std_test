#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "zpp_bits.h"

struct person
{
    std::string name;
    int age{};
};

int main1()
{
	// The `data_in_out` utility function creates a vector of bytes, the input and output archives
	// and returns them so we can decompose them easily in one line using structured binding like so:
	std::string data;
	zpp::bits::in in(data);
	zpp::bits::out out(data);

	// Serialize a few people:
	out(person{"Person1", 25}, person{"Person2", 35});

	// Define our people.
	person p1, p2;

	// We can now deserialize them either one by one `in(p1)` `in(p2)`, or together, here
	// we chose to do it together in one line:
	in(p1, p2);
	
	std::cout << data;

	return 0;
}

void write(std::vector<char>& data,std::string f)
{
	std::ofstream os(f, std::ios::binary);
	os.write( &data[0], data.size() );
	os.close();
}
int main2()
{
	//std::string data;
	std::vector<char> data;
	zpp::bits::in in(data);
	zpp::bits::out out(data);

	struct vec3{
		double x=0;
		double y=0;
		double z=0;
	};
	struct NURBS
	{
		int version=1;
		std::vector<vec3> control={vec3{1,2,3},vec3{4,5,6},vec3{7,8,9}};
		std::vector<double> knots={0,0,0,1,1,1};
		bool rational=false;
	};
	struct NURBS_set
	{
		std::vector<NURBS>contours={NURBS{},NURBS{},NURBS{}};
	};

	NURBS_set n1;
	out(n1);
	write(data,"NURBS_set1");
	
	{
		NURBS_set n1;n1.contours.resize(0);in(n1);
		//std::vector<char> data1;
		//zpp::bits::out out1(data1);
		out.reset();
		out(n1);
		write(data,"NURBS_set2");
	}
}

int main()
{
	//main1();
	main2();
}
