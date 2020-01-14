#ifndef BIZTONSAG_WRAPPED_HPP
#define BIZTONSAG_WRAPPED_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <type_traits>
#include <utility>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_WRAPPED_INNER2(t, tag_name, type_name)                      \
    namespace detail                                                           \
    {                                                                          \
        namespace auto_btshn                                                   \
        {                                                                      \
            struct tag_name                                                    \
            {                                                                  \
            };                                                                 \
        }                                                                      \
    }                                                                          \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                           \
    using type_name = ::btshn::Wrapped<t, detail::auto_btshn::tag_name>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_WRAPPED_INNER1(t, tag_first, tag_second, type_name)         \
    BTSHN_MAKE_WRAPPED_INNER2(t, tag_first##tag_second, type_name)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_WRAPPED(t, name)                                            \
    BTSHN_MAKE_WRAPPED_INNER1(t, name, Tag, name)

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

        // TODO: figure out how to noexcept this
        template <typename INDEX>
        constexpr auto operator[](INDEX && i)
        {
            return m_value[std::forward<INDEX>(i)];
        }

        // TODO: figure out how to noexcept this
        template <typename INDEX>
        constexpr auto operator[](INDEX && i) const
        {
            return m_value[std::forward<INDEX>(i)];
        }

    private:
        T m_value;
    };
} // namespace btshn

#endif // WRAPPED_HPP_INCLUDED
