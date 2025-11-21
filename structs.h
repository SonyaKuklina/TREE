#ifndef STRUCT_TREES
#define STRUCT_TREES

#include <stddef.h>
#include <string.h>
#include "enum_tree.h"
typedef char* TreeElement;
typedef struct Node_t* TypeStack;

struct Node_t {

    TreeElement node_element;
    struct Node_t* left_branch;//YES
    struct Node_t* right_branch;//NO
    struct Node_t* parent;
    int num_node;

};

struct Tree_t {

    struct Node_t* root;
    size_t node_size;

};

struct Stack_t {

    TypeStack* curr_node;
    size_t size_stack;
    size_t capacity;

};

struct Commands_t {

    const char* name_command;
    enum ProgrammReturn (*function)(struct Akinator*);

};

struct Akinator {

    struct Tree_t* tree;
    struct Stack_t* stack_road_def;
    struct Stack_t* stack_object_one;
    struct Stack_t* stack_object_two;

};

#endif
