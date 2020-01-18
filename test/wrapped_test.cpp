#include <biztonsag/wrapped.hpp>

#include <vector>

#include <gtest/gtest.h>

namespace
{
    struct FooTag
    {
    };

    using Foo = btshn::Wrapped<int, FooTag>;

    BTSHN_MAKE_WRAPPED(int, Bar);

    static_assert(!std::is_same<Foo, Bar>::value,
                  "Foo and Bar shouldn't be the same type");
    static_assert(!std::is_convertible<Foo, Bar>::value,
                  "Foo shouldn't be implicitly convertable to Bar");
    static_assert(!std::is_convertible<Bar, Foo>::value,
                  "Bar shouldn't be implicitly convertable to Foo");
} // namespace

TEST(Wrapped, access) // NOLINT
{
    Foo f{0};
    ASSERT_EQ(0, *f);

    *f = 10;
    ASSERT_EQ(10, *f);
}

TEST(Wrapped, const_access) // NOLINT
{
    Foo const f{0};
    ASSERT_EQ(0, *f);
}
