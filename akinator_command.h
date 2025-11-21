#ifndef AKINATOR_COMMAND
#define AKINATOR_COMMAND

#include "structs.h"
#include "enum_tree.h"

enum ProgrammReturn RunAkinatorInterface(struct Akinator* akinator);
enum ProgrammReturn StartCreateDefinition(struct Akinator* akinator);
enum ProgrammReturn StartCompareObjects(struct Akinator* akinator);
enum ProgrammReturn ExitTheProgram(struct Akinator* akinator);
enum ProgrammReturn StartProgram(struct Commands_t* basic_command, int command_count, struct Akinator* akinator);

#endif
