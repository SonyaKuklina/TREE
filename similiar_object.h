#ifndef SIMILIAR_OBJECT
#define SIMILIAR_OBJECT

#include "structs.h"
#include "enum_tree.h"

enum ProgrammReturn CompareObjects(char* one_object, char* two_object, struct Akinator* akinator);
void PrintDifferentAtt(char* one_object, char* two_object, struct Akinator* akinator, int curr_index);
enum ProgrammReturn FoundObjectToCompare(enum SearchList status_find_node, char* one_object);
int CountCommonAttribute(struct Akinator* akinator);
void PrintCommonAtt(char* one_object, char* two_object, struct Akinator* akinator, int common_count);



#endif
