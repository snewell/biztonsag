#ifndef BIZTONSAG_ARITHMETIC_HPP
#define BIZTONSAG_ARITHMETIC_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

//#include <biztonsag/mixins.hpp>

#include <utility>

#include <biztonsag/traits.hpp>

#if 0
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_DIVIDES(base, other, result)                                \
    BTSHN_MAKE_OP_HELPER(base, other, result, /)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_DIVIDES_ASSIGN(base, other)                                 \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, /=)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_MINUS(base, other, result)                                  \
    BTSHN_MAKE_OP_HELPER(base, other, result, -)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_MINUS_ASSIGN(base, other)                                   \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, -=)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_PLUS(base, other, result)                                   \
    BTSHN_MAKE_OP_HELPER(base, other, result, +)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_PLUS_ASSIGN(base, other)                                    \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, +=)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TIMES(base, other, result)                                  \
    BTSHN_MAKE_OP_HELPER(base, other, result, *)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TIMES_ASSIGN(base, other)                                   \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, *=)
#endif

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
} // namespace btshn

#define BTSHN_MAKE_PLUS(base_type, other_type, result_type)                    \
    template <>                                                                \
    struct plus_result<base_type, other_type>                                  \
    {                                                                          \
        using type = result_type;                                              \
    }

#endif
