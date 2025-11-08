#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "output.h"

void PrintNode(struct Node_t* node) {

    if (node == NULL) return;
    printf("( ");
    if (node -> left_branch != NULL)
        PrintNode(node -> left_branch);
    if (node -> right_branch != NULL)
        PrintNode(node -> right_branch);
    printf("%d ", node -> node_element);
    printf(") ");
    return;

}
