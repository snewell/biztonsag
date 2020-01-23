#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);

    BTSHN_MAKE_MINUS(Width, int, Width)
    BTSHN_MAKE_MINUS_ASSIGN(Width, int)
} // namespace

TEST(Minus, simple_minus) // NOLINT
{
    Width const orig{10};
    Width const expected{4};
    auto sum = orig - 6;

    ASSERT_EQ(expected, sum);
}

TEST(Minus, simple_minus_equals) // NOLINT
{
    Width const expected{4};
    Width w{10};
    w -= 6;

    ASSERT_EQ(expected, w);
}
