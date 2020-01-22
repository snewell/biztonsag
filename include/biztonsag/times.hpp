#ifndef BIZTONSAG_TIMES_HPP
#define BIZTONSAG_TIMES_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

namespace btshn
{
    template <typename BASE, typename OTHER, typename RESULT = BASE>
    struct Times
    {
        auto operator*(OTHER && other) const -> RESULT
        {
            return RESULT{*(*reinterpret_cast<BASE const *>(this)) *
                          std::forward<OTHER>(other)};
        }

        template <typename B = BASE, typename R = RESULT,
                  typename std::enable_if_t<std::is_same<B, R>::value, int> = 0>
        auto operator*=(OTHER && other) -> BASE &
        {
            *(*reinterpret_cast<BASE *>(this)) *= std::forward<OTHER>(other);
            return *reinterpret_cast<BASE *>(this);
        }
    };
} // namespace btshn

#endif
