#ifndef BIZTONSAG_DIVIDES_HPP
#define BIZTONSAG_DIVIDES_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

namespace btshn
{
    template <typename BASE, typename OTHER, typename RESULT = BASE>
    struct Divides
    {
        friend auto operator/(BASE const & lhs, OTHER && rhs) -> RESULT
        {
            return RESULT{(*lhs) / std::forward<OTHER>(rhs)};
        }

        template <typename B = BASE, typename R = RESULT,
                  typename std::enable_if_t<std::is_same<B, R>::value, int> = 0>
        auto operator/=(OTHER && other) -> BASE &
        {
            *(*reinterpret_cast<BASE *>(this)) /= std::forward<OTHER>(other);
            return *reinterpret_cast<BASE *>(this);
        }
    };
} // namespace btshn

#endif
