#ifndef BIZTONSAG_WRAPPED_HPP
#define BIZTONSAG_WRAPPED_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <type_traits>
#include <utility>

#include <biztonsag/create_macro.hpp>
#include <biztonsag/traits.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_WRAPPED(name, ...)                                          \
    BTSHN_MAKE_TYPE(Wrapped, name, __VA_ARGS__)

namespace btshn
{
    /** \brief A type-safe wrapper around some data
     *
     * `Wrapped` provides a way to trivially wrap a piece of data.  It's
     * designed to convert the types of bugs that "Apps Hungarian" provents into
     * compilation errors.
     *
     * `Wrapped` will always take up identical memory as a plain `T`; this is
     * guaranteed via `static_assert`.  With optimizations enabled, most
     * compilers should be able to remove any additional runtime overhead as
     * well.
     *
     * \tparam T the type of data to wrap
     * \tparam TAG a type to prevent implicit conversions
     *
     * \note `TAG` will never be instantiated by `Wrapped`
     *
     * \warning `TAG` isn't required to be unique, but that's what prevents the
     *          implicit conversions that Apps Hungarian tires to avoid
     */
    template <typename T, typename TAG>
    struct Wrapped
    {
        /// \brief the type of wrapped data
        using value_type = T;

        /// \brief the type of the tag
        using tag_type = TAG;

        /** \brief Construct via `std::move`
         *
         * \param value passed via `std::move` to `T`'s constructor
         */
        constexpr explicit Wrapped(T value) noexcept(
            std::is_nothrow_move_constructible<T>::value)
          : m_value{std::move(value)}
        {
            static_assert(sizeof(Wrapped<T, TAG>) == sizeof(T),
                          "Extra memory requirements");
        }

        /** \brief Construct using forwarded arguments
         *
         * This constructor is provided to avoid needing to construct a `T` just
         * to pass to the move constructor.  It's designed to work similiar to
         * the `emplace` or `make_*` functions from the standard librray.
         *
         * \param args arguments to pass on to `T`'s constructor
         *
         * \tparam ARGS a parameter pack
         */
        template <typename... ARGS>
        constexpr explicit Wrapped(ARGS &&... args) noexcept(
            std::is_nothrow_constructible<T, ARGS...>::value)
          : m_value(std::forward<ARGS>(args)...)
        {
            static_assert(sizeof(Wrapped<T, TAG>) == sizeof(T),
                          "Extra memory requirements");
        }

        /** \brief Construct using an `std::initializer_list`
         *
         * This constructor enables the wrapped data to be constructed with an
         * `std::initializer_list`.  This should make it more efficient when
         * constructing certain types.
         *
         * \note this constructor is only available if `T` can be constructed
         *       via an `std::initializer_list<U>`
         *
         * \param list the data to pass to `T`'s constructor
         *
         * \tparam U the type available in \a list
         */
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

        /// \brief access the wrapped data
        constexpr auto operator*() noexcept -> T &
        {
            return m_value;
        }

        /// \brief access the wrapped data
        constexpr auto operator*() const noexcept -> T const &
        {
            return m_value;
        }

        /// \brief access the wrapped data
        constexpr auto operator-> () noexcept -> T *
        {
            return &m_value;
        }

        /// \brief access the wrapped data
        constexpr auto operator-> () const noexcept -> T const *
        {
            return &m_value;
        }

    private:
        T m_value;
    };

    template <typename T, typename TAG>
    struct is_biztonsag_type<Wrapped<T, TAG>>
    {
        constexpr static bool value = true;
    };
} // namespace btshn

#endif // WRAPPED_HPP_INCLUDED
