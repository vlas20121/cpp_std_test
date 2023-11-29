//https://question-it.com/questions/120075/kak-poluchit-pravilnuju-dlinu-std-u8string-v-c

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <locale>
#undef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <string>
//#include <u8string>
#include <iostream>
#include <cstdlib>
#include <locale>
#include <codecvt>
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

std::string to_string(std::u8string input)
{
    return reinterpret_cast<const char*>(input.data());
}

//auto convert(std::u8string input) -> std::u32string
std::u32string to_u32string(std::u8string input)
{
    auto first = reinterpret_cast<const char*>(input.data());
    auto last = first + input.size();

    auto result = std::u32string();

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> ucs4conv;
    try
    {
        result = ucs4conv.from_bytes(first, last);
    }
    catch (const std::range_error& e) {
        last = first + ucs4conv.converted();
        std::clog << "UCS4 failed after consuming " << std::dec << std::distance(first, last) << " characters:\n";
        result = ucs4conv.from_bytes(first, last);
    }

    return result;
}

void cpp20utf8_test()
{
    SetConsoleOutputCP(CP_UTF8);
    const char* s0 = "Hello😃😃";
    std::cout << s0 << "\n";

    const char8_t* s = u8"Hello😃😃";

    auto st = std::u8string(s);
    std::string st0 = to_string(st);
    std::cout << "s0==st0: " << (s0 == st0) << "\n";

    //std::cout << s << ",";
    std::cout <<  ",bytes      : " << st.size() << std::endl;

    auto ws = to_u32string(st);
    //std::cout << ss << ",";
    std::cout << "wide chars : " << ws.size() << std::endl;
}

class runner_cpp20utf8
{
public:
    runner_cpp20utf8()
    {
        cpp20utf8_test();
    }
};
static runner_cpp20utf8 _runner_cpp20utf8;
