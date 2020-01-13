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

    BTSHN_MAKE_COMPARABLE(int, Baz);
} // namespace

TEST(Comparable, ctor) // NOLINT
{
    Foo f{0};

    ASSERT_EQ(0, *f);
    ASSERT_EQ(0, *f);
}

TEST(Comparable, equal) // NOLINT
{
    Foo f1{0};
    Foo f2{0};

    ASSERT_EQ(f1, f2);
}

TEST(Comparable, not_equal) // NOLINT
{
    Foo f1{0};
    Foo f2{1};

    ASSERT_NE(f1, f2);
}

TEST(ComparableMacro, compiles) // NOLINT
{
    Baz b{0};
}

#if 0
TEST(Comparable, invalid_compare) // NOLINT
{
    Foo f{0};
    Bar b{0};

    ASSERT_EQ(f, b);
}
#endif
