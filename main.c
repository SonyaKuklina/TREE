#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "structs.h"
#include "enum_tree.h"
#include "tree_operations.h"
#include "tree_private.h"
#include "output.h"
#include "describe_object.h"
#include "similiar_object.h"
#include "work_with_file.h"
#include "akinator_command.h"

#define DUMP_TREE(x) DumpTree((x), __FILE__, __LINE__)

int main(void) {

    struct Akinator* akinator = CreateAkinator();
    DUMP_TREE(akinator -> tree);
    RunAkinatorInterface(akinator);
    DUMP_TREE(akinator -> tree);
    DestroyAkinator(akinator);
    return CORRECT;

}
