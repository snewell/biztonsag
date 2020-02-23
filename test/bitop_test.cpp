#include <biztonsag/bitop.hpp>

#include <gtest/gtest.h>

#include <biztonsag/comparable.hpp>

namespace
{
    BTSHN_MAKE_COMPARABLE(Flags, unsigned int);

    constexpr auto flag1 = 0x01U;
    constexpr auto flag2 = 0x02U;
    constexpr auto flag3 = 0x04U;
} // namespace

namespace btshn
{
    BTSHN_MAKE_BITAND(Flags, Flags, Flags);
    BTSHN_MAKE_BITOR(Flags, Flags, Flags);
    BTSHN_MAKE_BITXOR(Flags, Flags, Flags);

    BTSHN_MAKE_LEFTSHIFT(Flags, unsigned int, Flags);
    BTSHN_MAKE_RIGHTSHIFT(Flags, unsigned int, Flags);
} // namespace btshn

TEST(Bitop, bitand_same_result) // NOLINT
{
    Flags const initial{flag1 | flag2 | flag3};
    Flags const expected{flag2};

    auto const result = initial & expected;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, bitand_assign_same) // NOLINT
{
    Flags f{flag1 | flag2 | flag3};
    Flags const expected{flag2};

    f &= expected;
    ASSERT_EQ(f, expected);
}

TEST(Bitop, bitor_same_result) // NOLINT
{
    Flags const initial{0};
    Flags const expected{flag1 | flag3};

    auto const result = initial | expected;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, bitor_assign_same) // NOLINT
{
    Flags f{0};
    Flags const expected{flag1 | flag3};

    f |= expected;
    ASSERT_EQ(f, expected);
}

TEST(Bitop, bitxor_same_result) // NOLINT
{
    Flags const initial{0};
    Flags const expected1{flag1};

    auto const result1 = initial ^ expected1;
    ASSERT_EQ(result1, expected1);
    auto const result2 = result1 ^ expected1;
    ASSERT_EQ(result2, initial);
}

TEST(Bitop, bitxor_assign_same) // NOLINT
{
    Flags f{0};
    Flags const expected{flag1};

    f ^= expected;
    ASSERT_EQ(f, expected);
    f ^= expected;
    ASSERT_EQ(f, Flags{0});
}

TEST(Bitop, leftshift_same_result) // NOLINT
{
    Flags const initial{flag1 | flag2};
    Flags const expected{flag2 | flag3};

    auto const result = initial << 1U;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, leftshift_assign_same) // NOLINT
{
    Flags f{flag1 | flag2};
    Flags const expected{flag2 | flag3};

    f <<= 1U;
    ASSERT_EQ(f, expected);
}

TEST(Bitop, rightshift_same_result) // NOLINT
{
    Flags const initial{flag2 | flag3};
    Flags const expected{flag1 | flag2};

    auto const result = initial >> 1U;
    ASSERT_EQ(result, expected);
}

TEST(Bitop, rightshift_assign_same) // NOLINT
{
    Flags f{flag2 | flag3};
    Flags const expected{flag1 | flag2};

    f >>= 1U;
    ASSERT_EQ(f, expected);
}
