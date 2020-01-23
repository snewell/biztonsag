#include <biztonsag/comparable.hpp>
#include <biztonsag/times.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);

    BTSHN_MAKE_TIMES(Width, int, Width)
} // namespace

TEST(Times, simple_times) // NOLINT
{
    Width const orig{2};
    Width const expected{20};
    auto sum = orig * 10;

    ASSERT_EQ(expected, sum);
}

TEST(Times, simple_times_equals) // NOLINT
{
    Width const expected{10};
    Width w{2};
    w *= 5;

    ASSERT_EQ(expected, w);
}
