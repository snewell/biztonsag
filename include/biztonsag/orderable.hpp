#ifndef BIZTONSAG_ORDERABLE_HPP
#define BIZTONSAG_ORDERABLE_HPP 1

#include <biztonsag/comparable.hpp>

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
