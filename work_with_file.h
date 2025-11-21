#ifndef WORK_WITH_FILE
#define WORK_WITH_FILE

#include "structs.h"
#include "enum_tree.h"
#include <stdio.h>

enum ProgrammReturn WriteTreeToFile(struct Akinator* akinator);
void WriteToFile(FILE* file, struct Node_t* current_node);
enum ProgrammReturn ReadTreeFromFile(struct Akinator* akinator);
struct Node_t* ReadFromFile(char* buffer, int* pos, struct Akinator* akinator, struct Node_t* parent_node);
TreeElement GetNodeName(char* buffer, int* pos);
void ShiftPos(char* buffer, int* pos);
void SkipSpaces(char* buffer, int* pos);
#endif
