#ifndef BIZTONSAG_CREATE_MIXINS_HPP
#define BIZTONSAG_CREATE_MIXINS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_OP_HELPER(base, other, result, binary_op, assign_op)        \
    constexpr auto operator binary_op(base const & lhs, other && rhs)->result  \
    {                                                                          \
        return result{(*lhs)binary_op std::forward<other>(rhs)};               \
    }                                                                          \
    template <typename B = base, typename R = result,                          \
              typename std::enable_if_t<std::is_same<B, R>::value, int> = 0>   \
    constexpr auto operator assign_op(base & lhs, other && rhs)->base &        \
    {                                                                          \
        *(lhs)assign_op std::forward<other>(rhs);                              \
        return lhs;                                                            \
    }

#endif
