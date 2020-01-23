#include <biztonsag/orderable.hpp>

#include <vector>

#include <gtest/gtest.h>

namespace
{
    struct FooTag
    {
    };

    using Foo = btshn::Orderable<int, FooTag>;

    BTSHN_MAKE_ORDERABLE(Bar, int);

    static_assert(!std::is_same<Foo, Bar>::value,
                  "Foo and Bar shouldn't be the same type");
    static_assert(!std::is_convertible<Foo, Bar>::value,
                  "Foo shouldn't be implicitly convertable to Bar");
    static_assert(!std::is_convertible<Bar, Foo>::value,
                  "Bar shouldn't be implicitly convertable to Foo");

    static_assert(btshn::is_biztonsag_type_v<Foo>,
                  "Foo should pass is_biztonsag_type");
    static_assert(btshn::is_biztonsag_type_v<Bar>,
                  "Bar should pass is_biztonsag_type");
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
    (void)b;
}
