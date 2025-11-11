#ifndef STRUCT_TREES
#define STRUCT_TREES

#include <stddef.h>
typedef int TreeElement;

struct Node_t {

    TreeElement node_element;
    struct Node_t* left_branch;
    struct Node_t* right_branch;
    struct Node_t* parent;
    int num_node;

};

struct Tree_t {

    struct Node_t* root;
    size_t node_size;

};

#endif
