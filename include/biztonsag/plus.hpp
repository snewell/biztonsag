#ifndef BIZTONSAG_PLUS_HPP
#define BIZTONSAG_PLUS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/mixins.hpp>

#define BTSHN_MAKE_PLUS(base, other, result)                                   \
    BTSHN_MAKE_OP_HELPER(base, other, result, +, +=)

#endif
