#include <biztonsag/arithmetic.hpp>
#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Width, int);
}

namespace btshn
{
    BTSHN_MAKE_PLUS(Width, int, Width);
    BTSHN_MAKE_PLUS(Width, unsigned int, std::uint64_t);
} // namespace btshn

TEST(Plus, simple_plus) // NOLINT
{
    auto const starting = 0;
    auto const rhs = 10;
    auto const result = starting + rhs;

    Width const orig{starting};
    Width const expected{result};
    auto sum = orig + rhs;

    ASSERT_EQ(expected, sum);
}

TEST(Plus, simple_plus_unsigned) // NOLINT
{
    auto const starting = 0;
    auto const rhs = 10U;
    auto const result = starting + rhs;

    Width const orig{starting};
    auto const sum = orig + rhs;

    static_assert(
        std::is_same<std::remove_cv_t<decltype(sum)>, std::uint64_t>::value,
        "Unexpected type");
    ASSERT_EQ(result, sum);
}

TEST(Plus, simple_plus_equals) // NOLINT
{
    auto const starting = 0;
    auto const rhs = 10;
    auto const result = starting + rhs;

    Width const expected{result};
    Width w{0};
    w += rhs;

    ASSERT_EQ(expected, w);
}
