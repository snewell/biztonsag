#include <biztonsag/incr.hpp>

#include <gtest/gtest.h>

#include <biztonsag/comparable.hpp>

namespace
{
    BTSHN_MAKE_COMPARABLE(Index, int);
    BTSHN_MAKE_COMPARABLE(Counter, int);
    BTSHN_MAKE_COMPARABLE(Super, int);

    template <typename T>
    struct Increment : ::testing::Test
    {
    };

    using IncrementTypes = ::testing::Types<Index, Super>;
    TYPED_TEST_SUITE(Increment, IncrementTypes, );

    template <typename T>
    struct Decrement : ::testing::Test
    {
    };

    using DecrementTypes = ::testing::Types<Counter, Super>;
    TYPED_TEST_SUITE(Decrement, DecrementTypes, );
} // namespace

namespace btshn
{
    BTSHN_MAKE_INCREMENTABLE(Index);
    BTSHN_MAKE_DECREMENTABLE(Counter);

    BTSHN_MAKE_INCREMENTABLE(Super);
    BTSHN_MAKE_DECREMENTABLE(Super);
} // namespace btshn

TYPED_TEST(Increment, pre) // NOLINT
{
    TypeParam i{0};
    TypeParam const expected{1};

    auto const result = ++i;
    ASSERT_EQ(result, expected);
    ASSERT_EQ(result, i);
    // this last check is redundant, but doesn't hurt
    ASSERT_EQ(expected, i);
}

TYPED_TEST(Increment, post) // NOLINT
{
    TypeParam i{0};
    TypeParam const last{0};
    TypeParam const next{1};

    auto const result = i++;
    ASSERT_EQ(result, last);
    ASSERT_EQ(i, next);
}

TYPED_TEST(Decrement, pre) // NOLINT
{
    TypeParam i{1};
    TypeParam const expected{0};

    auto const result = --i;
    ASSERT_EQ(result, expected);
    ASSERT_EQ(result, i);
    // this last check is redundant, but doesn't hurt
    ASSERT_EQ(expected, i);
}

TYPED_TEST(Decrement, post) // NOLINT
{
    TypeParam i{1};
    TypeParam const last{1};
    TypeParam const next{0};

    auto const result = i--;
    ASSERT_EQ(result, last);
    ASSERT_EQ(i, next);
}
