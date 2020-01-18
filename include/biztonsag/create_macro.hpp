#ifndef BIZTONSAG_CREATE_MACRO_HPP
#define BIZTONSAG_CREATE_MACRO_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

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

#endif
