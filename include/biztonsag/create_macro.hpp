#ifndef BIZTONSAG_CREATE_MACRO_HPP
#define BIZTONSAG_CREATE_MACRO_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <utility>

#include <biztonsag/traits.hpp>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TYPE_INNER2(btshn_type, tag_name, type_name, ...)           \
    namespace detail                                                           \
    {                                                                          \
        namespace auto_btshn                                                   \
        {                                                                      \
            struct tag_name                                                    \
            {                                                                  \
            };                                                                 \
        }                                                                      \
    }                                                                          \
    using type_name =                                                          \
        ::btshn::btshn_type<__VA_ARGS__, detail::auto_btshn::tag_name>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TYPE_INNER1(btshn_type, tag_first, tag_second, type_name,   \
                               ...)                                            \
    BTSHN_MAKE_TYPE_INNER2(btshn_type, tag_first##tag_second, type_name,       \
                           __VA_ARGS__)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TYPE(btshn_type, name, ...)                                 \
    BTSHN_MAKE_TYPE_INNER1(btshn_type, name, Tag, name, __VA_ARGS__)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_GENERATE_BINARY_FNS(result_type, binary_op, assign_op)           \
    template <typename LHS, typename RHS,                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,    \
              typename std::enable_if_t<                                       \
                  !is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 0>   \
    constexpr auto operator binary_op(LHS const & lhs, RHS && other) noexcept( \
        (noexcept((*lhs)binary_op std::forward<RHS>(other))))                  \
    {                                                                          \
        /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                       \
        return result_type<LHS, RHS>{                                          \
            (*lhs)binary_op std::forward<RHS>(other)};                         \
    }                                                                          \
    template <typename LHS, typename RHS,                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,    \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 1>    \
    constexpr auto operator binary_op(LHS const & lhs, RHS && other) noexcept( \
        (noexcept((*lhs)binary_op(*other))))                                   \
    {                                                                          \
        /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                       \
        return result_type<LHS, RHS>{(*lhs)binary_op(*other)};                 \
    }                                                                          \
    template <typename LHS, typename RHS,                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,    \
              typename std::enable_if_t<                                       \
                  !is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 0>   \
    constexpr auto operator assign_op(LHS & lhs, RHS && other) noexcept(       \
        (noexcept((*lhs)assign_op std::forward<RHS>(other))))                  \
        ->LHS &                                                                \
    {                                                                          \
        /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                       \
        static_assert(std::is_same<LHS, result_type<LHS, RHS>>::value,         \
                      "Result is a different type");                           \
        (*lhs) assign_op std::forward<RHS>(other);                             \
        return lhs;                                                            \
    }                                                                          \
    template <typename LHS, typename RHS,                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<LHS>>::value, int> = 0,    \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<RHS>>::value, int> = 1>    \
    constexpr auto operator assign_op(LHS & lhs, RHS && other) noexcept(       \
        (noexcept((*lhs)assign_op(*other))))                                   \
        ->LHS &                                                                \
    {                                                                          \
        /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                       \
        static_assert(std::is_same<LHS, result_type<LHS, RHS>>::value,         \
                      "Result is a different type");                           \
        (*lhs) assign_op(*other);                                              \
        return lhs;                                                            \
    }

#define BTSHN_GENERATE_UNARY_FNS(trait, unary_operator)                        \
    template <typename T,                                                      \
              typename std::enable_if_t<                                       \
                  is_biztonsag_type<remove_cv_ref_t<T>>::value, int> = 0>      \
    constexpr auto operator unary_operator(T && t) noexcept(                   \
        noexcept(unary_operator(*(std::forward<T>(t)))))                       \
        ->remove_cv_ref_t<T>                                                   \
    {                                                                          \
        static_assert(trait<remove_cv_ref_t<T>>::value, "Not negatable");      \
        return remove_cv_ref_t<T>{unary_operator(*t)};                         \
    }

#endif
