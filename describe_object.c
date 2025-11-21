#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "describe_object.h"
#include "enum_tree.h"
#include "structs.h"
#include "stack_for_road.h"

const int MAX_CAPACITY = 100;

enum ProgrammReturn CreateDescribe(char* search_list, struct Akinator* akinator) {

    assert(search_list != NULL);
    assert(akinator    != NULL);

    enum SearchList status_node_find = SearchObject(search_list, akinator, akinator -> stack_road_def);
    if (FoundObjectToDescribe(status_node_find, akinator, search_list) == INCORRECT) return INCORRECT;

    return CORRECT;

}


enum SearchList SearchList(struct Node_t* current_node, char* search_list,struct Stack_t* stack, struct Node_t** result_node) {

    assert(search_list != NULL);
    assert(stack       != NULL);
    assert(result_node != NULL);

    if (current_node == NULL) return NODE_NOT_FOUND;

    if (StackPush(stack, current_node) == INCORRECT) return SEARCH_ERROR;

    if (strcmp(current_node -> node_element, search_list) == 0) {
        *result_node = current_node;
        return SEARCH_SUCCESS;
    }

    enum SearchList left_node_status = SearchList(current_node -> left_branch, search_list, stack, result_node);
    if (left_node_status == SEARCH_SUCCESS) return SEARCH_SUCCESS;
    enum SearchList right_node_status = SearchList(current_node -> right_branch, search_list, stack, result_node);
    if (right_node_status == SEARCH_SUCCESS) return SEARCH_SUCCESS;

    StackPop(stack);
    return NODE_NOT_FOUND;

}

void PrintDescribe(struct Akinator* akinator, char* search_list) {

    assert(akinator    != NULL);
    assert(search_list != NULL);

    printf("%s -", search_list);

    size_t size_stack = (akinator -> stack_road_def) -> size_stack;
    for (int index = 0; index < size_stack - 2; index++) PrintObjectAttributes(akinator -> stack_road_def, &index);
    PrintLastObjectAttribute(akinator -> stack_road_def, size_stack - 2);

}


void PrintObjectAttributes(struct Stack_t* stack_road, int* index) {

    assert(stack_road != NULL);
    assert(index      != NULL);

    struct Node_t* current_node = stack_road -> curr_node[*index];
    TreeElement attribute = current_node -> node_element;

    struct Node_t* next_node = stack_road -> curr_node[(*index) + 1];

    bool is_left_branch = (current_node -> left_branch == next_node);
    if (is_left_branch) printf(" %s,", attribute);
    else printf(" not %s,", attribute);

}

void PrintLastObjectAttribute(struct Stack_t* stack_road, int index) {

    assert(stack_road != NULL);

    struct Node_t* current_node = stack_road -> curr_node[index];
    TreeElement attribute = current_node -> node_element;

    struct Node_t* next_node = stack_road -> curr_node[++index];

    bool is_left_branch = (current_node -> left_branch == next_node);

    if (is_left_branch) printf(" %s.\n", attribute);
    else printf(" not %s.\n", attribute);

}


enum SearchList SearchObject(char* object_name, struct Akinator* akinator, struct Stack_t* stack) {

    assert(object_name != NULL);
    assert(akinator    != NULL);
    assert(stack       != NULL);

    struct Node_t* result_node = NULL;
    return SearchList((akinator -> tree) -> root, object_name, stack, &result_node);

}

enum ProgrammReturn FoundObjectToDescribe(enum SearchList status_node_find, struct Akinator* akinator, char* search_list) {

    assert(search_list != NULL);

    switch (status_node_find) {

    case SEARCH_SUCCESS: PrintDescribe(akinator, search_list);
                         return CORRECT;

    case NODE_NOT_FOUND: printf("Object '%s' not found. Please try again.\n", search_list);
                         return CORRECT;

    case SEARCH_ERROR:   return INCORRECT;

    default:             assert(0);
                         return INCORRECT;

    }

}
