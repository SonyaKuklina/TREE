#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "tree_operations.h"
#include "tree_private.h"

enum ProgrammReturn InsertInTree(TreeElement element, struct Tree_t* tree) {

    assert(tree != NULL);
    if (TreeVerify(tree) != SUCCESS) return INCORRECT;

    struct Node_t* node = CreateNode(element);
    assert(node != NULL);

    if (tree -> root == NULL) {

        tree -> root = node;

    } else {

        struct Node_t* current_node = tree -> root;
        struct Node_t* parent_node  = NULL;

        while (current_node != NULL) {

            parent_node = current_node;

            if      (element < current_node -> node_element)  current_node = current_node -> left_branch;
            else if (element > current_node -> node_element)  current_node = current_node -> right_branch;
            else if (element == current_node -> node_element) return CORRECT;//то есть элемент уже есть в дереве, повторно не добавляю

        }

        if (element <= parent_node -> node_element) parent_node -> left_branch = node;
        else parent_node -> right_branch = node;

        node -> parent = parent_node;

    }

    (tree -> node_count)++;
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

        current_element = current_node -> node_element;

    }

    if (current_node == NULL) return CORRECT;

    if      (current_node == (tree -> root))        DestroyTree(tree, current_node, 'N');
    else if (element > parent_node -> node_element) DestroyTree(tree, current_node, 'R');
    else if (element < parent_node -> node_element) DestroyTree(tree, current_node, 'L');

    (tree -> node_count)--;

    return CORRECT;

}
