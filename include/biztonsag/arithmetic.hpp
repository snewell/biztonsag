#ifndef BIZTONSAG_ARITHMETIC_HPP
#define BIZTONSAG_ARITHMETIC_HPP 1 // NOLINT(cppcoreguidelines-macro-usage)

#include <biztonsag/mixins.hpp>

#define BTSHN_MAKE_DIVIDES(base, other, result)                                \
    BTSHN_MAKE_OP_HELPER(base, other, result, /)

#define BTSHN_MAKE_DIVIDES_ASSIGN(base, other)                                 \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, /=)

#define BTSHN_MAKE_MINUS(base, other, result)                                  \
    BTSHN_MAKE_OP_HELPER(base, other, result, -)

#define BTSHN_MAKE_MINUS_ASSIGN(base, other)                                   \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, -=)

#define BTSHN_MAKE_PLUS(base, other, result)                                   \
    BTSHN_MAKE_OP_HELPER(base, other, result, +)

#define BTSHN_MAKE_PLUS_ASSIGN(base, other)                                    \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, +=)

#define BTSHN_MAKE_TIMES(base, other, result)                                  \
    BTSHN_MAKE_OP_HELPER(base, other, result, *)

#define BTSHN_MAKE_TIMES_ASSIGN(base, other)                                   \
    BTSHN_MAKE_ASSIGN_OP_HELPER(base, other, *=)

#endif
