#ifndef TREE_PRIVATE
#define TREE_PRIVATE

#include "enum_tree.h"
#include "structs.h"

void TreeInit(struct Tree_t* tree);
struct Node_t* CreateNode(TreeElement element, struct Tree_t* tree);
enum ProgrammReturn AkinatorVerify(struct Akinator* akinator);
void DumpTree(struct Tree_t* tree, const char* file, const int line);
ErrorType TreeVerify(struct Tree_t* tree);
void SubTreeVerify(struct Node_t* curr_node, struct Node_t* expected_parent, ErrorType* curr_error);
struct Node_t* CreateNodeDubl(TreeElement element);
struct Tree_t* CreateAkinatorTree();
struct Akinator* CreateAkinator();
enum ProgrammReturn DestroyAkinator(struct Akinator* akinator);
void DestroyTree(struct Tree_t* tree);
void DestroySubtree(struct Node_t* node);


#endif
