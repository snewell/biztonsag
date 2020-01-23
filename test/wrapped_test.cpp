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

    static_assert(btshn::is_biztonsag_type_v<Foo>,
                  "Foo should pass is_biztonsag_type");
    static_assert(btshn::is_biztonsag_type_v<Bar>,
                  "Bar should pass is_biztonsag_type");

    BTSHN_MAKE_WRAPPED(IntPair, std::pair<int, int>);
    static_assert(btshn::is_biztonsag_type_v<IntPair>,
                  "IntPair should pass is_biztonsag_type");
} // namespace

TEST(Wrapped, access_star) // NOLINT
{
    Foo f{0};
    ASSERT_EQ(0, *f);

    auto const next = 10;
    *f = next;
    ASSERT_EQ(next, *f);
}

TEST(Wrapped, const_access_star) // NOLINT
{
    Foo const f{0};
    ASSERT_EQ(0, *f);
}

TEST(Wrapped, access_arrow) // NOLINT
{
    auto const first = 10;
    auto const second = 20;
    IntPair ip{std::make_pair(first, second)};
    ASSERT_EQ(first, ip->first);
    ASSERT_EQ(second, ip->second);

    *ip = std::make_pair(second, first);
    ASSERT_EQ(second, ip->first);
    ASSERT_EQ(first, ip->second);
}

TEST(Wrapped, const_access_arrow) // NOLINT
{
    auto const first = 10;
    auto const second = 20;
    IntPair ip{std::make_pair(first, second)};
    ASSERT_EQ(first, ip->first);
    ASSERT_EQ(second, ip->second);
}
