#ifndef BIZTONSAG_COMPARABLE_HPP
#define BIZTONSAG_COMPARABLE_HPP 1

#include <utility>

#define BTSHN_MAKE_COMPARABLE_INNER2(t, tag_name, type_name)                   \
    namespace detail                                                           \
    {                                                                          \
        namespace auto_btshn                                                   \
        {                                                                      \
            struct tag_name                                                    \
            {                                                                  \
            };                                                                 \
        }                                                                      \
    }                                                                          \
    using type_name = ::btshn::Comparable<t, detail::auto_btshn::tag_name>

#define BTSHN_MAKE_COMPARABLE_INNER1(t, tag_first, tag_second, type_name)      \
    BTSHN_MAKE_COMPARABLE_INNER2(t, tag_first##tag_second, type_name)

#define BTSHN_MAKE_COMPARABLE(t, name)                                         \
    BTSHN_MAKE_COMPARABLE_INNER1(t, name, Tag, name)

namespace btshn
{
    template <typename T, typename TAG>
    class Comparable
    {
    public:
        explicit Comparable(T value);

        explicit operator T &() noexcept;

        explicit operator T const &() const noexcept;

        T & operator*() noexcept;

        T const & operator*() const noexcept;

        T * operator->() noexcept;

        T const * operator->() const noexcept;

    private:
        T m_value;
    };

    template <typename T, typename TAG>
    inline bool operator==(Comparable<T, TAG> const & lhs,
                           Comparable<T, TAG> const & rhs) noexcept
    {
        return static_cast<T const &>(lhs) == static_cast<T const &>(rhs);
    }

    template <typename T, typename TAG>
    inline bool operator!=(Comparable<T, TAG> const & lhs,
                           Comparable<T, TAG> const & rhs) noexcept
    {
        return static_cast<T const &>(lhs) != static_cast<T const &>(rhs);
    }

    template <typename T, typename TAG>
    inline Comparable<T, TAG>::Comparable(T value)
      : m_value{std::move(value)}
    {
    }

    template <typename T, typename TAG>
    inline Comparable<T, TAG>::operator T &() noexcept
    {
        return m_value;
    }

    template <typename T, typename TAG>
    inline Comparable<T, TAG>::operator T const &() const noexcept
    {
        return m_value;
    }

    template <typename T, typename TAG>
    T & Comparable<T, TAG>::operator*() noexcept
    {
        return m_value;
    }

    template <typename T, typename TAG>
    T const & Comparable<T, TAG>::operator*() const noexcept
    {
        return m_value;
    }

    template <typename T, typename TAG>
    T * Comparable<T, TAG>::operator->() noexcept
    {
        return m_value;
    }

    template <typename T, typename TAG>
    T const * Comparable<T, TAG>::operator->() const noexcept
    {
        return m_value;
    }
} // namespace btshn

#endif // COMPARABLE_HPP_INCLUDED
