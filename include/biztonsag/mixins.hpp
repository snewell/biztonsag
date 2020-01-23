#ifndef BIZTONSAG_CREATE_MIXINS_HPP
#define BIZTONSAG_CREATE_MIXINS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

#include <biztonsag/traits.hpp>

namespace detail
{
    namespace btshn
    {
        template <typename RESULT, typename L, typename R, typename OP_FN,
                  typename std::enable_if_t<!::btshn::is_biztonsag_type_v<R>,
                                            int> = 0>
        constexpr auto apply_operator(L const & l, const R & r, OP_FN fn)
            -> RESULT
        {
            return fn(l, r);
        }

        template <
            typename RESULT, typename L, typename R, typename OP_FN,
            typename std::enable_if_t<::btshn::is_biztonsag_type_v<R>, int> = 1>
        constexpr auto apply_operator(L const & l, const R & r, OP_FN fn)
            -> RESULT
        {
            return fn(l, *r);
        }
    } // namespace btshn
} // namespace detail

#if __cplusplus >= 201703L
#define MIXIN_CONSTEXPR constexpr
#else
#define MIXIN_CONSTEXPR
#endif

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_OP_HELPER(base, other, result, binary_op, assign_op)        \
    MIXIN_CONSTEXPR auto operator binary_op(base const & lhs,                  \
                                            const other & rhs)                 \
        ->result                                                               \
    {                                                                          \
        return ::detail::btshn::apply_operator<result>(                        \
            lhs, rhs, [](auto const & lhs, const auto & rhs) {                 \
                return result{(*lhs)binary_op rhs};                            \
            });                                                                \
    }                                                                          \
    template <typename B = base, typename R = result,                          \
              typename std::enable_if_t<std::is_same<B, R>::value, int> = 0>   \
    constexpr auto operator assign_op(base & lhs, other && rhs)->base &        \
    {                                                                          \
        *(lhs)assign_op std::forward<other>(rhs);                              \
        return lhs;                                                            \
    }

#endif
