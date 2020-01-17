#include <iostream>

#include <biztonsag/wrapped.hpp>

namespace
{
    BTSHN_MAKE_WRAPPED(int, Width);
    BTSHN_MAKE_WRAPPED(int, Height);
    BTSHN_MAKE_WRAPPED(int, Area);

    auto operator*(Width lhs, Height rhs)
    {
        return Area{(*lhs) * (*rhs)};
    }

    // This overload isn't used, but we can provide it since the math works
    // either way.  If we were working with types where the order of operands
    // matters, then we wouldn't provide both forms.
    auto operator*(Height lhs, Width rhs)
    {
        return rhs * lhs;
    }
} // namespace

int main() // NOLINT(modernize-use-trailing-return-type)
{
    Width const width{10};   // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    Height const height{20}; // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    auto area = width * height;
    static_assert(std::is_same_v<Area, decltype(area)>);
    std::cout << "The area is " << *area << '\n';
    return 0;
}
