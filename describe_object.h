#ifndef DESCRIBE_OBJECT
#define DESCRIBE_OBJECT

#include "enum_tree.h"

enum ProgrammReturn CreateDescribe(char* search_list, struct Akinator* akinator);
enum SearchList SearchList(struct Node_t* current_node, char* search_list, struct Akinator* akinator, struct Node_t** result_node);
void PrintDescribe(struct Akinator* akinator, char* search_list);
void PrintObjectAttributes(struct Stack_t* stack_road, int* index);
void PrintLastObjectAttribute(struct Stack_t* stack_road, int index);
enum SearchList SearchObject(char* object_name, struct Akinator* akinator, struct Stack_t* stack);
enum ProgrammReturn FoundObjectToDescribe(enum SearchList status_node_find, struct Akinator* akinator, char* search_list);

#endif
