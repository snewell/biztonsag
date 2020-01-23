#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);

    BTSHN_MAKE_DIVIDES(Width, int, Width)
} // namespace

TEST(Divides, simple_divides) // NOLINT
{
    Width const orig{10};
    Width const expected{2};
    auto sum = orig / 5;

    ASSERT_EQ(expected, sum);
}

TEST(Divides, simple_divides_equals) // NOLINT
{
    Width const expected{2};
    Width w{10};
    w /= 5;

    ASSERT_EQ(expected, w);
}
