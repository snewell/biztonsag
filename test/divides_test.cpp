#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);

    BTSHN_MAKE_DIVIDES(Width, int, Width)
    BTSHN_MAKE_DIVIDES_ASSIGN(Width, int)
} // namespace

TEST(Divides, simple_divides) // NOLINT
{
    auto const starting = 10;
    auto const divisor = 5;
    auto const result = starting / divisor;

    Width const orig{starting};
    Width const expected{result};
    auto sum = orig / divisor;

    ASSERT_EQ(expected, sum);
}

TEST(Divides, simple_divides_equals) // NOLINT
{
    auto const starting = 10;
    auto const divisor = 5;
    auto const result = starting / divisor;

    Width const expected{result};
    Width w{starting};
    w /= divisor;

    ASSERT_EQ(expected, w);
}
