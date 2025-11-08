#ifndef TREE_GRAPH
#define TREE_GRAPH

#include <stdbool.h>
#include "struct_tree.h"

#define SIZE_NAME_PNG 100

void GraphicalDumpTree(struct Tree_t* tree, const char* file, const int line);
bool CreateNamePng(char* file_name_dot, char* png_file);
void CreateAndOpenHtmlFile(char* png_file, struct Tree_t* tree,
                           const char* file, const int line);
void CreateDotFile(struct Tree_t* tree);
void CreateNodesGraph(struct Node_t* node, FILE* file_dot);
void CreateConnectionsNodesGraph(struct Node_t* node, FILE* file);

#endif
