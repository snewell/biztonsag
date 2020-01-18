#include <biztonsag/wrapped.hpp>

#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_WRAPPED(std::string, Name);

    BTSHN_MAKE_WRAPPED(std::vector<int>, Ints);
} // namespace

TEST(Constructor, no_args) // NOLINT
{
    Name n;

    ASSERT_EQ(0, n->length());
}

TEST(Constructor, forwarding) // NOLINT
{
    Name n{static_cast<char const *>("Hello"), 4};

    ASSERT_EQ(4, n->size());
    ASSERT_EQ("Hell", (*n));
}

TEST(Constructor, initializer_list) // NOLINT
{
    Ints i{0, 1, 2};

    ASSERT_EQ(3, i->size());
    ASSERT_EQ(0, (*i)[0]);
    ASSERT_EQ(1, (*i)[1]);
    ASSERT_EQ(2, (*i)[2]);
}

TEST(Constructor, non_initializer_list) // NOLINT
{
    auto const size = 10;
    Ints i(size);

    ASSERT_EQ(size, i->size());
}
