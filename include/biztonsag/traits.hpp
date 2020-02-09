#ifndef BIZTONSAG_TRAITS_HPP
#define BIZTONSAG_TRAITS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <type_traits>

namespace btshn
{
    template <typename T>
    struct is_biztonsag_type
    {
        static constexpr bool value = false;
    };

#if __cplusplus >= 201703L
    template <typename T>
    constexpr inline auto is_biztonsag_type_v = is_biztonsag_type<T>::value;
#endif

    template <typename T>
    struct remove_cv_ref
    {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };

    template <typename T>
    using remove_cv_ref_t = typename remove_cv_ref<T>::type;
} // namespace btshn

#endif
