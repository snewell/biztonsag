#ifndef BIZTONSAG_COMPARABLE_HPP
#define BIZTONSAG_COMPARABLE_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/wrapped.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_COMPARABLE(name, ...)                                       \
    BTSHN_MAKE_TYPE(Comparable, name, __VA_ARGS__)

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
