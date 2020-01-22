#include <biztonsag/comparable.hpp>
#include <biztonsag/mixins.hpp>
#include <biztonsag/plus.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(WidthBase, int);

    BTSHN_MAKE_MIXIN(Width, WidthBase, btshn::Plus<Width, int>);
    BTSHN_MAKE_MIXIN(Width2, WidthBase, btshn::Plus<Width2, int, Width>);
} // namespace

TEST(Plus, simple_plus) // NOLINT
{
    Width const orig{0};
    Width const expected{10};
    auto sum = orig + 10;

    ASSERT_EQ(expected, sum);
}

TEST(Plus, simple_plus_equals) // NOLINT
{
    Width const expected{10};
    Width w{0};
    w += 10;

    ASSERT_EQ(expected, w);
}

TEST(Plus, simple_plus_other) // NOLINT
{
    Width2 const orig{0};
    Width2 const expected{10};
    auto sum = orig + 10;
    static_assert(std::is_same<Width, std::remove_cv_t<decltype(sum)>>::value,
                  "Unexpected type");

    ASSERT_EQ(expected, sum);
}

#if 0
TEST(Plus, simple_plus_equals_other) // NOLINT
{
    Width2 const expected{10};
    Width2 w{0};
    w += 10ul;

    ASSERT_EQ(expected, w);
}
#endif
