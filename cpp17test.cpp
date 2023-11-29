#include <iostream>
#include <vector>

#ifdef __cpp_lib_any
#include <any>
#endif
void any_test()
{
#ifdef __cpp_lib_any
    std::cout << std::boolalpha;

    // any type
    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';

    // bad cast
    try
    {
        a = 1;
        std::cout << std::any_cast<float>(a) << '\n';
    }
    catch (const std::bad_any_cast& e)
    {
        std::cout << e.what() << '\n';
    }

    // has value
    a = 1;
    if (a.has_value())
    {
        std::cout << a.type().name() << '\n';
    }

    // reset
    a.reset();
    if (!a.has_value())
    {
        std::cout << "no value\n";
    }

    // pointer to contained data
    a = 1;
    int* i = std::any_cast<int>(&a);
    std::cout << *i << "\n";
#endif
}

#ifdef __cpp_lib_any
void print(const std::any& a)
{
    std::cout << a.type().name() << '\n';
}
#endif

class A {};
class B {};
void any_test1()
{
#ifdef __cpp_lib_any
    std::cout << std::boolalpha;
    A a;
    B b;
    print(std::any(a));
    print(std::any(&a));
    print(std::any(b));
    print(std::any(&b));
#endif
}

void cpp17_tests()
{
    any_test();
    any_test1();
}

class runner17
{
public:
    runner17()
    {
        cpp17_tests();
    }
};
static runner17 run;
