#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tree_operations.h"
#include "tree_private.h"

enum ProgrammReturn InsertInTree(TreeElement element, struct Tree_t* tree) {

    assert(tree != NULL);
    if (TreeVerify(tree) != SUCCESS) return INCORRECT;

    struct Node_t* node = CreateNode(element, tree);
    assert(node != NULL);

    if (tree -> root != NULL) {

        struct Node_t* current_node = tree -> root;
        struct Node_t* parent_node  = NULL;

        while (current_node != NULL) {

            parent_node = current_node;

            if      (element < current_node -> node_element)  current_node = current_node -> left_branch;
            else if (element > current_node -> node_element)  current_node = current_node -> right_branch;
            else if (element == current_node -> node_element) {
                free(node);//
                return CORRECT;
            }

        }

        if (element <= parent_node -> node_element) parent_node -> left_branch = node;
        else parent_node -> right_branch = node;

        node -> parent = parent_node;

    } else {

        tree -> root = node;

    }

    (tree -> node_size)++;

    return CORRECT;

}

enum ProgrammReturn DeleteFromTree(TreeElement element, struct Tree_t* tree) {

    assert(tree != NULL);
    if (TreeVerify(tree) != SUCCESS) return INCORRECT;

    struct Node_t* current_node = tree -> root;
    struct Node_t* parent_node  = NULL;
    TreeElement current_element = current_node -> node_element;

    while (element != current_element) {

        parent_node = current_node;

        if (element < current_element) current_node = current_node -> left_branch;
        else current_node = current_node -> right_branch;

        if (current_node == NULL) return CORRECT; //элемент, который я хочу удалить не был найден

        current_element = current_node -> node_element;

    }

    if (current_node == NULL) return CORRECT;

    if (parent_node == NULL) {

        DestroyTree(tree, current_node);

    } else if (parent_node->left_branch == current_node) {

        DestroyTree(tree, current_node);
        parent_node->left_branch = NULL;

    } else {

        DestroyTree(tree, current_node);
        parent_node->right_branch = NULL;

    }

    return CORRECT;

}
