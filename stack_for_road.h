#ifndef STACK_FOR_ROAD
#define STACK_FOR_ROAD

#include "structs.h"

#define SIZE_STACK 10

struct Stack_t* CreateStack(size_t capacity);
ErrorType StackVerify(struct Stack_t* stack);
enum ProgrammReturn StackPush(struct Stack_t* stack_road, TypeStack value);
void StackPop(struct Stack_t* stack_road);
enum ProgrammReturn StackExpansion(struct Stack_t* stack_road);
void DestroyStack(struct Stack_t* stack);

#endif
