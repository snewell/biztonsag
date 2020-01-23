#ifndef BIZTONSAG_TRAITS_HPP
#define BIZTONSAG_TRAITS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

namespace btshn
{
    template <typename T>
    struct is_biztonsag_type
    {
        static constexpr bool value = false;
    };

    template <typename T>
    constexpr auto is_biztonsag_type_v = is_biztonsag_type<T>::value;
} // namespace btshn

#endif
