#ifndef BIZTONSAG_ORDERABLE_HPP
#define BIZTONSAG_ORDERABLE_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/comparable.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_ORDERABLE(name, ...)                                        \
    BTSHN_MAKE_TYPE(Orderable, name, __VA_ARGS__)

namespace btshn
{
    template <typename T, typename TAG>
    struct Orderable : Comparable<T, TAG>
    {
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
