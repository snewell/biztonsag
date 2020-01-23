#ifndef BIZTONSAG_MINUS_HPP
#define BIZTONSAG_MINUS_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/mixins.hpp>

#define BTSHN_MAKE_MINUS(base, other, result)                                  \
    BTSHN_MAKE_OP_HELPER(base, other, result, -, -=)

#endif
