#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack_for_road.h"
#include "similiar_object.h"
#include "describe_object.h"

#define MIN(x,y) ((x) < (y)) ? (x) : (y)

enum ProgrammReturn CompareObjects(char* one_object, char* two_object, struct Akinator* akinator) {

    assert(one_object != NULL);
    assert(two_object != NULL);
    assert(akinator   != NULL);

    enum SearchList status_node_one = SearchObject(one_object, akinator, akinator -> stack_object_one);
    if (FoundObjectToCompare(status_node_one, one_object) == INCORRECT) return INCORRECT;

    enum SearchList status_node_two = SearchObject(two_object, akinator, akinator -> stack_object_two);
    if (FoundObjectToCompare(status_node_two, two_object) == INCORRECT) return INCORRECT;

    int common_count = CountCommonAttribute(akinator);
    printf("%d\n", common_count);
    if (common_count > 0) {
        PrintCommonAtt(one_object, two_object, akinator, common_count);
        PrintDifferentAtt(one_object, two_object, akinator, common_count);
    } else {
        PrintDifferentAtt(one_object, two_object, akinator, common_count);
    }


    return CORRECT;

}

void PrintCommonAtt(char* one_object, char* two_object, struct Akinator* akinator, int common_count) {

    assert(one_object     != NULL);
    assert(two_object     != NULL);
    assert(akinator       != NULL);

    printf("%s and %s similar in that it is", one_object, two_object);
    size_t size_stack_one = (akinator -> stack_object_one) -> size_stack;

    for (int index = 0; index < common_count - 2; index++)
        PrintObjectAttributes(akinator -> stack_object_one, &index);

    PrintLastObjectAttribute(akinator -> stack_object_one, common_count - 2);


}

void PrintDifferentAtt(char* one_object, char* two_object, struct Akinator* akinator, int common_count) {

    assert(one_object     != NULL);
    assert(two_object     != NULL);
    assert(akinator       != NULL);

    printf("Objects are different in that %s", one_object);

    size_t size_stack_one = (akinator -> stack_object_one) -> size_stack;
    size_t size_stack_two = (akinator -> stack_object_two) -> size_stack;

    for (int index = common_count;  index < size_stack_one - 1; index++)
        PrintObjectAttributes(akinator -> stack_object_one, &index);

    printf("and %s", two_object);

    for (int index = common_count; index < size_stack_two - 2; index++)
        PrintObjectAttributes(akinator -> stack_object_two, &index);

    PrintLastObjectAttribute(akinator -> stack_object_two, size_stack_two - 2);

}

enum ProgrammReturn FoundObjectToCompare(enum SearchList status_find_node, char* one_object) {

    assert(one_object != NULL);

    switch (status_find_node) {

        case SEARCH_SUCCESS: return CORRECT;

        case NODE_NOT_FOUND: printf("Object '%s' not found. Please try again.\n", one_object);
                             return CORRECT;

        case SEARCH_ERROR:   return INCORRECT;

        default:             assert(0);
                             return INCORRECT;

    }
}

int CountCommonAttribute(struct Akinator* akinator) {

    assert(akinator != NULL);

    int common_count = 0;

    int common_size = MIN((akinator -> stack_object_one) -> size_stack, (akinator -> stack_object_two) -> size_stack);

    for (int index = 0; index < common_size; index++) {

        struct Node_t* curr_node_one = (akinator -> stack_object_one) -> curr_node[common_count];
        struct Node_t* curr_node_two = (akinator -> stack_object_two) -> curr_node[common_count];
        struct Node_t* next_node_one = (akinator -> stack_object_one) -> curr_node[common_count + 1];
        struct Node_t* next_node_two = (akinator -> stack_object_two) -> curr_node[common_count + 1];

        if (curr_node_one != curr_node_two) break;
        if ((curr_node_one -> left_branch == next_node_one) != (curr_node_two -> left_branch == next_node_two)) break;

        common_count++;

    }

    return common_count;


}




