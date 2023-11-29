#include <print>
 
int main()
{
    // Each call to std::println ends with new-line
    std::println("Please");
    std::println("enter");
 
    std::print("pass");
    std::print("word");
 
    std::println(""); // same effect as std::print("\n");
}
