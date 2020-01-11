#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    struct BarTag
    {
    };

    struct FooTag
    {
    };

    using Bar = btshn::Comparable<int, BarTag>;

    using Foo = btshn::Comparable<int, FooTag>;
} // namespace

TEST(Comparable, ctor)
{
    Foo f{0};

    ASSERT_EQ(0, static_cast<int &>(f));
    ASSERT_EQ(0, static_cast<int const &>(f));
}

TEST(Comparable, equal)
{
    Foo f1{0};
    Foo f2{0};

    ASSERT_EQ(f1, f2);
}

TEST(Comparable, not_equal)
{
    Foo f1{0};
    Foo f2{1};

    ASSERT_NE(f1, f2);
}

#if 0
TEST(Comparable, invalid_compare)
{
    Foo f{0};
    Bar b{0};

    ASSERT_EQ(f, b);
}
#endif
