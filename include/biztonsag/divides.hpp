#ifndef BIZTONSAG_DIVIDES_HPP
#define BIZTONSAG_DIVIDES_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/mixins.hpp>

#define BTSHN_MAKE_DIVIDES(base, other, result)                                \
    BTSHN_MAKE_OP_HELPER(base, other, result, /, /=)

#endif
