#ifndef BIZTONSAG_ARITHMETIC_HPP
#define BIZTONSAG_ARITHMETIC_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

#include <biztonsag/traits.hpp>

namespace btshn
{
    template <typename LHS, typename RHS>
    struct plus_result;

    template <typename LHS, typename RHS>
    using plus_result_t = typename plus_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    template <typename LHS, typename RHS,
              typename std::enable_if_t<is_biztonsag_type<LHS>::value, int> = 0>
    constexpr auto operator+(LHS const & lhs, RHS && other)
    {
        return plus_result_t<LHS, RHS>{(*lhs) + std::forward<RHS>(other)};
    }

    template <typename LHS, typename RHS,
              typename std::enable_if_t<is_biztonsag_type<LHS>::value, int> = 0>
    constexpr auto operator+=(LHS & lhs, RHS && other) -> LHS &
    {
        static_assert(std::is_same<LHS, plus_result_t<LHS, RHS>>::value,
                      "Result is a different type");
        (*lhs) += std::forward<RHS>(other);
        return lhs;
    }

    template <typename LHS, typename RHS>
    struct times_result;

    template <typename LHS, typename RHS>
    using times_result_t = typename times_result<
        LHS, std::remove_cv_t<std::remove_reference_t<RHS>>>::type;

    template <typename LHS, typename RHS,
              typename std::enable_if_t<
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,
              typename std::enable_if_t<
                  !is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 0>
    constexpr auto operator*(LHS const & lhs, RHS && other)
    {
        return times_result_t<LHS, RHS>{(*lhs) * std::forward<RHS>(other)};
    }

    template <typename LHS, typename RHS,
              typename std::enable_if_t<
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,
              typename std::enable_if_t<
                  is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 1>
    constexpr auto operator*(LHS const & lhs, RHS && other)
    {
        return times_result_t<LHS, RHS>{(*lhs) * (*other)};
    }

    template <typename LHS, typename RHS,
              typename std::enable_if_t<
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0>
    constexpr auto operator*=(LHS & lhs, RHS && other) -> LHS &
    {
        static_assert(std::is_same<LHS, times_result_t<LHS, RHS>>::value,
                      "Result is a different type");
        (*lhs) *= std::forward<RHS>(other);
        return lhs;
    }
} // namespace btshn

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
