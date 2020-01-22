#include <biztonsag/comparable.hpp>
#include <biztonsag/minus.hpp>
#include <biztonsag/mixins.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(WidthBase, int);

    BTSHN_MAKE_MIXIN(Width, WidthBase, btshn::Minus<Width, int>);
    BTSHN_MAKE_MIXIN(Width2, WidthBase, btshn::Minus<Width2, int, Width>);
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

TEST(Minus, simple_minus_other) // NOLINT
{
    Width2 const orig{10};
    Width2 const expected{4};
    auto sum = orig - 6;
    static_assert(std::is_same<Width, std::remove_cv_t<decltype(sum)>>::value,
                  "Unexpected type");

    ASSERT_EQ(expected, sum);
}
