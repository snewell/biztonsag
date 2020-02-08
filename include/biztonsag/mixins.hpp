#ifndef BIZTONSAG_CREATE_MIXINS_HPP
#define BIZTONSAG_CREATE_MIXINS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

#include <biztonsag/traits.hpp>

namespace detail
{
    namespace btshn
    {
        template <typename RESULT, typename L, typename R, typename OP_FN,
                  typename std::enable_if_t<
                      !::btshn::is_biztonsag_type<R>::value, int> = 0>
        constexpr auto apply_operator(L const & l, const R & r, OP_FN fn)
            -> RESULT
        {
            return RESULT{fn(l, r)};
        }

        template <typename RESULT, typename L, typename R, typename OP_FN,
                  typename std::enable_if_t<
                      ::btshn::is_biztonsag_type<R>::value, int> = 1>
        constexpr auto apply_operator(L const & l, const R & r, OP_FN fn)
            -> RESULT
        {
            return RESULT{fn(l, *r)};
        }
    } // namespace btshn
} // namespace detail

#if __cplusplus >= 201703L
#define MIXIN_CONSTEXPR constexpr // NOLINT(cppcoreguidelines-macro-usage)
#else
#define MIXIN_CONSTEXPR // NOLINT(cppcoreguidelines-macro-usage)
#endif

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_OP_HELPER(base, other, result, binary_op)                   \
    MIXIN_CONSTEXPR auto operator binary_op(base const & lhs,                  \
                                            const other & rhs)                 \
        ->result                                                               \
    {                                                                          \
        return ::detail::btshn::apply_operator<result>(                        \
            lhs, rhs, [](auto const & lhs, const auto & rhs) {                 \
                return (*lhs)binary_op rhs;                                    \
            });                                                                \
    }                                                                          \
    static_assert(true, "cannot fail")

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, assign_op)                    \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                           \
    constexpr auto operator assign_op(base & lhs, const other & rhs)->base &   \
    {                                                                          \
        *(lhs)assign_op(rhs);                                                  \
        return lhs;                                                            \
    }                                                                          \
    static_assert(true, "cannot fail")

#endif
