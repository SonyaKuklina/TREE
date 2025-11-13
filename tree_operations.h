#ifndef TREE_OPERATIONS
#define TREE_OPERATIONS

#include "enum_tree.h"
#include "struct_tree.h"

enum ProgrammReturn InsertInTree(TreeElement element, struct Tree_t* tree);
enum ProgrammReturn DeleteFromTree(TreeElement element, struct Tree_t* tree);

void Akinator(struct Tree_t* tree);
void PlayAkinator(struct Tree_t* tree);
void QuestionAnswer(struct Node_t* current_node, struct Tree_t* tree);
void GetAnswerToRepeatGame(struct Node_t* current_node, struct Tree_t* tree);
void AddNodes(struct Node_t* current_node, struct Tree_t* tree,
              char* search_object, char* difference);
void AnalysisAttribute(char* difference);
void ChangeStrDifference(char* difference);

#endif
