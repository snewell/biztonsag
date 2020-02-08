#include <cassert>
#include <iostream>

#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>
#include <biztonsag/wrapped.hpp>

namespace
{
    BTSHN_MAKE_WRAPPED(Width, int);
    BTSHN_MAKE_WRAPPED(Height, int);

    BTSHN_MAKE_COMPARABLE(Area, int);

    // we can have biztonsag stamp out operator* automatically
    BTSHN_MAKE_TIMES(Width, Height, Area);
    BTSHN_MAKE_TIMES(Height, Width, Area);
} // namespace

int main() // NOLINT(modernize-use-trailing-return-type)
{
    Width const width{10};   // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    Height const height{20}; // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    auto const area = width * height;
    static_assert(std::is_same_v<Area, std::remove_cv_t<decltype(area)>>);
    auto const area2 = height * width;
    static_assert(std::is_same_v<Area, std::remove_cv_t<decltype(area2)>>);
    assert(area == area2); // NOLINT
    std::cout << "The area is " << *area << '\n';
    return 0;
}
