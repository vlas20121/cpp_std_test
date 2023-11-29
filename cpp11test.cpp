//auto
//decltype
//std::initializer_list

#include <iostream>
#include <vector>
#include <initializer_list>

//no auto parameters in <=c++17
/*
auto plus(auto a, auto b)
{
    return a + b;
}
*/

template <class T>
struct S {
    std::vector<T> v;
    S(std::initializer_list<T> l) : v(l) {
        std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }
    std::pair<const T*, std::size_t> c_arr() const {
        return { &v[0], v.size() };  // copy list-initialization in return statement
                                   // this is NOT a use of std::initializer_list
    }
};

template <typename T>
void templated_fn(T) {}

void init_test1()
{
    S<int> s = { 1, 2, 3, 4, 5 }; // copy list-initialization
    s.append({ 6, 7, 8 });      // list-initialization in function call

    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";


    for (auto n : s.v)
        std::cout << n << ' ';

    std::cout << '\n';

    std::cout << "Range-for over brace-init-list: \n";

    for (int x : {-1, -2, -3}) // the rule for auto makes this ranged-for work
        std::cout << x << ' ';
    std::cout << '\n';

    auto al = { 10, 11, 12 };   // special rule for auto
    for (auto n : al) {}

    std::cout << "The list bound to auto has size() = " << al.size() << '\n';

    templated_fn(al);
    //templated_fn({1, 2, 3});  // compiler error! "{1, 2, 3}" is not an expression,
                                // it has no type, and so T cannot be deduced
    templated_fn<std::initializer_list<int>>({ 1, 2, 3 }); // OK
    templated_fn<std::vector<int>>({ 1, 2, 3 });           // also OK
}

void init_test2()
{
	std::cout << "\n";
	for (auto i : { 11,12,13,14,16,17,18,19 })
		std::cout << i << ",";
	std::cout << "\n";
	for (auto i : { 21.1,22.1,23.1,24.1,26.1,27.1,28.1,29.1 })
		std::cout << i << ",";
	std::cout << "\n";
	for (auto i : { "a", "b" ,"c" ,"d" })
		std::cout << i << ",";
	std::cout << "\n";
}

/*
* so, do not do:
int list[]={1,2,3,4,5};
best
auto list={1,2,3,4,5};
*/
void init_test3()
{
    //old
    int list1[] = { 1,2,3,4,5 };
    for (auto v : list1) {}
    //new
    auto list2 = { 1,2,3,4,5 };
    auto n = list2.size();
    for (auto v : list2) {}
}

//#pragma source_character_set("utf-8")
//#pragma execution_character_set("utf-8")
//#pragma execution_character_set("Windows-1252")
#if 0
void тест_не_анси_имен()
{
    using целое = int;
    using двойная = double;
    целое один = 1;
    целое ¹ = 1;
    //целое ♫ = 1;

    двойная Пи = 3.14;
    двойная ῖ = 3.14;
    двойная π = 3.14;

#define Π *
    двойная π² = π Π π;
#undef Π
    целое unicode_\u00fe = 1;
}
#endif
//https://docs.microsoft.com/ru-ru/cpp/cpp/user-defined-literals-cpp?view=msvc-160
#include <string>
#include <complex>
#include <chrono>

const long double km_per_mile = 1.609344L;

long double operator"" _km(long double val)
{
    return val;
}

long double operator"" _mi(long double val)
{
    return val * km_per_mile;
}

void test_user_literals()
{
    using namespace std;
    std::string str = "hello"s + "World"s;//https://en.cppreference.com/w/cpp/string/basic_string/operator%22%22s
    complex<double> num = (2.0 + 3.01i) * (5.0 + 4.3i);
    auto duration = 15ms + 42h;

    long double distance = 36.0_mi + 42.0_km;
    long double _km_per_mile = operator"" _mi(1);
}

void cpp11_tests()
{
    //тест_не_анси_имен();
    //list-initialization
    init_test1();
    init_test2();
    init_test3();
    //
    test_user_literals();
}

class runner11
{
public:
    runner11()
    {
        cpp11_tests();
    }
};
static runner11 run;
