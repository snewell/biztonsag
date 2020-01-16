#ifndef BIZTONSAG_WRAPPED_HPP
#define BIZTONSAG_WRAPPED_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <type_traits>
#include <utility>

#include <biztonsag/create_macro.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_WRAPPED(t, name) BTSHN_MAKE_TYPE(Wrapped, t, name)

namespace btshn
{
    template <typename T, typename TAG>
    class Wrapped
    {
    public:
        using value_type = T;

        using tag_type = TAG;

        constexpr explicit Wrapped(T value) noexcept(
            std::is_nothrow_move_constructible<T>::value)
          : m_value{std::move(value)}
        {
            static_assert(sizeof(Wrapped<T, TAG>) == sizeof(T),
                          "Extra memory requirements");
        }

        template <typename... ARGS>
        constexpr explicit Wrapped(ARGS &&... args) noexcept(
            std::is_nothrow_constructible<T, ARGS...>::value)
          : m_value(std::forward<ARGS>(args)...)
        {
            static_assert(sizeof(Wrapped<T, TAG>) == sizeof(T),
                          "Extra memory requirements");
        }

        template <typename U,
                  std::enable_if_t<
                      std::is_constructible<T, std::initializer_list<U>>::value,
                      int> = 1>
        constexpr Wrapped(std::initializer_list<U> list) noexcept(
            std::is_nothrow_constructible<T, std::initializer_list<U>>::value)
          : m_value{std::forward<std::initializer_list<U>>(list)}
        {
            static_assert(sizeof(Wrapped<T, TAG>) == sizeof(T),
                          "Extra memory requirements");
        }

        constexpr explicit operator T &() noexcept
        {
            return m_value;
        }

        constexpr explicit operator T const &() const noexcept
        {
            return m_value;
        }

        constexpr auto operator*() noexcept -> T &
        {
            return m_value;
        }

        constexpr auto operator*() const noexcept -> T const &
        {
            return m_value;
        }

        constexpr auto operator-> () noexcept -> T *
        {
            return &m_value;
        }

        constexpr auto operator-> () const noexcept -> T const *
        {
            return &m_value;
        }

    private:
        T m_value;
    };
} // namespace btshn

#endif // WRAPPED_HPP_INCLUDED
