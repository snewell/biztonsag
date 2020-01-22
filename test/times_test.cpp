#include <biztonsag/comparable.hpp>
#include <biztonsag/mixins.hpp>
#include <biztonsag/times.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(WidthBase, int);

    BTSHN_MAKE_MIXIN(Width, WidthBase, btshn::Times<Width, int>);
    BTSHN_MAKE_MIXIN(Width2, WidthBase, btshn::Times<Width2, int, Width>);
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

TEST(Times, simple_times_other) // NOLINT
{
    Width2 const orig{2};
    Width2 const expected{10};
    auto sum = orig * 5;
    static_assert(std::is_same<Width, std::remove_cv_t<decltype(sum)>>::value,
                  "Unexpected type");

    ASSERT_EQ(expected, sum);
}
#if 0
TEST(Times, simple_times_equals_other) // NOLINT
{
    Width2 const expected{10};
    Width2 w{0};
    w += 10ul;

    ASSERT_EQ(expected, w);
}
#endif
