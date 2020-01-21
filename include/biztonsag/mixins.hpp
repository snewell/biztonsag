#ifndef BIZTONSAG_CREATE_MIXINS_HPP
#define BIZTONSAG_CREATE_MIXINS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define BTSHN_MAKE_MIXIN(name, base, ...)                                      \
    struct name : base, __VA_ARGS__                                            \
    {                                                                          \
        using base::base;                                                      \
    }

#endif
