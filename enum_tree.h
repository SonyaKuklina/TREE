#ifndef ENUM_TREE
#define ENUM_TREE

#include <stdint.h>

typedef uint32_t ErrorType;

enum Err_t {

    SUCCESS = 0,
    NULL_POINTER      = 1 << 0,
    ERROR_PARENT_NODE = 1 << 1,
    ERROR_LEFT_NODE   = 1 << 2,
    ERROR_RIGHT_NODE  = 1 << 3,
    ERROR_NODE_COUNT  = 1 << 4,

};

enum ProgrammReturn {

    CORRECT = 0,
    INCORRECT,

};

#endif
