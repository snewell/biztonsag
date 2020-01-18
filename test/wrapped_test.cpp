#include <biztonsag/wrapped.hpp>

#include <vector>

#include <gtest/gtest.h>

namespace
{
    struct FooTag
    {
    };

    using Foo = btshn::Wrapped<int, FooTag>;

    BTSHN_MAKE_WRAPPED(Bar, int);

    static_assert(!std::is_same<Foo, Bar>::value,
                  "Foo and Bar shouldn't be the same type");
    static_assert(!std::is_convertible<Foo, Bar>::value,
                  "Foo shouldn't be implicitly convertable to Bar");
    static_assert(!std::is_convertible<Bar, Foo>::value,
                  "Bar shouldn't be implicitly convertable to Foo");

    BTSHN_MAKE_WRAPPED(IntPair, std::pair<int, int>);
} // namespace

TEST(Wrapped, access_star) // NOLINT
{
    Foo f{0};
    ASSERT_EQ(0, *f);

    *f = 10;
    ASSERT_EQ(10, *f);
}

TEST(Wrapped, const_access_star) // NOLINT
{
    Foo const f{0};
    ASSERT_EQ(0, *f);
}

TEST(Wrapped, access_arrow) // NOLINT
{
    IntPair ip{std::make_pair(10, 20)};
    ASSERT_EQ(10, ip->first);
    ASSERT_EQ(20, ip->second);

    *ip = std::make_pair(20, 10);
    ASSERT_EQ(20, ip->first);
    ASSERT_EQ(10, ip->second);
}

TEST(Wrapped, const_access_arrow) // NOLINT
{
    IntPair ip{std::make_pair(10, 20)};
    ASSERT_EQ(10, ip->first);
    ASSERT_EQ(20, ip->second);
}
