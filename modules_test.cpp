//#include <vector>

import std.core;//std.core.ixx?
//import std.filesystem;
//import std.memory;
//import std.regex;
//import std.threading;

void modules_test()
{
	for (auto i : std::vector<int>{ 1,2,3,4,6,7,8,9 })
		std::cout << i << ",";
}

class modules_test_runner
{
public:
	modules_test_runner()
	{
		modules_test();
	}
};
static modules_test_runner run;
