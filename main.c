#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "struct_tree.h"
#include "enum_tree.h"
#include "tree_operations.h"
#include "tree_private.h"
#include "output.h"
#include "describe_object.h"

#define DUMP_TREE(x) DumpTree((x), __FILE__, __LINE__)

int main(void) {

    struct Tree_t* tree = CreateAkinatorTree();
    //DUMP_TREE(tree);
    Akinator(tree);
    DUMP_TREE(tree);
    if (CreateDescribe("Katya K", tree) == INCORRECT) return INCORRECT;
    return CORRECT;

}
