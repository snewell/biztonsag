#include <biztonsag/comparable.hpp>
#include <biztonsag/mixins.hpp>
#include <biztonsag/plus.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(WidthBase, int);

    BTSHN_MAKE_MIXIN(Width, WidthBase, btshn::Plus<Width, int>);
} // namespace

TEST(Plus, simple_plus)
{
    Width const orig{0};
    Width const expected{10};
    auto sum = orig + 10;

    ASSERT_EQ(expected, sum);
}

TEST(Plus, simple_plus_equals)
{
    Width const expected{10};
    Width w{0};
    w += 10;

    ASSERT_EQ(expected, w);
}
