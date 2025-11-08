#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree_private.h"
#include "struct_tree.h"
#include "tree_graph.h"

static int node_count = 0;

void TreeInit(struct Tree_t* tree) {

    assert(tree != NULL);
    tree -> root = NULL;
    tree -> node_count = 0;

}

struct Node_t* CreateNode(TreeElement element) {

    struct Node_t* node = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    assert(node != NULL);
    node -> node_element = element;
    node -> left_branch  = NULL;
    node -> right_branch = NULL;
    node -> parent       = NULL;
    node -> num_node     = node_count++;
    return node;
}

void DestroyTree(struct Tree_t* tree, struct Node_t* current_node, char branch) {

    assert(tree != NULL);

    if (current_node == NULL) return;

    if (current_node -> left_branch !=  NULL) {
        (tree -> node_count)--;
        DestroyTree(tree, current_node -> left_branch, 'L');
    }
    if (current_node -> right_branch != NULL) {
        (tree -> node_count)--;
        DestroyTree(tree, current_node -> right_branch, 'R');
    }

    if      (branch == 'L' && current_node->parent != NULL) (current_node -> parent) -> left_branch  = NULL;
    else if (branch == 'R' && current_node->parent != NULL) (current_node -> parent) -> right_branch = NULL;
    else if (branch == 'N') tree->root = NULL;


    current_node -> left_branch  = NULL;
    current_node -> right_branch = NULL;
    current_node -> parent       = NULL;

    free(current_node);

    return;

}

ErrorType TreeVerify(struct Tree_t* tree) {

    assert(tree != NULL);

    ErrorType curr_error = SUCCESS;
    if (tree == NULL)
        curr_error |= NULL_POINTER;
    if (tree -> node_count == 0 && tree -> root != NULL)
        curr_error |= ERROR_NODE_COUNT;
    if (tree -> root != NULL)
        SubTreeVerify(tree -> root, NULL, &curr_error);

    return curr_error;

}

void SubTreeVerify(struct Node_t* curr_node, struct Node_t* expected_parent, ErrorType* curr_error) {

    assert(curr_error != NULL);

    if (curr_node == NULL) return;

    if (curr_node -> parent != expected_parent)
        *curr_error |= ERROR_PARENT_NODE;

    if (curr_node -> left_branch != NULL) {
        if (((curr_node -> left_branch) -> node_element) > (curr_node -> node_element))
            *curr_error |= ERROR_LEFT_NODE;
        SubTreeVerify(curr_node -> left_branch, curr_node, curr_error);
    }

    if (curr_node -> right_branch != NULL) {
        if (((curr_node -> right_branch) -> node_element) < (curr_node -> node_element))
            *curr_error |= ERROR_RIGHT_NODE;
        SubTreeVerify(curr_node -> right_branch, curr_node, curr_error);
    }

}

void DumpTree(struct Tree_t* tree, const char* file, const int line) {

    assert(file != NULL);
    assert(tree != NULL);

    GraphicalDumpTree(tree, file, line);

}

