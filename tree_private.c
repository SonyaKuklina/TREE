#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree_private.h"
#include "struct_tree.h"
#include "tree_graph.h"

void TreeInit(struct Tree_t* tree) {

    assert(tree != NULL);
    tree -> root = NULL;
    tree -> node_size = 0;

}

struct Tree_t* CreateAkinatorTree() {
    struct Tree_t* tree = (struct Tree_t*)calloc(1, sizeof(struct Tree_t));
    assert(tree != NULL);

    tree->root = CreateNode("Animal?", tree);
    (tree -> node_size)++;

    tree->root->left_branch = CreateNode("Cat", tree);
    (tree -> node_size)++;
    tree->root->right_branch = CreateNode("He teach math?", tree);
    (tree -> node_size)++;
    ((tree -> root) -> right_branch) -> left_branch = CreateNode("Lukash", tree);
    (tree -> node_size)++;
    ((tree -> root) -> right_branch) -> right_branch = CreateNode("Sonya", tree);
    (tree -> node_size)++;

    tree->root->left_branch->parent = tree->root;
    tree->root->right_branch->parent = tree->root;

    (((tree -> root) -> right_branch) -> left_branch) -> parent = tree->root->right_branch;
    (((tree -> root) -> right_branch) -> right_branch) -> parent = tree->root->right_branch;

    return tree;
}

struct Node_t* CreateNode(TreeElement element, struct Tree_t* tree) {

    struct Node_t* node = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    assert(node != NULL);
    node -> node_element = element;
    node -> left_branch  = NULL;
    node -> right_branch = NULL;
    node -> parent       = NULL;
    node -> num_node     = tree -> node_size;
    return node;
}

void DestroyTree(struct Tree_t* tree, struct Node_t* current_node) {

    assert(tree != NULL);

    if (current_node == NULL) return;

    if (current_node == tree->root) {
        tree->root = NULL;
    }

    if (current_node -> left_branch != NULL)  DestroyTree(tree, current_node -> left_branch);
    if (current_node -> right_branch != NULL) DestroyTree(tree, current_node -> right_branch);

    (tree -> node_size)--;
    free(current_node);

    return;

}

ErrorType TreeVerify(struct Tree_t* tree) {

    assert(tree != NULL);

    ErrorType curr_error = SUCCESS;
    if (tree == NULL)
        curr_error |= NULL_POINTER;

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

