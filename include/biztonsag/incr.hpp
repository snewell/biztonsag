#ifndef BIZTONSAG_INCR_HPP
#define BIZTONSAG_INCR_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/traits.hpp>

namespace btshn
{
    template <typename T>
    struct can_increment
    {
        static constexpr bool value = false;
    };

#if __cplusplus >= 201703L
    template <typename T>
    constexpr inline auto can_increment_v = can_increment<T>::value;
#endif

    template <typename T>
    struct can_decrement
    {
        static constexpr bool value = false;
    };

#if __cplusplus >= 201703L
    template <typename T>
    constexpr inline auto can_decrement_v = can_decrement<T>::value;
#endif

    template <typename T,
              typename std::enable_if_t<is_biztonsag_type<T>::value, int> = 0>
    auto operator++(T & t) noexcept((noexcept(++(*t)))) -> T &
    {
        static_assert(can_increment<T>::value, "Type cannot be incremented");
        ++(*t);
        return t;
    }

    template <typename T,
              typename std::enable_if_t<is_biztonsag_type<T>::value, int> = 0>
    auto operator++(T & t, int) noexcept((noexcept((*t)++))) -> T
    {
        static_assert(can_increment<T>::value, "Type cannot be incremented");
        auto ret = t;
        (*t)++;
        return ret;
    }

    template <typename T,
              typename std::enable_if_t<is_biztonsag_type<T>::value, int> = 0>
    auto operator--(T & t) noexcept((noexcept(--(*t)))) -> T &
    {
        static_assert(can_decrement<T>::value, "Type cannot be decremented");
        --(*t);
        return t;
    }

    template <typename T,
              typename std::enable_if_t<is_biztonsag_type<T>::value, int> = 0>
    auto operator--(T & t, int) noexcept((noexcept((*t)--))) -> T
    {
        static_assert(can_decrement<T>::value, "Type cannot be decremented");
        auto ret = t;
        (*t)--;
        return ret;
    }
} // namespace btshn

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_INCREMENTABLE(base_type)                                    \
    template <>                                                                \
    struct can_increment<base_type>                                            \
    {                                                                          \
        static constexpr bool value = true;                                    \
    }

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_DECREMENTABLE(base_type)                                    \
    template <>                                                                \
    struct can_decrement<base_type>                                            \
    {                                                                          \
        static constexpr bool value = true;                                    \
    }

#endif
