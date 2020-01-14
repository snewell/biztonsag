#include <biztonsag/comparable.hpp>

#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_COMPARABLE(std::string, Name);

    BTSHN_MAKE_COMPARABLE(std::vector<int>, Ints);
} // namespace

TEST(Constructor, no_args)
{
    Name n;

    ASSERT_EQ(0, n->length());
}

TEST(Constructor, forwarding)
{
    Name n{"Hello", 4};

    ASSERT_EQ(4, n->size());
    ASSERT_EQ("Hell", (*n));
}

TEST(Constructor, initializer_list)
{
    Ints i{0, 1, 2};

    ASSERT_EQ(3, i->size());
    ASSERT_EQ(0, i[0]);
    ASSERT_EQ(1, i[1]);
    ASSERT_EQ(2, i[2]);
}

TEST(Constructor, non_initializer_list)
{
    Ints i(10);

    ASSERT_EQ(10, i->size());
}
