#ifndef BIZTONSAG_ORDERABLE_HPP
#define BIZTONSAG_ORDERABLE_HPP 1

#include <biztonsag/comparable.hpp>

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
    using type_name = ::btshn::Orderable<t, detail::auto_btshn::tag_name>

#define BTSHN_MAKE_ORDERABLE_INNER1(t, tag_first, tag_second, type_name)       \
    BTSHN_MAKE_ORDERABLE_INNER2(t, tag_first##tag_second, type_name)

#define BTSHN_MAKE_ORDERABLE(t, name)                                          \
    BTSHN_MAKE_ORDERABLE_INNER1(t, name, Tag, name)

namespace btshn
{
    template <typename T, typename TAG>
    class Orderable : public Comparable<T, TAG>
    {
        using Comparable<T, TAG>::Comparable;
    };

    template <typename T, typename TAG>
    inline bool operator<(Orderable<T, TAG> const & lhs,
                          Orderable<T, TAG> const & rhs) noexcept
    {
        return static_cast<T const &>(lhs) < static_cast<T const &>(rhs);
    }

    template <typename T, typename TAG>
    inline bool operator>(Orderable<T, TAG> const & lhs,
                          Orderable<T, TAG> const & rhs) noexcept
    {
        return static_cast<T const &>(lhs) > static_cast<T const &>(rhs);
    }

    template <typename T, typename TAG>
    inline bool operator<=(Orderable<T, TAG> const & lhs,
                           Orderable<T, TAG> const & rhs) noexcept
    {
        return !(static_cast<T const &>(lhs) > static_cast<T const &>(rhs));
    }

    template <typename T, typename TAG>
    inline bool operator>=(Orderable<T, TAG> const & lhs,
                           Orderable<T, TAG> const & rhs) noexcept
    {
        return !(static_cast<T const &>(lhs) < static_cast<T const &>(rhs));
    }
} // namespace btshn

#endif
