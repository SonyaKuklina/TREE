#ifndef TREE_OPERATIONS
#define TREE_OPERATIONS

#include "enum_tree.h"
#include "structs.h"

enum ProgrammReturn InsertInTree(TreeElement element, struct Tree_t* tree);
enum ProgrammReturn DeleteFromTree(TreeElement element, struct Tree_t* tree);

enum ProgrammReturn PlayAkinator(struct Akinator* akinator);
void AskQuestion(struct Akinator* akinator);
void CheckAnswer(struct Node_t* current_node, struct Akinator* akinator);
void AddNodes(struct Node_t* current_node, struct Akinator* akinator,
              char* search_object, char* difference);
void AnalysisAttribute(char* difference);

char* GetUserResponse();

#endif
