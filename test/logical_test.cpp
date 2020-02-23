#include <biztonsag/logical.hpp>

#include <biztonsag/comparable.hpp>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(Bool, bool);
}

namespace btshn
{
    BTSHN_MAKE_NEGATABLE(Bool);
}

TEST(Logical, negate)
{
    Bool const initial{false};
    auto const result = !initial;

    ASSERT_TRUE(*result);
}
