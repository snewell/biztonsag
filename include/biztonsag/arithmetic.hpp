#ifndef BIZTONSAG_ARITHMETIC_HPP
#define BIZTONSAG_ARITHMETIC_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/create_macro.hpp>

namespace btshn
{
    template <typename LHS, typename RHS>
    struct divides_result;

    template <typename LHS, typename RHS>
    using divides_result_t = typename divides_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(divides_result_t, /, /=)

    template <typename LHS, typename RHS>
    struct minus_result;

    template <typename LHS, typename RHS>
    using minus_result_t = typename minus_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(minus_result_t, -, -=)

    template <typename LHS, typename RHS>
    struct plus_result;

    template <typename LHS, typename RHS>
    using plus_result_t = typename plus_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(plus_result_t, +, +=)

    template <typename LHS, typename RHS>
    struct times_result;

    template <typename LHS, typename RHS>
    using times_result_t = typename times_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    BTSHN_GENERATE_BINARY_FNS(times_result_t, *, *=)
} // namespace btshn

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_DIVIDES(base_type, other_type, result_type)                 \
    template <>                                                                \
    struct divides_result<base_type, other_type>                               \
    {                                                                          \
        using type = result_type;                                              \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_MINUS(base_type, other_type, result_type)                   \
    template <>                                                                \
    struct minus_result<base_type, other_type>                                 \
    {                                                                          \
        using type = result_type;                                              \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_PLUS(base_type, other_type, result_type)                    \
    template <>                                                                \
    struct plus_result<base_type, other_type>                                  \
    {                                                                          \
        using type = result_type;                                              \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TIMES(base_type, other_type, result_type)                   \
    template <>                                                                \
    struct times_result<base_type, other_type>                                 \
    {                                                                          \
        using type = result_type;                                              \
    }

#endif
