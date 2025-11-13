#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "work_with_file.h"

void OpenFile(struct Tree_t* tree) {

    assert(tree != NULL);

    FILE* file = fopen("tree_akinator.txt", "w");
    WriteToFile(file, tree -> root);

}

void WriteToFile(FILE* file, struct Node_t* current_node) {

    assert(file != NULL);

    fprintf(file, "( ");
    fprintf(file, "\"%s\"", current_node -> node_element);

}
