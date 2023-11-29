/*
vc19 r16.11.2
C++20 Core
-__cpp_constexpr_in_decltype
C++20 LIB
- __cpp_lib_format
- __cpp_lib_ranges
*/

#include <iostream>
#include <concepts>
#include <vector>
#include <cassert>
#include <string>
#include <array>
#include <algorithm>
#include <numbers>
#include <bitset>
#include <chrono>
#include "Generator.h"
#include <thread>
#include <syncstream>

#pragma region ConceptsTest

void print(std::integral auto i) {
    std::cout << "Integral: " << i << '\n';
}

void print(auto x) {
    std::cout << "Non-integral: " << x << '\n';
}

void ConceptsTest1()
{
    print('o'); static_assert(std::integral<char>);
    print(007); static_assert(std::integral<int>);
    print(2.1); static_assert(!std::integral<float>);
    print("∫∫∫"); static_assert(!std::integral<decltype("")>);
}

template<typename T>
requires std::integral<T>
T gcd(T a, T b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

template<typename T>
T gcd1(T a, T b) requires std::integral<T>
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

template<std::integral T>
T gcd2(T a, T b)// requires std::integral<T>
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

auto gcd3(std::integral auto a, std::integral auto b) {     
    if (b == 0) 
        return (int)a; 
    else 
        return (int)gcd3(b, a % b);
}

//4.1.4.3 Concepts as Return Type of a Function
template<typename T> requires std::integral<T>
std::integral auto gcd4(T a, T b) { 
    if (b == 0) 
        return a;    
    else 
        return gcd(b, a % b); 
}
//Concepts is generic(duck typing) type
std::integral auto gcd5(std::integral auto a, std::integral auto b) 
{
    if (b == 0)
        return a;
    else 
        return gcd1(b, a % b);
}

auto gcd6(auto a, auto b)
{
    if (b == 0)
        return a;
    else
        return gcd1(b, a % b);
}

template <unsigned int i> 
requires (i <= 20)
int sum(int j) { 
    return i + j; 
}

void requiresClause()
{
    std::cout << '\n'; 
    std::cout << "sum<20>(2000): " << sum<20>(2000) << '\n', 
    //std::cout << "sum<23>(2000): " << sum<23>(2000) << '\n',  // ERROR
    std::cout << '\n';
}

void ConceptsTest2()
{
    std::cout << "gcd(10, 2)=" << gcd(10, 2) << '\n';
    //std::cout << "gcd(10., 2.)=" << gcd(10., 2.) << '\n';
    std::cout << "gcd1(10, 2)=" << gcd1(10, 2) << '\n';
    std::cout << "gcd2(10, 2)=" << gcd2(10, 2) << '\n';
    std::cout << "gcd3(10, 2)=" << gcd3(10, 2) << '\n';
    std::cout << "gcd3(10l, 2)=" << gcd3(10, 2l) << '\n';
    std::cout << "gcd4(10, 2)=" << gcd4(10, 2) << '\n';
    std::cout << "gcd5(10, 2)=" << gcd5(10, 2) << '\n';
    std::cout << "gcd6(10, 2)=" << gcd6(10, 2) << '\n';
    //std::cout << "gcd6(10, 2)=" << gcd6(10, 2.) << '\n';//Ошибка	C2297% : недопустимо, правый оператор имеет тип double

    requiresClause();
}

struct Test {};
void ConceptsTest3()//4.1.4.4.1 Compile-Time Predicates
{
    std::cout << '\n'; 
    std::cout << std::boolalpha; 
    std::cout << "std::three_way_comparable<int>: " << std::three_way_comparable<int> << "\n"; 
    std::cout << "std::three_way_comparable<double>: "; if (std::three_way_comparable<double>) std::cout << "True"; else std::cout << "False";
    std::cout << "\n\n"; static_assert(std::three_way_comparable<std::string>); 
    
    std::cout << "std::three_way_comparable<Test>: "; 
    if constexpr (std::three_way_comparable<Test>)
        std::cout << "True"; 
    else 
        std::cout << "False"; 
    std::cout << '\n'; 
    
    std::cout << "std::three_way_comparable<std::vector<int>>: "; 
    if constexpr (std::three_way_comparable<std::vector<int>>)
        std::cout<< "True"; 
    else 
        std::cout << "False";
}

template < typename T>
struct MyVector {
    void push_back(const T&) requires std::copyable<T> {}
};

void ConceptsTest4()//4.1.4.4.3 Generic Member Functions
{
    struct NotCopyable { 
        NotCopyable() = default; 
        NotCopyable(const NotCopyable&) = delete; 
    }; 
    
    MyVector<int> myVec1; 
    myVec1.push_back(2020); 
    MyVector<NotCopyable> myVec2;
    //myVec2.push_back(NotCopyable());  // ERROR because not copyable
}

template < std::integral... Args>
bool all(Args... args) { return (... && args); }

template < std::integral... Args>
bool any(Args... args) { return (... || args); }

template < std::integral... Args>
bool none(Args... args) { return not(... || args); }

void ConceptsTest5()//4.1.4.4.4 Variadic Templates
{
    std::cout << std::boolalpha << '\n'; 
    std::cout << "all(5, true, false): " << all(5, true, false) << '\n';     
    std::cout << "any(5, true, false): " << any(5, true, false) << '\n';    
    std::cout << "none(5, true, false): " << none(5, true, false) << '\n'; 
    //std::cout << "none(5., true, false): " << none(5., true, false) << '\n';
}

#pragma region 4.1.4.4.5 concept overloading
#include <forward_list> 
#include <list> 
#include <vector> 
template < std::forward_iterator I>
void advance(I & iter, int n) { 
    std::cout << "forward_iterator" << '\n'; 
}

template < std::bidirectional_iterator I>
void advance(I & iter, int n) { 
    std::cout << "bidirectional_iterator" << '\n'; 
}

template < std::random_access_iterator I>
void advance(I & iter, int n) { 
    std::cout << "random_access_iterator" << '\n'; 
}

void ConceptsTest6()
{
#if 0
    std::cout << '\n';
    std::forward_list forwList{ 1, 2, 3 };     
    std::forward_list<int>::iterator itFor = forwList.begin();
    advance(itFor, 2); 
    
    std::list li{ 1, 2, 3 }; 
    std::list<int>::iterator itBi = li.begin(); 
    advance(itBi, 2); 
    
    std::vector vec{ 1, 2, 3 }; 
    std::vector<int>::iterator itRa = vec.begin(); 
    advance(itRa, 2); 
    std::cout << '\n';
#endif
}
#pragma endregion

#pragma region 4.1.4.4.6 Template Specialization(132)
template <typename T> 
struct Vector { 
    Vector() { 
        std::cout << "Vector<T>" << '\n'; 
    }
}; 

template <std::regular Reg>
struct Vector<Reg> {
    Vector() {
        std::cout << "Vector<std::regular>" << '\n';
    }
};

void ConceptsTest7()
{
    std::cout << '\n'; 
    Vector<int> myVec1; 
    Vector<int&> myVec2; 
    std::cout << '\n';
}
#pragma endregion

void ConceptsTests()
{
    ConceptsTest1();
    ConceptsTest2();
    ConceptsTest3();
    ConceptsTest4();
    ConceptsTest5();
    ConceptsTest6();
    ConceptsTest7();
}

//4.1.7.2 Concepts Library
void same_as()
{
    std::cout << "std::same_as<int,int>:" << std::same_as < int, int> << '\n';
    std::cout << "std::same_as<double,int>:" << std::same_as < double, int> << '\n';
}

class A {};

class B : public A {};
class C : private A {};

void derived_from() {
    // std::derived_from == true only for public inheritance or exact same class
    static_assert(std::derived_from<B, B> == true);      // same class: true
    static_assert(std::derived_from<int, int> == false); // same primitive type: false
    static_assert(std::derived_from<B, A> == true);      // public inheritance: true
    static_assert(std::derived_from<C, A> == false);     // private inheritance: false

    // std::is_base_of == true also for private inheritance
    static_assert(std::is_base_of_v<B, B> == true);      // same class: true
    static_assert(std::is_base_of_v<int, int> == false); // same primitive type: false
    static_assert(std::is_base_of_v<A, B> == true);      // public inheritance: true
    static_assert(std::is_base_of_v<A, C> == true);      // private inheritance: true
}

void convertible_to()
{
    std::cout << "std::convertible_to<int,long int>:" << std::convertible_to<int, long int> << '\n';
    std::cout << "std::convertible_to<long int,int>:" << std::convertible_to<long int, int> << '\n';
    std::cout << "std::convertible_to<int,std::vector<int>>:" << std::convertible_to<int, std::vector<int>> << '\n';
}

void common_reference_with()
{
}

class CallableCls {
public:
    int operator()(int a) {}
    int operator()() {}
};
void CallableConcepts()
{
    std::cout << "std::invocable<decltype(CallableConcepts), int>:" << std::invocable<decltype(CallableConcepts)> << '\n';
    std::cout << "std::invocable<CallableCls, int>:" << std::invocable<CallableCls, int> << '\n';
    std::cout << "std::invocable<CallableCls>:" << std::invocable<CallableCls> << '\n';
    std::cout << "std::invocable<regular_invocable, int>:" << std::regular_invocable<CallableCls, int> << '\n';
}

//4.1.7.4 Iterators Library
#include <iterator>

void Iterators()
{
    std::vector<int> v;
    auto it = v.begin();
    std::cout << "std::random_access_iterator<decltype(it)>:" << std::random_access_iterator<decltype(it)> << '\n';
    std::cout << "std::input_iterator<decltype(it)>:" << std::input_iterator<decltype(it)> << '\n';
    std::cout << "std::output_iterator<decltype(it)>:" << std::output_iterator<decltype(it),int> << '\n';
    std::cout << "std::forward_iterator<decltype(it)>:" << std::forward_iterator<decltype(it)> << '\n';
    std::cout << "std::bidirectional_iterator<decltype(it)>:" << std::bidirectional_iterator<decltype(it)> << '\n';
    std::cout << "std::contiguous_iterator<decltype(it)>:" << std::contiguous_iterator<decltype(it)> << '\n';
}

void ConceptsLibrary()
{
    std::cout << std::boolalpha;
//4.1.7.2.1 Language-related concepts
    std::cout << "Language-related Concepts\n";
    same_as();
    derived_from();
    convertible_to();
    common_reference_with();
    //common_with
    //assignable_from
    //swappable
//4.1.7.2.2 Arithmetic Concepts
    std::cout << "Arithmetic Concepts\n";
    //integral
    //signed_integral
    //unsigned_integral
    //floating_point
//4.1.7.2.3 Lifetime Concepts
    std::cout << "Lifetime Concepts\n";
    //destructible
    //constructible_from
    //default_constructible
    //move_constructible
    //copy_constructible
//4.1.7.2.4 Comparison Concepts
    std::cout << "Comparison Concepts\n";
    //equality_comparable
    //totally_ordered
//4.1.7.2.5 Object Concepts
    std::cout << "Object Concepts\n";
    //movable
    //copyable
    //semiregular
    //regular
//4.1.7.2.6 Callable Concepts
    std::cout << "CallableConcepts\n";
    //invocable
    //regular_invocable : a type models invocableand equality - preserving, and does not modify the function arguments; equality - preserving means the it produces the same output when given the same input
    //predicate : a type models a predicate if it models invocableand returns a boolean
    CallableConcepts();
//4.1.7.3 General Utilities Library
//4.1.7.4 Iterators Library
    //https://en.cppreference.com/w/cpp/iterator
    std::cout << "Iterators\n";
    //input_iterator
    //output_iterator
    //forward_iterator
    //bidirectional_iterator
    //random_access_iterator
    //contiguous_iterator
    Iterators();
//4.1.7.4.1 Algorithm Concepts
    //  https://en.cppreference.com/w/cpp/header/iterator
    //permutable : in - place reordering of elements is possible
    //mergeable : merging sorted sequences into an output sequence is possible
    //sortable : permuting a sequence into an ordered sequence is possible
//4.1.7.5 Ranges Library <ranges>
    // https://en.cppreference.com/w/cpp/header/ranges
    //std::ranges::range
}

//4.1.8 Defining Concepts
//4.1.8.2.1 Simple Requirements
template<typename T>
concept MyAddable = requires (T a, T b) 
{
    a + b; 
};

template<typename T>
concept MyCallable = requires (T a)
{
    a();
};

//Requirements on return types (a.k.a compound requirements)
//https://www.sandordargo.com/blog/2021/03/17/write-your-own-cpp-concepts-part-ii

template <typename T>
concept HasSquare = requires (T t) {
    {t.square()} -> std::convertible_to<double>;
};
class QSquare
{
public:
    double square()const { return 0; };
};
void DefiningConcepts()
{
    std::cout << "MyAddable<int>:" << MyAddable<int> << '\n';
    std::cout << "MyAddable<A>:" << MyAddable<A> << '\n';
    std::cout << "MyCallable<int>:" << MyCallable<int> << '\n';
    std::cout << "MyCallable<CallableCls>:" << MyCallable<CallableCls> << '\n';
    std::cout << "HasSquare<QSquare>:" << HasSquare<QSquare> << '\n';
    std::cout << "HasSquare<A>:" << HasSquare<A> << '\n';
    std::cout << "HasSquare<int>:" << HasSquare<int> << '\n';
}

void ConceptsTest()
{
    ConceptsTests();
    ConceptsLibrary();
    DefiningConcepts();
}

#pragma endregion ConceptsTest

//import std::core;

#pragma region ModulesTest
import math;
void ModulesTest(){
    std::cout << "add(2000, 20)=" << add(2000, 20) << "\n";
}
#pragma endregion ModulesTest

#pragma region Ranges library
#ifdef __cpp_lib_ranges
#include <ranges>
#endif
void RangesTest()
{
#ifdef __cpp_lib_ranges
    std::vector<int> ints{ 0, 1, 2, 3, 4, 5 };
    auto even = [](int i) { return i % 2 == 0; };
    auto square = [](int i) { return i * i; };

    for (int i : ints | std::views::filter(even) | std::views::transform(square))
    {
        std::cout << i << ' ';             // 0 4 16
    }
#endif
}
#pragma endregion Ranges library

#pragma region Coroutines
Generator<int> cor()
{
    co_yield 1;
    co_yield 2;
    co_yield 3;
    co_yield 5;
}

Generator<std::string> cor_strings()
{
    co_yield "s1";
    co_yield "s2";
    co_yield "s3";
    co_yield "s5";
}

static Generator<int> getNext(int start = 0, int step = 1, int n = 1000)
{
    auto value = start;
    for (int i = 0; i < n; i++) {
        co_yield value;
        value += step;
    }
}

static Generator<int> Fib(int i0, int i1, int n)
{
    int n0 = i0;
    int n1 = i1;
    for (int i = 0; i < n; i++) {
        co_yield n0;
        int n2 = n0 + n1;
        n0 = n1;
        n1 = n2;
    }
}

static Generator<int> CreateGenerator(bool b=true)
{
    if (b)
        return Fib(0, 1, 10);
    else
        return Fib(1, 2, 10);
}

void CoroutinesTest1()
{
    std::cout << "\ncor():";    
    for (auto gen = cor(); gen.next();)
        std::cout << " " << gen.getValue();

    std::cout << "\ncor_strings():";
    for (auto gen = cor_strings(); gen.next();)
        std::cout << " " << gen.getValue();

    std::cout << "\ngetNext(0,1,10):";
    for (auto gen = getNext(0, 1, 10); gen.next();)
        std::cout << " " << gen.getValue();


    std::cout << "\ngetNext(1, -1, 20):";    
    for (auto gen = getNext(1, -1, 20); gen.next();)
        std::cout << " " << gen.getValue();

    std::cout << "\nFib():";
    for (auto gen = Fib(0,1,20); gen.next();)
        std::cout << " " << gen.getValue();

    std::cout << "\n";
}

void CoroutinesCopyTest()
{
    Generator<int> gen = getNext(0, 1, 10);
    //Generator<int> genCopy;
    //genCopy = gen;
    std::cout << gen.nextValue() << "\n";
    //std::cout << genCopy.nextValue() << "\n";
    auto g = CreateGenerator();
    std::cout << g.nextValue() << "\n";
}


template<class GENERATOR>
static GENERATOR Compose(GENERATOR& gen1, GENERATOR& gen2)
{
    for (;;)
    {
        bool next1 = gen1.next();
        if(next1)
            co_yield gen1.getValue();
        bool next2 = gen2.next();
        if (next2)
            co_yield gen2.getValue();
        if (!next1 && !next2)
            break;
    }
}

void CoroutinesComposeTest()
{
    auto gen1 = Fib(0, 1, 10);
    auto gen2 = getNext(1000, 1, 10);
    std::cout << "\nCompose(Fib(0, 1, 10),getNext(1000, 1, 10)):\n";
    auto gen = Compose(gen1, gen2);
    for (; gen.next();)
        std::cout << " " << gen.getValue();

    std::cout << "\n";
}

void CoroutinesTest()
{
    CoroutinesTest1();
    CoroutinesCopyTest();
    CoroutinesComposeTest();
}

#pragma endregion Coroutines

//spaceship_operator_test(3-way comparison operator)
//https ://habr.com/ru/company/microsoft/blog/458242/
//  auto operator<=>(const IntWrapper&) const = default;

struct MyInt {
    int value;
    int value2=0;
    MyInt(int value)
        : value{ value } { }
    auto operator<=>(const MyInt&) const = default;
};

class Int {
public:
    int i = 0;
    Int(int _i) :i(_i) {}
    auto operator<=>(const Int& v) const {
        std::strong_ordering r;
        r._Value=i - v.i;
        return  r;
    }
};

void spaceship_operator_test()
{
    bool ret = 1 < 2;
    auto spaceshipVal = Int(1) <=> Int(2);
    ret = spaceshipVal > 0;
    auto spaceshipVal1=MyInt(1) <=> MyInt(2);

    assert(MyInt(1) < MyInt(2));
    assert(MyInt(1) <= MyInt(2));
    assert(MyInt(1) == MyInt(1));
    assert(MyInt(1) >= MyInt(1));
    assert(MyInt(2) > MyInt(1));
    //
    assert(Int(1) <  Int(2));
    assert(Int(1) <= Int(2));
    //assert(Int(1) == Int(1));
    assert(Int(1) >= Int(1));
    assert(Int(2) >  Int(1));
}

struct Point2D { int x;  int y; };
class Point3D { public:  int x;  int y;  int z; };
void aggregate_initialization()
{
    Point2D point2D{ .x = 1, .y = 2 }; 
    // Point2D point2d {.y = 2, .x = 1};         // error
    Point3D point3D {.x = 1, .y = 2, .z = 2};   
    // Point3D point3D {.x = 1, .z = 2}          // {1, 0, 2}
    std::cout << "point2D: " << point2D.x << " " << point2D.y << "\n";
    std::cout << "point3D: " << point3D.x << " " << point3D.y << " " << point3D.z << "\n";
}

consteval int sqr(int n) { return n * n; }
void consteval_constinit()
{
    constexpr int r = sqr(100);  // OK
    //int x = 100;int r2 = sqr(x);             // Error
}

//template conctructor

struct Implicit { 
    template <typename T>
    Implicit(T t)
    {
        std::cout << "Implicit(" << t << ")\n";
    }
};

struct Explicit {
    template <typename T>
    explicit Explicit(T t)
    {
        std::cout << "Explicit(" << t << ")\n";
    }
};

void generic_constructor()
{
    Implicit imp1(1);
    Implicit imp2=2;
    Implicit imp3{"Implicit"};

    //Explicit exp1 = "implicit";  // Error
    Explicit exp2{"explicit"};
}

void Template_Improvements()
{
    generic_constructor();
}

void Lambda_Improvements()
{
    auto foo = []<typename T>(std::vector<T> const& vec) {
        // do vector-specific stuff    
    };
    auto f=foo;
    f(std::vector<int>());
    f(std::vector<double>());
    auto plus = [](auto a, auto b)->auto {
        return a + b;
    };
    plus(1, 2);
    plus(1, 2.);
}

#include <span>
void copy(std::span<const int> src, std::span<int> des) {}
void lib_std_span()
{
    int arr1[] = { 1, 2, 3 };
    int arr2[] = { 3, 4, 5 };    
    copy(arr1, arr2);
}

/*std::vector and std::string have constexpr constructors and can, therefore, be used at compile time. 
All standard library containers support consistent container erasure and the associative containers support a contains member function. 
Additionally, std::string allows checking for a prefix or suffix .
*/

#if __cpp_lib_constexpr_vector
//constexpr Containersand Algorithms in C++20
// 
//constexpr auto r=std::string();
constexpr char constString[] = "constString";
//constexpr std::string constString = "constString";

void Container_Improvements()
{
    //https://www.modernescpp.com/index.php/constexpr-vector-and-string-in-c-20
    std::cout << std::endl;

    //constexpr std::vector myVec{ 15, -5, 0, 5, 10 };
    //constexpr std::sort(myVec.begin(), myVec.end());
    //for (auto v : myVec) std::cout << v << " ";
    //std::cout << "\n\n";

    using namespace std::string_literals;
    //constexpr std::vector<std::string> myStringVec{ "Stroustrup"s, "Vandevoorde"s,"Sutter"s, "Josuttis"s, "Wong"s };
    //constexpr std::sort(myStringVec.begin(), myStringVec.end());
    //for (auto s : myStringVec) std::cout << s << " ";

    //std::cout << "\n\n";
}
#endif

void mathematical_constants()
{
#if 0
    {
        int α, β, ɣ, ɤ, ꙋ, ү, Γ, γ;
        int φ, ϕ; 
        int ɛ;
    }
    auto γ = std::numbers::egamma;
    auto π = std::numbers::pi;
    auto ϕ = std::numbers::phi;
    auto ɛ = std::numbers::e;
    std::cout << "γ=" << γ << "\n";
    std::cout << "π=" << π << "\n";
    std::cout << "ϕ=" << ϕ << "\n";
    std::cout << "ɛ=" << ɛ << "\n";
#endif
}

void bit_manipulation()
{
    std::uint8_t num = 0b10110010;
    std::cout << std::has_single_bit(num) << '\n';            // false
    std::cout << std::bit_width(unsigned(5)) << '\n';         // 3
    std::cout << std::bitset<8>(std::rotl(num, 2)) << '\n';   // 11001010
    std::cout << std::bitset<8>(std::rotr(num, 2)) << '\n';   // 10101100
    std::cout << std::bitset<8>(std::rotr(num, 2)) << '\n';   // 10101100
}

#ifdef __cpp_lib_format
#include <format>
#endif
void Calendar_TimeZones()
{
#ifdef __cpp_lib_format
    using namespace std::chrono;
    auto time = floor<milliseconds>(system_clock::now());
    auto localTime = zoned_time<milliseconds>(current_zone(), time);
    auto berlinTime = zoned_time<milliseconds>("Europe/Berlin", time);
    auto newYorkTime = zoned_time<milliseconds>("America/New_York", time);
    auto tokyoTime = zoned_time<milliseconds>("Asia/Tokyo", time);
    std::cout << time << '\n';        // 2020-05-23 19:07:20.290
    std::cout << localTime << '\n';   // 2020-05-23 21:07:20.290 CEST
    std::cout << berlinTime << '\n';  // 2020-05-23 21:07:20.290 CEST
#endif
}

void Formatting_Library()
{
#ifdef __cpp_lib_format
    std::cout << std::format("The answer is {}.\n", 42);
    std::cout << std::format("I'd rather be {1} than {0}.\n", "right", "happy");        // s == "I'd rather be happy than right."

    //https://en.cppreference.com/w/cpp/utility/format/format_to
    std::string buf;
    std::format_to(std::back_inserter(buf), "{}", 42);    // replaces itoa(42, buffer, \10)
    std::format_to(std::back_inserter(buf), "{:x}", 42);  // replaces itoa(42, buffer, \16)

    /*Standard format specification
    fill-and-align(optional) sign(optional) #(optional) 0(optional) width(optional) precision(optional) L(optional) type(optional)		

    The sign, # and 0 options are only valid when an integer or floating-point presentation type is used.

    fill and align
    fill-and-align is an optional fill character (which can be any character other than { or }), followed by one of the align options <, >, ^. The meaning of align options is as follows:

    <: Forces the field to be aligned to the start of the available space. This is the default when a non-integer non-floating-point presentation type is used.
    >: Forces the field to be aligned to the end of the available space. This is the default when an integer or floating-point presentation type is used.
    ^: Forces the field to be centered within the available space by inserting ⌊
    n/2 characters before and n/2 characters after the value, where n is the total number of fill characters to insert.
    */
    char c = 120;
    auto s0 = std::format("{:6}", 42);    // value of s0 is "    42"
    auto s1 = std::format("{:6}", 'x');   // value of s1 is "x     "
    auto s2 = std::format("{:*<6}", 'x'); // value of s2 is "x*****"
    auto s3 = std::format("{:*>6}", 'x'); // value of s3 is "*****x"
    auto s4 = std::format("{:*^6}", 'x'); // value of s4 is "**x***"
    auto s5 = std::format("{:6d}", c);    // value of s5 is "   120"
    auto s6 = std::format("{:6}", true);  // value of s6 is "true  "

    double inf = std::numeric_limits<double>::infinity();
    double nan = std::numeric_limits<double>::quiet_NaN();
    auto s00 = std::format("{0:},{0:+},{0:-},{0: }", 1);   // value of s0 is "1,+1,1, 1"
    auto s01 = std::format("{0:},{0:+},{0:-},{0: }", -1);  // value of s1 is "-1,-1,-1,-1"
    auto s02 = std::format("{0:},{0:+},{0:-},{0: }", inf); // value of s2 is "inf,+inf,inf, inf"
    auto s03 = std::format("{0:},{0:+},{0:-},{0: }", nan); // value of s3 is "nan,+nan,nan, nan"

    c = 120;
    auto s11 = std::format("{:+06d}", c);   // value of s1 is "+00120"
    auto s12 = std::format("{:#06x}", 0xa); // value of s2 is "0x000a"
    auto s13 = std::format("{:<06}", -42);  // value of s3 is "-42   "
                                           // (0 is ignored because of < alignment)

    float pi = 3.14f;
    auto s21 = std::format("{:10f}", pi);           // s1 = "  3.140000" (width = 10)
    auto s22 = std::format("{:{}f}", pi, 10);       // s2 = "  3.140000" (width = 10)
    auto s23 = std::format("{:.5f}", pi);           // s3 = "3.14000" (precision = 5)
    auto s24 = std::format("{:.{}f}", pi, 5);       // s4 = "3.14000" (precision = 5)
    auto s25 = std::format("{:10.5f}", pi);         // s5 = "   3.14000"
                                                   // (width = 10, precision = 5)
    auto s26 = std::format("{:{}.{}f}", pi, 10, 5); // s6 = "   3.14000"
                                                   // (width = 10, precision = 5)
    //auto b21 = std::format("{:{}f}", pi, 10.0);     // throws: width is not of integral type 
    //auto b22 = std::format("{:{}f}", pi, -10);      // throws: width is negative
    //auto b23 = std::format("{:.{}f}", pi, 5.0);     // throws: precision is not of integral type
#endif
}

void jthread_test()
{
    using namespace std::chrono_literals;
    std::cout << '\n'; 
    std::jthread nonInterruptible([] {  
        int counter{ 0 };
        while (counter < 10) { 
            std::this_thread::sleep_for(0.2s); 
            std::cerr << "nonInterruptible: " << counter << '\n'; 
            ++counter; 
        }}); 
    
    std::jthread interruptible([](std::stop_token stoken) {            
        int counter{ 0 }; 
        while (counter < 10) { 
            std::this_thread::sleep_for(0.2s); 
            if (stoken.stop_requested()) return; 
            std::cerr << "interruptible: " << counter << '\n'; 
            ++counter; 
        }}); 
    
    std::this_thread::sleep_for(1s); 
    std::cerr << '\n'; 
    std::cerr << "Main thread interrupts both jthreads" << std::endl; 
    nonInterruptible.request_stop(); 
    interruptible.request_stop();
    std::cout << '\n'; 
}

void sayHello(std::string name) {
    //std::cout
    std::osyncstream(std::cout) 
        << "Hello from " << name << '\n';
}

void Synchronized_Outputstreams()
{
    std::jthread t3(sayHello, "t3");   
    std::jthread t4(sayHello, "t4");   
    std::jthread t5(sayHello, "t5");   
    std::jthread t6(sayHello, "t6");   
    std::jthread t7(sayHello, "t7");   
    std::jthread t8(sayHello, "t8");   
    std::jthread t9(sayHello, "t9");   
    std::jthread t10(sayHello, "t10");        
    std::cout << '\n';
}

void cpp20_tests()
{
    //The Big Four
    ConceptsTest();
    ModulesTest();
    RangesTest();
    CoroutinesTest();

    //Core Language
    spaceship_operator_test();//3-way comparison operator
    aggregate_initialization();
    consteval_constinit();
    Template_Improvements();
    Lambda_Improvements();

    //Library
    lib_std_span();
#if __cpp_lib_constexpr_vector
    Container_Improvements();
#endif
    mathematical_constants();
    bit_manipulation();
    Calendar_TimeZones();
    Formatting_Library();
    //Concurrency
    jthread_test();
    Synchronized_Outputstreams();
    //p188, 4.1.9.1 The Concepts Equal and Ordering
    //p215, 4.2 Modules
}

class runner20
{
public:
    runner20()
    {
        cpp20_tests();
    }
};
static runner20 run;
