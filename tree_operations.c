#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "tree_operations.h"
#include "tree_private.h"

#define MAX_SIZE_STR 100
#define STRINGIFY(x) #x
#define SIZE_STR(x) STRINGIFY(x)

enum ProgrammReturn InsertInTree(TreeElement element, struct Tree_t* tree) {

    assert(tree != NULL);
    if (TreeVerify(tree) != SUCCESS) return INCORRECT;

    struct Node_t* node = CreateNode(element, tree);
    assert(node != NULL);

    if (tree -> root != NULL) {

        struct Node_t* current_node = tree -> root;
        struct Node_t* parent_node  = NULL;

        while (current_node != NULL) {

            parent_node = current_node;

            if      (element < current_node -> node_element)  current_node = current_node -> left_branch;
            else if (element > current_node -> node_element)  current_node = current_node -> right_branch;
            else if (element == current_node -> node_element) {
                free(node);//
                return CORRECT;
            }

        }

        if (element <= parent_node -> node_element) parent_node -> left_branch = node;
        else parent_node -> right_branch = node;

        node -> parent = parent_node;

    } else {

        tree -> root = node;

    }

    (tree -> node_size)++;

    return CORRECT;

}

enum ProgrammReturn DeleteFromTree(TreeElement element, struct Tree_t* tree) {

    assert(tree != NULL);
    if (TreeVerify(tree) != SUCCESS) return INCORRECT;

    struct Node_t* current_node = tree -> root;
    struct Node_t* parent_node  = NULL;
    TreeElement current_element = current_node -> node_element;

    while (element != current_element) {

        parent_node = current_node;

        if (element < current_element) current_node = current_node -> left_branch;
        else current_node = current_node -> right_branch;

        if (current_node == NULL) return CORRECT; //элемент, который я хочу удалить не был найден

        current_element = current_node -> node_element;

    }

    if (current_node == NULL) return CORRECT;

    if (parent_node == NULL) {

        DestroyTree(tree, current_node);

    } else if (parent_node->left_branch == current_node) {

        DestroyTree(tree, current_node);
        parent_node->left_branch = NULL;

    } else {

        DestroyTree(tree, current_node);
        parent_node->right_branch = NULL;

    }

    return CORRECT;

}

void Akinator(struct Tree_t* tree) {

    assert(tree != NULL);

    PlayAkinator(tree);

    printf("Thank you for game!\n");

}

void PlayAkinator(struct Tree_t* tree) {

    assert(tree != NULL);

    bool repeat_play = true;
    char answer[MAX_SIZE_STR];

    while (repeat_play) {

        QuestionAnswer(tree -> root, tree);
        printf("Play again?: ");
        scanf("%" SIZE_STR(MAX_SIZE_STR) "[^\n]", answer);
        getchar();
        repeat_play = ((strcmp("Yes", answer) == 0) || (strcmp("yes", answer) == 0));

    }

}

void QuestionAnswer(struct Node_t* current_node, struct Tree_t* tree) {

    assert(tree != NULL);

    if ((current_node -> left_branch == NULL) && (current_node -> right_branch == NULL)) {
        GetAnswerToRepeatGame(current_node, tree);
        return;
    }

    printf("%s: ", current_node -> node_element);
    char answer[MAX_SIZE_STR];
    scanf("%" SIZE_STR(MAX_SIZE_STR) "[^\n]", answer);
    getchar();

    if ((strcmp("Yes", answer) == 0) || (strcmp("yes", answer) == 0)) {
        QuestionAnswer(current_node -> left_branch, tree);
    }
    else {
        QuestionAnswer(current_node -> right_branch, tree);
    }

}


void GetAnswerToRepeatGame(struct Node_t* current_node, struct Tree_t* tree) {

    assert(tree != NULL);

    char* answer        = (char*)calloc(MAX_SIZE_STR, sizeof(char));
    char* search_object = (char*)calloc(MAX_SIZE_STR, sizeof(char));
    char* difference    = (char*)calloc(MAX_SIZE_STR, sizeof(char));

    printf("Is it %s? ", current_node -> node_element);
    scanf("%" SIZE_STR(MAX_SIZE_STR) "[^\n]", answer);
    getchar();

    if ((strcmp("yes", answer) == 0) || (strcmp("Yes", answer) == 0)) {

        printf("I guessed it! ");
        return;

    } else {

        printf("What did you guess? : ");
        scanf("%" SIZE_STR(MAX_SIZE_STR) "[^\n]", search_object);
        getchar();
        printf("What is the difference between %s and the %s? : ", search_object, current_node -> node_element);
        scanf("%" SIZE_STR(MAX_SIZE_STR) "[^\n]", difference);
        getchar();
        AnalysisAttribute(difference);
        AddNodes(current_node, tree, search_object, difference);
        return;

    }


}

void AddNodes(struct Node_t* current_node, struct Tree_t* tree,
              char* search_object, char* difference) {

    assert(tree          != NULL);
    assert(search_object != NULL);
    assert(difference    != NULL);

    TreeElement old_answer    = current_node -> node_element;
    struct Node_t* left_node  = CreateNode(search_object, tree);
    (tree -> node_size)++;
    struct Node_t* right_node = CreateNode(old_answer, tree);
    (tree -> node_size)++;

    ChangeStrDifference(difference);

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
        scanf("%" SIZE_STR(MAX_SIZE_STR) "[^\n]", difference);
        getchar();

    } else {

        flag = true;

    }

    } while(!flag);

}

void ChangeStrDifference(char* difference) {

    assert(difference != NULL);

    int len_str = strlen(difference);
    *(difference + len_str) = '?';
    *(difference + len_str + 1) = '\0';

    if (!isupper(*difference)) *difference = *difference - 32;

}


