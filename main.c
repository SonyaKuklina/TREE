#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "struct_tree.h"
#include "enum_tree.h"
#include "tree_operations.h"
#include "tree_private.h"
#include "output.h"

#define DUMP_TREE(x) DumpTree((x), __FILE__, __LINE__)

int main(void) {

    struct Tree_t tree = {};
    TreeInit(&tree);
    if (InsertInTree(10, &tree) != CORRECT)   return INCORRECT;
    if (InsertInTree(5, &tree) != CORRECT)    return INCORRECT;
    if (InsertInTree(20, &tree) != CORRECT)   return INCORRECT;
    if (InsertInTree(3, &tree) != CORRECT)    return INCORRECT;
    if (InsertInTree(7, &tree) != CORRECT)    return INCORRECT;
    if (InsertInTree(15, &tree) != CORRECT)   return INCORRECT;
    if (InsertInTree(6, &tree) != CORRECT)    return INCORRECT;
    if (InsertInTree(13, &tree) != CORRECT)   return INCORRECT;
    if (InsertInTree(16, &tree) != CORRECT)   return INCORRECT;
    if (DeleteFromTree(15, &tree) != CORRECT) return INCORRECT;
    PrintNode(tree.root);
    DUMP_TREE(&tree);

    return CORRECT;
}
