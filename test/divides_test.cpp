#include <biztonsag/comparable.hpp>
#include <biztonsag/divides.hpp>
#include <biztonsag/mixins.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(WidthBase, int);

    BTSHN_MAKE_MIXIN(Width, WidthBase, btshn::Divides<Width, int>);
    BTSHN_MAKE_MIXIN(Width2, WidthBase, btshn::Divides<Width2, int, Width>);
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

TEST(Divides, simple_divides_other) // NOLINT
{
    Width2 const orig{10};
    Width2 const expected{2};
    auto sum = orig / 5;
    static_assert(std::is_same<Width, std::remove_cv_t<decltype(sum)>>::value,
                  "Unexpected type");

    ASSERT_EQ(expected, sum);
}
