#ifndef BIZTONSAG_ORDERABLE_HPP
#define BIZTONSAG_ORDERABLE_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/comparable.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_ORDERABLE_INNER2(t, tag_name, type_name)                    \
    namespace detail                                                           \
    {                                                                          \
        namespace auto_btshn                                                   \
        {                                                                      \
            struct tag_name                                                    \
            {                                                                  \
            };                                                                 \
        }                                                                      \
    }                                                                          \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                           \
    using type_name = ::btshn::Orderable<t, detail::auto_btshn::tag_name>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_ORDERABLE_INNER1(t, tag_first, tag_second, type_name)       \
    BTSHN_MAKE_ORDERABLE_INNER2(t, tag_first##tag_second, type_name)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_ORDERABLE(t, name)                                          \
    BTSHN_MAKE_ORDERABLE_INNER1(t, name, Tag, name)

namespace btshn
{
    template <typename T, typename TAG>
    class Orderable : public Comparable<T, TAG>
    {
    public:
        using Comparable<T, TAG>::Comparable;
    };

    template <typename T, typename TAG>
    constexpr auto operator<(Orderable<T, TAG> const & lhs,
                             Orderable<T, TAG> const & rhs) noexcept
    {
        return (*lhs) < (*rhs);
    }

    template <typename T, typename TAG>
    constexpr auto operator>(Orderable<T, TAG> const & lhs,
                             Orderable<T, TAG> const & rhs) noexcept
    {
        return (*lhs) > (*rhs);
    }

    template <typename T, typename TAG>
    constexpr auto operator<=(Orderable<T, TAG> const & lhs,
                              Orderable<T, TAG> const & rhs) noexcept
    {
        return !((*lhs) > (*rhs));
    }

    template <typename T, typename TAG>
    constexpr auto operator>=(Orderable<T, TAG> const & lhs,
                              Orderable<T, TAG> const & rhs) noexcept
    {
        return !((*lhs) < (*rhs));
    }
} // namespace btshn

#endif
