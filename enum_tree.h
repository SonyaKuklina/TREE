#ifndef ENUM_TREE
#define ENUM_TREE

#include <stdint.h>

typedef uint32_t ErrorType;

enum Err_t {

    SUCCESS = 0,
    NULL_POINTER           = 1 << 0,
    NULL_POINTER_CURR_NODE = 1 << 1,
    ERROR_PARENT_NODE      = 1 << 2,
    ERROR_LEFT_NODE        = 1 << 3,
    ERROR_RIGHT_NODE       = 1 << 4,
    ERROR_NODE_COUNT       = 1 << 5,
    ERROR_ROOT_PARENT      = 1 << 6,
    ERROR_NODE_SIZE        = 1 << 7,
    INVALID_STACK_CAPACITY = 1 << 8,

};

enum ProgrammState {

    PROGRAMM_EXIT = 0,
    PROGRAMM_RUNNING,

};

enum ProgrammReturn {

    CORRECT = 0,
    INCORRECT,

};

enum SearchList {

    SEARCH_ERROR,
    SEARCH_SUCCESS,
    NODE_NOT_FOUND,

};

#endif
