#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

#include <biztonsag/orderable.hpp>

namespace
{
    BTSHN_MAKE_ORDERABLE(SafeString, std::string);
    BTSHN_MAKE_ORDERABLE(UnsafeString, std::string);

    auto encode(UnsafeString const & us)
    {
        auto raw = *us;
        static_assert(std::is_same_v<std::string, decltype(raw)>);

        std::transform(std::begin(raw), std::end(raw), std::begin(raw),
                       [](auto v) { return std::toupper(v); });
        return SafeString{std::move(raw)};
    }

    void print(SafeString const & ss)
    {
        std::cout << (*ss) << '\n';
    }
} // namespace

int main(int argc, char ** argv) // NOLINT(modernize-use-trailing-return-type)
{
    for(auto i = 1; i < argc; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        UnsafeString us{argv[i]};
        auto ss = encode(us);
        // auto ss2 = encode(ss);
        // print(us);
        print(ss);
    }
    return 0;
}
