#ifndef BIZTONSAG_PLUS_HPP
#define BIZTONSAG_PLUS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

namespace btshn
{
    template <typename BASE, typename OTHER>
    class Plus
    {
    public:
        auto operator+(OTHER && other) const -> BASE
        {
            return BASE{*(*reinterpret_cast<BASE const *>(this)) +
                        std::forward<OTHER>(other)};
        }

        auto operator+=(OTHER && other) -> BASE &
        {
            *(*reinterpret_cast<BASE *>(this)) += std::forward<OTHER>(other);
            return *reinterpret_cast<BASE *>(this);
        }
    };
} // namespace btshn

#endif
