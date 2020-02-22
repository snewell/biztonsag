#ifndef BIZTONSAG_COMPARABLE_HPP
#define BIZTONSAG_COMPARABLE_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

/// \file comparable.hpp

#include <biztonsag/wrapped.hpp>

/// \brief Create a Comparable type
///
/// This will create a tag type and a type alias for a Comparable that uses that
/// tag.  For example, `BTSHN_MAKE_COMPARABLE(Foo, int)` is morally identical to
/// the following:
///
/// \code
/// namespace detail {
///   namespace auto_btsh {
///     struct FooTag { };
///   }
/// }
/// using Foo = btshn::Comparable<int, detail::auto_btshn<FooTag>>;
/// \endcode
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_COMPARABLE(name, ...)                                       \
    BTSHN_MAKE_TYPE(Comparable, name, __VA_ARGS__)

namespace btshn
{
    /// \brief A type-safe wrapper that includes equality functionality
    ///
    /// Comparble provides all the functionality of Wrapped, but also
    /// includes equality functionality (i.e., `operator==` and `operator!=`).
    /// Sticking with the ideals of avoiding implicit conversions, equality
    /// tests are only available against \em identical types.
    ///
    /// \tparam T the type of data to wrap
    /// \tparam TAG a type to prevent implicit conversions
    ///
    /// \note `TAG` will never be instantiated by a Comparable

    /// \note For most use cases, using \ref BTSHN_MAKE_COMPARABLE is simpler
    ///       than using Comparable directly.
    ///
    /// \warning `TAG` isn't required to be unique, but that's what prevents the
    ///          implicit conversions that Apps Hungarian tires to avoid
    template <typename T, typename TAG>
    struct Comparable : Wrapped<T, TAG>
    {
        using Wrapped<T, TAG>::Wrapped;
    };

    /// \brief compare two instances of the same Comparable for equality
    template <typename T, typename TAG>
    constexpr auto operator==(
        Comparable<T, TAG> const & lhs,
        Comparable<T, TAG> const & rhs) noexcept(noexcept((*lhs) == (*rhs)))
    {
        return (*lhs) == (*rhs);
    }

    /// \brief compare two instances of the same Comparable for inequality
    template <typename T, typename TAG>
    constexpr auto operator!=(
        Comparable<T, TAG> const & lhs,
        Comparable<T, TAG> const & rhs) noexcept(noexcept((*lhs) != (*rhs)))
    {
        return (*lhs) != (*rhs);
    }

    /// \brief specialization of is_biztonsag_type
    template <typename T, typename TAG>
    struct is_biztonsag_type<Comparable<T, TAG>>
    {
        /// \brief any Comparable is by definition a biztonsag type
        constexpr static bool value = true;
    };
} // namespace btshn

#endif // COMPARABLE_HPP_INCLUDED
