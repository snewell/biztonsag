#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

#include <biztonsag/orderable.hpp>

namespace
{
    BTSHN_MAKE_ORDERABLE(std::string, SafeString);
    BTSHN_MAKE_ORDERABLE(std::string, UnsafeString);

    SafeString encode(UnsafeString const & us)
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

int main(int argc, char ** argv)
{
    for(auto i = 1; i < argc; ++i)
    {
        UnsafeString us{argv[i]};
        auto ss = encode(us);
        // auto ss2 = encode(ss);
        // print(us);
        print(ss);
    }
    return 0;
}
