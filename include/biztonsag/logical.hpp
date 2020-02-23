#ifndef BIZTONSAG_LOGICAL_HPP
#define BIZTONSAG_LOGICAL_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/create_macro.hpp>

namespace btshn
{
    template <typename T>
    struct can_negate
    {
        static constexpr bool value = false;
    };

#if __cplusplus >= 201703L
    template <typename T>
    constexpr inline auto can_negate_v = can_negate<T>::value;
#endif

    BTSHN_GENERATE_UNARY_FNS(can_negate, !)

} // namespace btshn

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_NEGATABLE(base_type)                                        \
    template <>                                                                \
    struct can_negate<base_type>                                               \
    {                                                                          \
        static constexpr bool value = true;                                    \
    }

#endif
