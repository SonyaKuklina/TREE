#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "work_with_file.h"
#include "tree_private.h"

enum ProgrammReturn WriteTreeToFile(struct Akinator* akinator) {

    assert(akinator != NULL);
    enum ProgrammReturn completion_status = AkinatorVerify(akinator);
    if (completion_status == INCORRECT) return INCORRECT;

    FILE* file = fopen("tree_akinator.txt", "w");
    if (file == NULL) return INCORRECT;
    WriteToFile(file, (akinator -> tree) -> root);
    fclose(file);

    return completion_status;

}

enum ProgrammReturn ReadTreeFromFile(struct Akinator* akinator) {

    assert(akinator != NULL);
    enum ProgrammReturn completion_status = AkinatorVerify(akinator);
    if (completion_status == INCORRECT) return INCORRECT;

    FILE* file = fopen("tree_akinator.txt", "r");
    if (file == NULL) return INCORRECT;

    fseek(file , 0 , SEEK_END); //переходим в конец файла
    long file_size = ftell(file); //возвращаем текущую позицию
    rewind(file);//возвращаемся файла для чтения

    char* buffer = (char*)calloc(file_size, sizeof(char));
    if (buffer == NULL) return INCORRECT;

    size_t result_size = fread(buffer, sizeof(char), file_size, file);
    if (result_size != file_size) return INCORRECT;

    (akinator -> tree) -> root = NULL;
    (akinator -> tree) -> node_size = 0;

    int pos = 0;
    ((akinator -> tree) -> root) =  ReadFromFile(buffer, &pos, akinator, NULL);

    free(buffer);

    return CORRECT;

}

void WriteToFile(FILE* file, struct Node_t* current_node) {

    assert(file != NULL);

    if (current_node == NULL) {
        fprintf(file, "nill ");
        return;
    }

    fprintf(file, "( ");
    fprintf(file, "\"%s\" ", current_node -> node_element);

    WriteToFile(file, current_node -> left_branch);
    WriteToFile(file, current_node -> right_branch);

    fprintf(file, " ) ");
    return;

}

struct Node_t* ReadFromFile(char* buffer, int* pos, struct Akinator* akinator, struct Node_t* parent_node) {

    assert(buffer    != NULL);
    assert(pos       != NULL);
    assert(akinator  != NULL);

    if (buffer[*pos] == '(') {

        SkipSpaces(buffer, pos);

        TreeElement name_node = GetNodeName(buffer, pos);
        struct Node_t* current_node   = CreateNode(name_node, akinator -> tree);

        assert(current_node != NULL);

        current_node -> parent        = parent_node;
        current_node -> left_branch   = ReadFromFile(buffer, pos, akinator, current_node);
        current_node -> right_branch  = ReadFromFile(buffer, pos, akinator, current_node);

        (*pos)++;
        SkipSpaces(buffer, pos);

        return current_node;

    }

    if (buffer[*pos] == 'n') {

        ShiftPos(buffer, pos);
        return NULL;

    }

    return NULL;

}

TreeElement GetNodeName(char* buffer, int* pos) {

    assert(buffer != NULL);
    assert(pos    != NULL);

    while (buffer[*pos] != '"') (*pos)++;
    (*pos)++;
    int len_name = strchr(buffer + *pos, '"') - (buffer + *pos);
    TreeElement name_node = strdup(buffer + *pos);
    *(name_node + len_name) = '\0';
    *pos += len_name + 1;

    SkipSpaces(buffer, pos);
    return name_node;

}

void ShiftPos(char* buffer, int* pos) {

    assert(buffer != NULL);
    assert(pos    != NULL);

    while (buffer[*pos] != ' ') (*pos)++;
    SkipSpaces(buffer, pos);

}

void SkipSpaces(char* buffer, int* pos) {

    assert(buffer != NULL);
    assert(pos    != NULL);

    while (buffer[*pos] == ' ') (*pos)++;

}
