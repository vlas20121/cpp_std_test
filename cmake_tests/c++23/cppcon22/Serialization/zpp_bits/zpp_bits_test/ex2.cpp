#include <string>
#include "zpp_bits.h"

constexpr auto tuple_integers()
{
    std::array<std::byte, 0x1000> data{};
    auto [in, out] = zpp::bits::in_out(data);
    out(std::tuple{1,2,3,4,5}).or_throw();

    std::tuple t{0,0,0,0,0};
    in(t).or_throw();
    return t;
}
// Compile time check.
static_assert(tuple_integers() == std::tuple{1,2,3,4,5});
