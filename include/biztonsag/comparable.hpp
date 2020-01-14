#ifndef BIZTONSAG_COMPARABLE_HPP
#define BIZTONSAG_COMPARABLE_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/wrapped.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_COMPARABLE_INNER2(t, tag_name, type_name)                   \
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
    using type_name = ::btshn::Comparable<t, detail::auto_btshn::tag_name>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_COMPARABLE_INNER1(t, tag_first, tag_second, type_name)      \
    BTSHN_MAKE_COMPARABLE_INNER2(t, tag_first##tag_second, type_name)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_COMPARABLE(t, name)                                         \
    BTSHN_MAKE_COMPARABLE_INNER1(t, name, Tag, name)

namespace btshn
{
    template <typename T, typename TAG>
    class Comparable : public Wrapped<T, TAG>
    {
    public:
        using Wrapped<T, TAG>::Wrapped;
    };

    template <typename T, typename TAG>
    constexpr auto operator==(Comparable<T, TAG> const & lhs,
                              Comparable<T, TAG> const & rhs) noexcept
    {
        return (*lhs) == (*rhs);
    }

    template <typename T, typename TAG>
    constexpr auto operator!=(Comparable<T, TAG> const & lhs,
                              Comparable<T, TAG> const & rhs) noexcept
    {
        return (*lhs) != (*rhs);
    }
} // namespace btshn

#endif // COMPARABLE_HPP_INCLUDED
