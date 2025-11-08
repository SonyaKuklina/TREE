#ifndef TREE_OPERATIONS
#define TREE_OPERATIONS

#include "enum_tree.h"
#include "struct_tree.h"

enum ProgrammReturn InsertInTree(TreeElement element, struct Tree_t* tree);
enum ProgrammReturn DeleteFromTree(TreeElement element, struct Tree_t* tree);

#endif
