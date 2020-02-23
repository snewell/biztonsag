#ifndef BIZTONSAG_BITOP_HPP
#define BIZTONSAG_BITOP_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/create_macro.hpp>

namespace btshn
{
    template <typename LHS, typename RHS>
    struct bitand_result;

    template <typename LHS, typename RHS>
    using bitand_result_t = typename bitand_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(bitand_result_t, &, &=)

    template <typename T>
    struct can_bitnot
    {
        static constexpr bool value = false;
    };

#if __cplusplus >= 201703L
    template <typename T>
    constexpr inline auto can_bitnot_v = can_bitnot<T>::value;
#endif

    BTSHN_GENERATE_UNARY_FNS(can_bitnot, ~)

    template <typename LHS, typename RHS>
    struct bitor_result;

    template <typename LHS, typename RHS>
    using bitor_result_t = typename bitor_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(bitor_result_t, |, |=)

    template <typename LHS, typename RHS>
    struct bitxor_result;

    template <typename LHS, typename RHS>
    using bitxor_result_t = typename bitxor_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(bitxor_result_t, ^, ^=)

    template <typename LHS, typename RHS>
    struct leftshift_result;

    template <typename LHS, typename RHS>
    using leftshift_result_t = typename leftshift_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(leftshift_result_t, <<, <<=)

    template <typename LHS, typename RHS>
    struct rightshift_result;

    template <typename LHS, typename RHS>
    using rightshift_result_t = typename rightshift_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(rightshift_result_t, >>, >>=)
} // namespace btshn

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_BITAND(base_type, other_type, result_type)                  \
    template <>                                                                \
    struct bitand_result<base_type, other_type>                                \
    {                                                                          \
        using type = result_type;                                              \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_BITNOT(base_type)                                           \
    template <>                                                                \
    struct can_bitnot<base_type>                                               \
    {                                                                          \
        static constexpr bool value = true;                                    \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_BITOR(base_type, other_type, result_type)                   \
    template <>                                                                \
    struct bitor_result<base_type, other_type>                                 \
    {                                                                          \
        using type = result_type;                                              \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_BITXOR(base_type, other_type, result_type)                  \
    template <>                                                                \
    struct bitxor_result<base_type, other_type>                                \
    {                                                                          \
        using type = result_type;                                              \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_LEFTSHIFT(base_type, other_type, result_type)               \
    template <>                                                                \
    struct leftshift_result<base_type, other_type>                             \
    {                                                                          \
        using type = result_type;                                              \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_RIGHTSHIFT(base_type, other_type, result_type)              \
    template <>                                                                \
    struct rightshift_result<base_type, other_type>                            \
    {                                                                          \
        using type = result_type;                                              \
    }

#endif
