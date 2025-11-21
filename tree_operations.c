#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree_operations.h"
#include "tree_private.h"

#define MAX_SIZE_STR 100
#define STRING(x) #x
#define SIZE_STR(x) STRING(x)


enum ProgrammReturn PlayAkinator(struct Akinator* akinator) {

    assert(akinator != NULL);
    enum ProgrammReturn completion_status = AkinatorVerify(akinator);
    if (completion_status == INCORRECT) return INCORRECT;

    bool repeat_play = true;

    while (repeat_play) {

        AskQuestion(akinator);
        printf("Play again?: ");
        char* answer = GetUserResponse();
        repeat_play = ((strcmp("Yes", answer) == 0) || (strcmp("yes", answer) == 0));
        free(answer);

    }

    return completion_status;

}

void AskQuestion(struct Akinator* akinator) {

    assert(akinator != NULL);

    struct Node_t* current_node = (akinator -> tree) -> root;

    while (current_node != NULL) {

        if ((current_node -> left_branch == NULL) && (current_node -> right_branch == NULL)) {
            CheckAnswer(current_node, akinator);
            return;
        }

        printf("%s?: ", current_node -> node_element);
        char* answer = GetUserResponse();

        if ((strcmp("Yes", answer) == 0) || (strcmp("yes", answer) == 0)) current_node = current_node -> left_branch;
        else current_node = current_node -> right_branch;

        free(answer);

    }

}


void CheckAnswer(struct Node_t* current_node, struct Akinator* akinator) {

    assert(akinator != NULL);

    printf("Is it %s? ", current_node -> node_element);
    char* answer = GetUserResponse();

    if ((strcmp("yes", answer) == 0) || (strcmp("Yes", answer) == 0)) {

        printf("I guessed it! ");
        free(answer);
        return;

    } else {

        printf("What did you guess? : ");
        char* search_object = GetUserResponse();
        printf("What is the difference between %s and the %s? : ", search_object, current_node -> node_element);
        char* difference = GetUserResponse();
        AnalysisAttribute(difference);
        AddNodes(current_node, akinator, search_object, difference);
        return;

    }

}

void AddNodes(struct Node_t* current_node, struct Akinator* akinator,
              char* search_object, char* difference) {

    assert(akinator      != NULL);
    assert(search_object != NULL);
    assert(difference    != NULL);

    TreeElement old_answer    = current_node -> node_element;
    struct Node_t* left_node  = CreateNode(search_object, akinator -> tree);
    struct Node_t* right_node = CreateNode(old_answer, akinator -> tree);

    current_node -> node_element = difference;
    current_node -> left_branch  = left_node;
    current_node -> right_branch = right_node;

    left_node  -> parent = current_node;
    right_node -> parent = current_node;


}

void AnalysisAttribute(char* difference) {

    assert(difference != NULL);

    bool flag = false;

    do {

    if ((strstr(difference, " not ") != NULL) ||
        (strstr(difference, "not ")  != NULL) ||
        (strstr(difference, " not")  != NULL) ||
        (strstr(difference, "Not ")  != NULL) ||
        (strstr(difference, " no ")  != NULL)) {

        printf("The sign is too complex, please repeat: ");
        difference = GetUserResponse();

    } else {

        flag = true;

    }

    } while(!flag);

}

char* GetUserResponse() {

    char* answer = (char*)calloc(MAX_SIZE_STR, sizeof(char));
    assert(answer != NULL);
    scanf("%" SIZE_STR(MAX_SIZE_STR) "[^\n]", answer);
    getchar();
    return answer;

}




