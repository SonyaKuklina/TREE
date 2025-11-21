#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "akinator_command.h"
#include "tree_operations.h"
#include "work_with_file.h"
#include "describe_object.h"
#include "similiar_object.h"

enum ProgrammReturn RunAkinatorInterface(struct Akinator* akinator) {

    assert(akinator != NULL);

    struct Commands_t basic_command[] = {
                                        {"play akinator",    PlayAkinator},
                                        {"get definition",   StartCreateDefinition},
                                        {"compare objects",  StartCompareObjects},
                                        {"write to file",    WriteTreeToFile},
                                        {"read from file",   ReadTreeFromFile},
                                        {"exit the program", ExitTheProgram}

                                      };


    int command_count = sizeof(basic_command)/sizeof(basic_command[0]);
    enum ProgrammReturn completion_status = StartProgram(basic_command, command_count, akinator);
    return completion_status;

}

enum ProgrammReturn StartCreateDefinition(struct Akinator* akinator) {

    assert(akinator != NULL);

    printf("What do you want to describe?: ");
    char* user_answer = GetUserResponse();
    enum ProgrammReturn completion_status = CreateDescribe(user_answer, akinator);
    free(user_answer);
    return completion_status;

}

enum ProgrammReturn StartCompareObjects(struct Akinator* akinator) {

    assert(akinator != NULL);

    printf("What objects do you want to compare?: ");
    char* object_one = GetUserResponse();
    char* object_two = GetUserResponse();
    enum ProgrammReturn completion_status = CompareObjects(object_one, object_two, akinator);
    free(object_one);
    free(object_two);
    return completion_status;

}

enum ProgrammReturn ExitTheProgram(struct Akinator* akinator) {

    assert(akinator != NULL);
    printf("Thank you for a game! \n");
    return CORRECT;

}

enum ProgrammReturn StartProgram(struct Commands_t* basic_command, int command_count, struct Akinator* akinator) {

    assert(basic_command != NULL);
    assert(akinator      != NULL);

    enum ProgrammState status = PROGRAMM_RUNNING;
    enum ProgrammReturn completion_status = CORRECT;

    while (status) {

        printf("What do you want?: play akinator, get definition, compare objects, write to file, read from file, exit the program \n");
        char* user_choice = GetUserResponse();

        for (int index = 0; index < command_count; index++) {

            if (strcmp(user_choice, "exit the program") == 0) status = PROGRAMM_EXIT;

            if (strcmp(user_choice, basic_command[index].name_command) == 0) {
                completion_status = basic_command[index].function(akinator);
                if (completion_status == INCORRECT) return completion_status;
            }

        }

    }

    return completion_status;

}
