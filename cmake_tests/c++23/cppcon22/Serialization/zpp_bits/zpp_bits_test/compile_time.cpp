#include "zpp_bits.h"

using namespace zpp::bits::literals;

// Returns an array
// where the first bytes are those of the hello world string and then
// the 1337 as 4 byte integer.
constexpr std::array data =
    zpp::bits::to_bytes<"Hello World!"_s, 1337>();

static_assert(
    zpp::bits::from_bytes<data,
                          zpp::bits::string_literal<char, 12>,
                          int>() == std::tuple{"Hello World!"_s, 1337});
