#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "stack_for_road.h"
#include "enum_tree.h"

struct Stack_t* CreateStack(size_t capacity) {

    struct Stack_t* stack_road = (struct Stack_t*)calloc(1, sizeof(struct Stack_t));

    assert(stack_road != NULL);

    TypeStack* data_nodes = (TypeStack*)calloc(capacity, sizeof(TypeStack));

    assert(data_nodes != NULL);

    stack_road -> curr_node  = data_nodes;

    stack_road -> capacity   = capacity;
    stack_road -> size_stack = 0;

    return stack_road;

}

enum ProgrammReturn StackPush(struct Stack_t* stack_road, TypeStack value) {

    assert(stack_road != NULL);
    if (StackVerify(stack_road) != SUCCESS) return INCORRECT;

    if ((stack_road -> size_stack) >= (stack_road -> capacity)) {
        if (StackExpansion(stack_road)) return INCORRECT;
    }

    (stack_road -> curr_node[(stack_road -> size_stack++)]) = value;

    return CORRECT;

}

void DestroyStack(struct Stack_t* stack) {

    if (stack == NULL) return;

    free(stack -> curr_node);
    free(stack);

}

void StackPop(struct Stack_t* stack_road) {

    assert(stack_road != NULL);
    (stack_road -> size_stack)--;

}

enum ProgrammReturn StackExpansion(struct Stack_t* stack_road) {

    assert(stack_road != NULL);

    size_t capacity_t   = stack_road -> capacity;
    size_t size_stack_t = stack_road -> size_stack;

    TypeStack* old_data_ptr = stack_road -> curr_node;

    assert(old_data_ptr != NULL);

    TypeStack* new_data_ptr = (TypeStack*)realloc(old_data_ptr,
                                (capacity_t * 2) * sizeof(TypeStack));

    if (new_data_ptr == NULL) {

        free(old_data_ptr);
        return INCORRECT;

    }

    old_data_ptr = new_data_ptr;

    for (size_t index = capacity_t; index < capacity_t * 2; index++) *(old_data_ptr + index) = 0;

    capacity_t *= 2;
    (stack_road -> curr_node) = old_data_ptr;
    (stack_road -> capacity)  = capacity_t;

    return CORRECT;

}

ErrorType StackVerify(struct Stack_t* stack_road)  {

    ErrorType curr_error = SUCCESS;

    if (stack_road == NULL) curr_error |= NULL_POINTER;
    if ((stack_road -> curr_node) == NULL) curr_error |= NULL_POINTER_CURR_NODE;
    if ((stack_road -> capacity) == 0) curr_error |= INVALID_STACK_CAPACITY;

    return curr_error;


}
