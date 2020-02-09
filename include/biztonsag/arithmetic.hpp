#ifndef BIZTONSAG_ARITHMETIC_HPP
#define BIZTONSAG_ARITHMETIC_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

#include <biztonsag/traits.hpp>

#define BTSHN_GENERATE_BINARY_FNS(result_type, binary_op, assign_op)           \
    template <typename LHS, typename RHS,                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,    \
              typename std::enable_if_t<                                       \
                  !is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 0>   \
    constexpr auto operator binary_op(LHS const & lhs, RHS && other)           \
    {                                                                          \
        return result_type<LHS, RHS>{                                          \
            (*lhs)binary_op std::forward<RHS>(other)};                         \
    }                                                                          \
    template <typename LHS, typename RHS,                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,    \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 1>    \
    constexpr auto operator binary_op(LHS const & lhs, RHS && other)           \
    {                                                                          \
        return result_type<LHS, RHS>{(*lhs)binary_op(*other)};                 \
    }                                                                          \
    template <typename LHS, typename RHS,                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0>    \
    constexpr auto operator assign_op(LHS & lhs, RHS && other)->LHS &          \
    {                                                                          \
        static_assert(std::is_same<LHS, result_type<LHS, RHS>>::value,         \
                      "Result is a different type");                           \
        (*lhs) assign_op std::forward<RHS>(other);                             \
        return lhs;                                                            \
    }

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

#define BTSHN_MAKE_DIVIDES(base_type, other_type, result_type)                 \
    template <>                                                                \
    struct divides_result<base_type, other_type>                               \
    {                                                                          \
        using type = result_type;                                              \
    }

#define BTSHN_MAKE_MINUS(base_type, other_type, result_type)                   \
    template <>                                                                \
    struct minus_result<base_type, other_type>                                 \
    {                                                                          \
        using type = result_type;                                              \
    }

#define BTSHN_MAKE_PLUS(base_type, other_type, result_type)                    \
    template <>                                                                \
    struct plus_result<base_type, other_type>                                  \
    {                                                                          \
        using type = result_type;                                              \
    }

#define BTSHN_MAKE_TIMES(base_type, other_type, result_type)                   \
    template <>                                                                \
    struct times_result<base_type, other_type>                                 \
    {                                                                          \
        using type = result_type;                                              \
    }

#endif
