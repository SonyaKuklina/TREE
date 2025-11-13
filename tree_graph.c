#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "tree_graph.h"

void GraphicalDumpTree(struct Tree_t* tree, const char* file, const int line) {

    assert(file != NULL);

    CreateDotFile(tree);

    char* file_name_dot = "debug.dot";
    char file_name_png[SIZE_NAME_PNG];
    char* png_file = file_name_png;
    if (CreateNamePng(file_name_dot, png_file)) {
        CreateAndOpenHtmlFile(png_file, tree, file, line);
    }

}

void CreateDotFile(struct Tree_t* tree) {

    assert(tree != NULL);

    FILE* file_dot = fopen("debug.dot", "w");
    fprintf(file_dot, "digraph G {\n");
    fprintf(file_dot, "    bgcolor = \"white\";\n");
    fprintf(file_dot, "    rankdir = TB;\n");
    fprintf(file_dot, "    nodesep = 0.5;\n");
    fprintf(file_dot, "    ranksep = 2.0;\n");
    fprintf(file_dot, "    splines = ortho;\n");
    fprintf(file_dot, "    node [style = \"filled\", shape = Mrecord,\n");
    fprintf(file_dot, "         fillcolor = aquamarine, color = black,\n");
    fprintf(file_dot, "         width = 0.2, height = 0.4];\n");
    CreateNodesGraph(tree -> root, file_dot);
    CreateConnectionsNodesGraph(tree -> root, file_dot);
    fprintf(file_dot, "}");
    fclose(file_dot);

}

void CreateNodesGraph(struct Node_t* node, FILE* file_dot) {

    assert(file_dot != NULL);

    if (node == NULL) return;

    fprintf(file_dot, "node%d  [label = \"{<par> parent: %p | <el> node_element: %s | {<left> left_branch: %p | <right> right_branch: %p}}\"];\n",
                node -> num_node, node -> parent, node -> node_element, node -> left_branch, node -> right_branch);

    if (node -> left_branch != NULL) {
        CreateNodesGraph(node -> left_branch, file_dot);
    }

    if (node -> right_branch != NULL) {
        CreateNodesGraph(node -> right_branch, file_dot);
    }

}

void CreateConnectionsNodesGraph(struct Node_t* node, FILE* file_dot) {

    assert(file_dot != NULL);
    if (node == NULL) return;

    if (node -> left_branch != NULL) {

        if (((node -> left_branch) -> parent) == node)
            fprintf(file_dot, "node%d:left -> node%d:par [color = seagreen];\n",
                    node -> num_node, (node -> left_branch) -> num_node);
        else
            fprintf(file_dot, "node%d:left -> node%d:par [color = crimson];\n",
                    node -> num_node, (node -> left_branch) -> num_node);

        CreateConnectionsNodesGraph(node -> left_branch, file_dot);

    }

    if (node -> right_branch != NULL) {

        if (((node -> right_branch) -> parent) == node)
            fprintf(file_dot, "node%d:right -> node%d:par [color = seagreen];\n",
                    node -> num_node, (node -> right_branch) -> num_node);
        else
            fprintf(file_dot, "node%d:right -> node%d:par [color = crimson];\n",
                    node -> num_node, (node -> right_branch) -> num_node);

        CreateConnectionsNodesGraph(node -> right_branch, file_dot);

    }

}

bool CreateNamePng(char* file_name_dot, char* png_file) {

    assert(file_name_dot != NULL);
    assert(png_file      != NULL);

    char* file_name = strchr(file_name_dot, '.');

    if (file_name == NULL) return false;

    long int len_file_name = file_name - file_name_dot;
    png_file = strncpy(png_file, file_name_dot, len_file_name);
    *(png_file + len_file_name) = '\0';
    png_file = strcat(png_file, ".png");

    char command[100];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s", file_name_dot, png_file);
    if (system(command) == 0) return true;
    return false;

}

void CreateAndOpenHtmlFile(char* png_file, struct Tree_t* tree,
                           const char* file, const int line) {

    assert(png_file != NULL);
    assert(tree     != NULL);
    assert(file     != NULL);

    FILE* file_html = fopen("debug.html", "w");

    assert(file_html != NULL);

    fprintf(file_html, "<!DOCTYPE html>\n");
    fprintf(file_html, "<body>\n");
    fprintf(file_html, "<h3>TREE</h3>\n");

    fprintf(file_html, "<p>DumpTree called from: %s %d</p>\n", file, line);

    fprintf(file_html, "<img src = \"%s\">\n", png_file);

    fprintf(file_html, "</body>\n");
    fprintf(file_html, "</html>\n");

    fclose(file_html);

    system("explorer debug.html");

}
