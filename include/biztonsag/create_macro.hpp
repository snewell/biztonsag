#ifndef BIZTONSAG_CREATE_MACRO_HPP
#define BIZTONSAG_CREATE_MACRO_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TYPE_INNER2(btshn_type, t, tag_name, type_name)             \
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
    using type_name = ::btshn::btshn_type<t, detail::auto_btshn::tag_name>

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TYPE_INNER1(btshn_type, t, tag_first, tag_second,           \
                               type_name)                                      \
    BTSHN_MAKE_TYPE_INNER2(btshn_type, t, tag_first##tag_second, type_name)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_TYPE(btshn_type, t, name)                                   \
    BTSHN_MAKE_TYPE_INNER1(btshn_type, t, name, Tag, name)

#endif
