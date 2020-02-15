#include <biztonsag/bitop.hpp>

#include <gtest/gtest.h>

#include <biztonsag/comparable.hpp>

namespace
{
    BTSHN_MAKE_COMPARABLE(Flags, int);

    constexpr auto flag1 = 0x01;
    constexpr auto flag2 = 0x02;
    constexpr auto flag3 = 0x04;
} // namespace

namespace btshn
{
    BTSHN_MAKE_BITAND(Flags, Flags, Flags);
    BTSHN_MAKE_BITOR(Flags, Flags, Flags);

    BTSHN_MAKE_LEFTSHIFT(Flags, unsigned int, Flags);
    BTSHN_MAKE_RIGHTSHIFT(Flags, unsigned int, Flags);
} // namespace btshn

TEST(Bitop, bitand_same_result)
{
    Flags const initial{flag1 | flag2 | flag3};
    Flags const expected{flag2};

    auto const result = initial & expected;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, bitand_assign_same)
{
    Flags f{flag1 | flag2 | flag3};
    Flags const expected{flag2};

    f &= expected;
    ASSERT_EQ(f, expected);
}

TEST(Bitop, bitor_same_result)
{
    Flags const initial{0};
    Flags const expected{flag1 | flag3};

    auto const result = initial | expected;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, bitor_assign_same)
{
    Flags f{0};
    Flags const expected{flag1 | flag3};

    f |= expected;
    ASSERT_EQ(f, expected);
}

TEST(Bitop, leftshift_same_result)
{
    Flags const initial{flag1 | flag2};
    Flags const expected{flag2 | flag3};

    auto const result = initial << 1u;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, leftshift_assign_same)
{
    Flags f{flag1 | flag2};
    Flags const expected{flag2 | flag3};

    f <<= 1u;
    ASSERT_EQ(f, expected);
}

TEST(Bitop, rightshift_same_result)
{
    Flags const initial{flag2 | flag3};
    Flags const expected{flag1 | flag2};

    auto const result = initial >> 1u;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, rightshift_assign_same)
{
    Flags f{flag2 | flag3};
    Flags const expected{flag1 | flag2};

    f >>= 1u;
    ASSERT_EQ(f, expected);
}
