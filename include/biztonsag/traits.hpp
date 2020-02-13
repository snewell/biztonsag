#ifndef BIZTONSAG_TRAITS_HPP
#define BIZTONSAG_TRAITS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <type_traits>

/** \file traits.hpp
 *
 * \defgroup TypeTraits Type Traits
 */

namespace btshn
{
    /// \brief a type trait that determines if something is part of biztonsag
    ///
    /// \note This is mostly for intended for internal use
    ///
    /// \ingroup TypeTraits
    template <typename T>
    struct is_biztonsag_type
    {
        /// \brief a compile-time variable that determines if a type is part of
        ///        biztonsag
        ///
        /// Most types will be `false`, so any biztonsag type will need to
        /// specialize.
        ///
        /// \note This is mostly intended for internal use, but may be useful
        ///       for some compile-time type evaluation.
        static constexpr bool value = false;
    };

#if __cplusplus >= 201703L
    /// \brief a convience variable for is_biztonsag_type
    /// \ingroup TypeTraits
    template <typename T>
    constexpr inline auto is_biztonsag_type_v = is_biztonsag_type<T>::value;
#endif

    /// \brief a type trait that removes cv-attributes and the reference type
    ///
    /// \note This is mostly for intended for internal use
    ///
    /// \ingroup TypeTraits
    template <typename T>
    struct remove_cv_ref
    {
        /// \brief the actual type biztonsag cares about
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

    /// \brief a convience type alias for remove_cv_ref
    /// \ingroup TypeTraits
    template <typename T>
    using remove_cv_ref_t = typename remove_cv_ref<T>::type;
} // namespace btshn

#endif
