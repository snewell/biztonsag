#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);

    BTSHN_MAKE_TIMES(Width, int, Width);
    BTSHN_MAKE_TIMES_ASSIGN(Width, int);
} // namespace

TEST(Times, simple_times) // NOLINT
{
    auto const starting = 2;
    auto const rhs = 10;
    auto const result = starting * rhs;

    Width const orig{starting};
    Width const expected{result};
    auto sum = orig * rhs;

    ASSERT_EQ(expected, sum);
}

TEST(Times, simple_times_equals) // NOLINT
{
    auto const starting = 2;
    auto const rhs = 5;
    auto const result = starting * rhs;

    Width const expected{result};
    Width w{starting};
    w *= rhs;

    ASSERT_EQ(expected, w);
}
