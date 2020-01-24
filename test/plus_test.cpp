#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);

    BTSHN_MAKE_PLUS(Width, int, Width)
    BTSHN_MAKE_PLUS_ASSIGN(Width, int)
    BTSHN_MAKE_PLUS(Width, unsigned int, std::uint64_t)
} // namespace

TEST(Plus, simple_plus) // NOLINT
{
    Width const orig{0};
    Width const expected{10};
    auto sum = orig + 10;

    ASSERT_EQ(expected, sum);
}

TEST(Plus, simple_plus_unsigned) // NOLINT
{
    Width const orig{0};
    std::uint64_t const expected{10};
    auto const sum = orig + 10U;

    static_assert(
        std::is_same<std::remove_cv_t<decltype(sum)>, std::uint64_t>::value,
        "Unexpected type");
    ASSERT_EQ(expected, sum);
}

TEST(Plus, simple_plus_equals) // NOLINT
{
    Width const expected{10};
    Width w{0};
    w += 10;

    ASSERT_EQ(expected, w);
}
