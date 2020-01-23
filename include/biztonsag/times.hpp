#ifndef BIZTONSAG_TIMES_HPP
#define BIZTONSAG_TIMES_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/mixins.hpp>

#define BTSHN_MAKE_TIMES(base, other, result)                                  \
    BTSHN_MAKE_OP_HELPER(base, other, result, *, *=)

#endif
