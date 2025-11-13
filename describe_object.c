#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "describe_object.h"
#include "enum_tree.h"
#include "struct_tree.h"
#include "stack_for_road.h"

enum ProgrammReturn CreateDescribe(char* search_list, struct Tree_t* tree) {

    assert(search_list != NULL);
    assert(tree        != NULL);

    struct Stack_t* stack_road = (struct Stack_t*)calloc(tree -> node_size, sizeof(struct Stack_t));
    if (stack_road == NULL) return INCORRECT;
    struct Node_t* search_node = SearchList(tree -> root, search_list);
    int size_road = CreateRoadToNode(search_node, tree, stack_road);
    PrintDescribe(stack_road, search_list, size_road);
    return CORRECT;

}

struct Node_t* SearchList(struct Node_t* current_node, char* search_list) {

    assert(search_list != NULL);

    if (current_node == NULL) return NULL;

    if (strcmp(current_node -> node_element, search_list) == 0) return current_node;

    struct Node_t* node = SearchList(current_node -> left_branch, search_list);
    if (node != NULL) return node;
    node = SearchList(current_node -> right_branch, search_list);
    return node;

}

int CreateRoadToNode(struct Node_t* search_node, struct Tree_t* tree, struct Stack_t* stack_road) {

    assert(stack_road != NULL);

    struct Node_t* current_node = search_node;
    int index = 0;
    while (current_node != tree -> root) {

        stack_road[index].curr_node = current_node -> parent;
        stack_road[index].answer    = (stack_road[index].curr_node -> left_branch == current_node) ? true : false;
        current_node = current_node -> parent;
        index++;

    }

    return index;

}

void PrintDescribe(struct Stack_t* stack_road, char* search_list, int size_road) {

    assert(stack_road != NULL);
    assert(search_list != NULL);

    printf("%s - ", search_list);

    for (int index = size_road - 1; index >= 0; index--) {

        TreeElement attribute = stack_road[index].curr_node -> node_element;
        char* copy_attribute = strdup(attribute);
        *copy_attribute = (char)tolower(*copy_attribute);
        int len_att = strlen(copy_attribute);
        *(copy_attribute + len_att - 1) = '\0';

        if (index == 0) {

            if (!stack_road[index].answer) printf("not %s.", copy_attribute);
            else printf("%s.", copy_attribute);

        } else {

            if (!stack_road[index].answer) printf("not %s, ", copy_attribute);
            else printf("%s, ", copy_attribute);

        }

    }


}
