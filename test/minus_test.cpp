#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);

    BTSHN_MAKE_MINUS(Width, int, Width);
    BTSHN_MAKE_MINUS_ASSIGN(Width, int);
} // namespace

TEST(Minus, simple_minus) // NOLINT
{
    auto const starting = 10;
    auto const rhs = 6;
    auto const result = starting - rhs;

    Width const orig{starting};
    Width const expected{result};
    auto sum = orig - rhs;

    ASSERT_EQ(expected, sum);
}

TEST(Minus, simple_minus_equals) // NOLINT
{
    auto const starting = 10;
    auto const rhs = 6;
    auto const result = starting - rhs;

    Width const expected{result};
    Width w{starting};
    w -= rhs;

    ASSERT_EQ(expected, w);
}
