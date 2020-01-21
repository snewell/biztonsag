#include <biztonsag/wrapped.hpp>

#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace
{
    BTSHN_MAKE_WRAPPED(Name, std::string);

    BTSHN_MAKE_WRAPPED(Ints, std::vector<int>);
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

namespace
{
    enum class ConstructorType
    {
        default_constructor,
        args_constructor,
        move_constructor,
        initializer_list_constructor
    };

    struct ComplexBase
    {
        ComplexBase()
          : m_type{ConstructorType::default_constructor}
        {
        }

        ComplexBase(int a, int b)
          : m_type{ConstructorType::args_constructor}
        {
            (void)a;
            (void)b;
        }

        ComplexBase(std::initializer_list<int> init_list)
          : m_type{ConstructorType::initializer_list_constructor}
        {
            (void)init_list;
        }

        ComplexBase(ComplexBase && c)
          : m_type{ConstructorType::move_constructor}
        {
            (void)c;
        }

        ConstructorType const m_type;
    };

    BTSHN_MAKE_WRAPPED(Complex, ComplexBase);
} // namespace

TEST(Constructor, multi_default) // NOLINT
{
    Complex c{};
    ASSERT_EQ(ConstructorType::default_constructor, c->m_type);
}

TEST(Constructor, multi_args) // NOLINT
{
    Complex c(0, 0);
    ASSERT_EQ(ConstructorType::args_constructor, c->m_type);
}

TEST(Constructor, multi_initializer_list) // NOLINT
{
    Complex c{0, 0};
    ASSERT_EQ(ConstructorType::initializer_list_constructor, c->m_type);
}

TEST(Constructor, multi_move) // NOLINT
{
    Complex c{ComplexBase{}};
    ASSERT_EQ(ConstructorType::move_constructor, c->m_type);
}

namespace
{
    struct ThrowingObjectBase
    {
        ThrowingObjectBase() {}
    };
    BTSHN_MAKE_WRAPPED(ThrowingObject, ThrowingObjectBase);
    static_assert(!std::is_nothrow_default_constructible<ThrowingObject>::value,
                  "noexcept not propagating properly");

    struct NoexceptBase
    {
        NoexceptBase() noexcept {}
    };
    BTSHN_MAKE_WRAPPED(Noexcept, NoexceptBase);
    static_assert(std::is_nothrow_default_constructible<Noexcept>::value,
                  "noexcept not propagating properly");
} // namespace
