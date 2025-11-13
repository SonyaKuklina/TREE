#ifndef TREE_PRIVATE
#define TREE_PRIVATE

#include "enum_tree.h"
#include "struct_tree.h"

void TreeInit(struct Tree_t* tree);
struct Node_t* CreateNode(TreeElement element, struct Tree_t* tree);
//void DestroyTree(struct Tree_t* tree, struct Node_t* current_node, char branch);
void DestroyTree(struct Tree_t* tree, struct Node_t* current_node);
void DumpTree(struct Tree_t* tree, const char* file, const int line);
ErrorType TreeVerify(struct Tree_t* tree);
void SubTreeVerify(struct Node_t* curr_node, struct Node_t* expected_parent, ErrorType* curr_error);

struct Tree_t* CreateAkinatorTree();
#endif
