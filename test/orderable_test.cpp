#include <biztonsag/orderable.hpp>

#include <gtest/gtest.h>

namespace
{
    struct FooTag
    {
    };

    using Foo = btshn::Orderable<int, FooTag>;

    BTSHN_MAKE_ORDERABLE(int, Bar);
} // namespace

TEST(Orderable, less) // NOLINT
{
    Foo f1{0};
    Foo f2{1};

    ASSERT_LT(f1, f2);
}

TEST(Orderable, greater) // NOLINT
{
    Foo f1{0};
    Foo f2{1};

    ASSERT_GT(f2, f1);
}

TEST(Orderable, less_equal) // NOLINT
{
    Foo f1{0};
    Foo f2{1};

    ASSERT_LE(f1, f2);
    ASSERT_LE(f1, f1);
}

TEST(Orderable, greater_equal) // NOLINT
{
    Foo f1{0};
    Foo f2{1};

    ASSERT_GE(f2, f1);
    ASSERT_GE(f2, f2);
}

TEST(OrderableMacro, compiles) // NOLINT
{
    Bar b{0};
}
