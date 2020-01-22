#ifndef BIZTONSAG_MINUS_HPP
#define BIZTONSAG_MINUS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

namespace btshn
{
    template <typename BASE, typename OTHER, typename RESULT = BASE>
    struct Minus
    {
        friend constexpr auto operator-(BASE const & lhs, OTHER && rhs)
            -> RESULT
        {
            return RESULT{(*lhs) - std::forward<OTHER>(rhs)};
        }

        template <typename B = BASE, typename R = RESULT,
                  typename std::enable_if_t<std::is_same<B, R>::value, int> = 0>
        friend constexpr auto operator-=(BASE & lhs, OTHER && rhs) -> BASE &
        {
            *(lhs) -= std::forward<OTHER>(rhs);
            return lhs;
        }
    };
} // namespace btshn

#endif
