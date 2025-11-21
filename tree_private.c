#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree_private.h"
#include "structs.h"
#include "tree_graph.h"
#include "stack_for_road.h"

void TreeInit(struct Tree_t* tree) {

    assert(tree != NULL);
    tree -> root = NULL;
    tree -> node_size = 0;

}

struct Akinator* CreateAkinator() {

    struct Akinator* akinator = (struct Akinator*)calloc(1, sizeof(struct Akinator));

    if (akinator == NULL) {
        free(akinator);
        return NULL;
    }

    akinator -> tree = CreateAkinatorTree();
    if (akinator -> tree == NULL) {
        free(akinator -> tree);
        return NULL;
    }

    akinator -> stack_road_def = CreateStack(SIZE_STACK);
    if (akinator -> stack_road_def == NULL) {
        free(akinator -> stack_road_def);
        return NULL;
    }

    akinator -> stack_object_one = CreateStack(SIZE_STACK);
    if (akinator -> stack_object_one == NULL) {
        free(akinator -> stack_object_one);
        return NULL;
    }

    akinator -> stack_object_two= CreateStack(SIZE_STACK);
    if (akinator -> stack_object_two == NULL) {
        free(akinator -> stack_object_two);
        return NULL;
    }

    return akinator;

}

struct Tree_t* CreateAkinatorTree() {

    struct Tree_t* tree = (struct Tree_t*)calloc(1, sizeof(struct Tree_t));
    assert(tree != NULL);

    tree->root = CreateNode((TreeElement)"animal", tree);

    tree->root->left_branch  = CreateNode((TreeElement)"cat", tree);
    tree->root->right_branch = CreateNode((TreeElement)"teach math", tree);
    ((tree -> root) -> right_branch) -> left_branch  = CreateNode((TreeElement)"lukash", tree);
    ((tree -> root) -> right_branch) -> right_branch = CreateNode((TreeElement)"bogdanov", tree);

    tree->root->left_branch->parent  = tree->root;
    tree->root->right_branch->parent = tree->root;

    (((tree -> root) -> right_branch) -> left_branch) -> parent  = tree->root->right_branch;
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
    (tree -> node_size)++;
    return node;
}


enum ProgrammReturn AkinatorVerify(struct Akinator* akinator) {

    ErrorType curr_error = SUCCESS;

    if (akinator == NULL) curr_error |= NULL_POINTER;
    if (curr_error != SUCCESS) return INCORRECT;

    curr_error |= StackVerify(akinator -> stack_road_def);
    curr_error |= StackVerify(akinator -> stack_object_one);
    curr_error |= StackVerify(akinator -> stack_object_two);
    curr_error |= TreeVerify(akinator -> tree);

    if (curr_error == INCORRECT) return INCORRECT;
    return CORRECT;

}

ErrorType TreeVerify(struct Tree_t* tree) {

    assert(tree != NULL);

    ErrorType curr_error = SUCCESS;

    if (tree == NULL) curr_error |= NULL_POINTER;
    if (((tree -> root) -> parent) != NULL) curr_error |= ERROR_ROOT_PARENT;
    if ((tree -> root == NULL) && (tree -> node_size != 0)) curr_error |= ERROR_NODE_SIZE;
    if (tree -> root != NULL) SubTreeVerify(tree -> root, NULL, &curr_error);

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


void DestroySubtree(struct Node_t* node) {

    if (node == NULL) return;

    DestroySubtree(node -> left_branch);
    DestroySubtree(node -> right_branch);
    free(node -> node_element);
    free(node);

}

void DestroyTree(struct Tree_t* tree) {

    if (tree == NULL) return;
    DestroySubtree(tree -> root);
    free(tree);

}

enum ProgrammReturn DestroyAkinator(struct Akinator* akinator) {

    if (akinator == NULL) return INCORRECT;

    DestroyStack(akinator -> stack_road_def);
    DestroyStack(akinator -> stack_object_one);
    DestroyStack(akinator -> stack_object_two);

    DestroyTree(akinator -> tree);

    free(akinator);
    return CORRECT;

}


