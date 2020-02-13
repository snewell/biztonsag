#ifndef BIZTONSAG_ORDERABLE_HPP
#define BIZTONSAG_ORDERABLE_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

/// \file orderable.hpp

#include <biztonsag/comparable.hpp>

/// \brief Create an Orderable type
///
/// This will create a tag type and a type alias for an Orderable that uses that
/// tag.  For example, `BTSHN_MAKE_ORDERABLE(Foo, int)` is morally identical to
/// the following:
///
/// \code
/// namespace detail {
///   namespace auto_btsh {
///     struct FooTag { };
///   }
/// }
/// using Foo = btshn::Orderable<int, detail::auto_btshn<FooTag>>;
/// \endcode
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_ORDERABLE(name, ...)                                        \
    BTSHN_MAKE_TYPE(Orderable, name, __VA_ARGS__)

namespace btshn
{
    /// \brief A type-safe wrapper that includes ordering support
    ///
    /// Orderable provides all the functionality of Comparable, but also
    /// includes ordering functionality (i.e., `operator<`, `operator>`,
    /// `operator<=`, and `operator>=`). Sticking with the ideals of avoiding
    /// implicit conversions, equality tests are only available against \em
    /// identical types.
    ///
    /// \tparam T the type of data to wrap
    /// \tparam TAG a type to prevent implicit conversions
    ///
    /// \note `TAG` will never be instantiated by Ordreable

    /// \note For most use cases, using \ref BTSHN_MAKE_ORDERABLE is simpler
    ///       than using Orderable directly.
    ///
    /// \warning `TAG` isn't required to be unique, but that's what prevents the
    ///          implicit conversions that Apps Hungarian tires to avoid
    template <typename T, typename TAG>
    struct Orderable : Comparable<T, TAG>
    {
        using Comparable<T, TAG>::Comparable;
    };

    /// \brief compare two Orderables using the less-than operator
    template <typename T, typename TAG>
    constexpr auto operator<(Orderable<T, TAG> const & lhs,
                             Orderable<T, TAG> const & rhs) noexcept
    {
        return (*lhs) < (*rhs);
    }

    /// \brief compare two Orderables using the greater-than operator
    template <typename T, typename TAG>
    constexpr auto operator>(Orderable<T, TAG> const & lhs,
                             Orderable<T, TAG> const & rhs) noexcept
    {
        return (*lhs) > (*rhs);
    }

    /// \brief compare two Orderables using the less-than or equal operator
    template <typename T, typename TAG>
    constexpr auto operator<=(Orderable<T, TAG> const & lhs,
                              Orderable<T, TAG> const & rhs) noexcept
    {
        return !((*lhs) > (*rhs));
    }

    /// \brief compare two Orderables using the greater-than or equal operator
    template <typename T, typename TAG>
    constexpr auto operator>=(Orderable<T, TAG> const & lhs,
                              Orderable<T, TAG> const & rhs) noexcept
    {
        return !((*lhs) < (*rhs));
    }

    /// \brief specialization of is_biztonsag_type
    template <typename T, typename TAG>
    struct is_biztonsag_type<Orderable<T, TAG>>
    {
        /// \brief any Orderable is by definition a biztonsag type
        constexpr static bool value = true;
    };
} // namespace btshn

#endif
