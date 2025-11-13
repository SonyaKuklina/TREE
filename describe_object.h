#ifndef DESCRIBE_OBJECT
#define DESCRIBE_OBJECT

#include "enum_tree.h"

enum ProgrammReturn CreateDescribe(char* search_list, struct Tree_t* tree);
struct Node_t* SearchList(struct Node_t* current_node, char* search_list);
int CreateRoadToNode(struct Node_t* search_node, struct Tree_t* tree, struct Stack_t* stack_road);
void PrintDescribe(struct Stack_t* stack_road, char* search_list, int size_road);

#endif
