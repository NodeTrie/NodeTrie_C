#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include "node.h"

char** match_entries(char **keys, char *query) {
    char **matched_entries;
    size_t i = 0, j = 0;
    char *key = keys[i];
    while (key) {
        if (fnmatch(query, key, 0) == 0) {
            matched_entries[j] = key;
            j++;
        }
        i++;
        key = keys[i];
    }
    matched_entries[j+1] = NULL;
    return matched_entries;
}

void print_index(struct Node *node) {
    if (node->children_i > 0) {
        for (size_t i = 0; i < node->children_i; i++) {
           print_index(&node->children[i]);
        }
    }
    printf("Node %s\n", node->name);
}

struct Node* clear(struct Node *node) {
    if(!node) return node;
    if (node->children_i > 0) {
        for (size_t i = 0; i < node->children_i; i++) {
            clear(&node->children[i]);
        }
    }
    printf("Freeing node %s children\n", node->name);
    free(node->children);
    node->children = NULL;
    node->children_i = 0;
    node->children_size = 0;
    // Clear root node if all sub-tree children have been cleared
    if(node != NULL && (node->name == NULL)) {
        free(node);
        node = NULL;
        return node;
    }
}

struct Node* insert(struct Node *parent, char *path) {
    if (!parent->children) {
        parent->children = calloc(parent->children_size, sizeof(struct Node));
    }
    if (parent->children_i == parent->children_size) {
        parent->children_size *= 2;
        printf("Resizing children of %s to %zu\n", parent->name, parent->children_size);
        struct Node *new_children = realloc(parent->children, parent->children_size * sizeof(struct Node));
        if (new_children) {
            parent->children = new_children;
            memset(&parent->children[parent->children_i], 0,
                   sizeof(struct Node) * (parent->children_size - parent->children_i));
        }
        else return NULL;
    }
    parent->children[parent->children_i].name = malloc(strlen(path)+1 * sizeof(char));
    if (strcpy(parent->children[parent->children_i].name, path) == NULL) return NULL;
    parent->children[parent->children_i].children_i = 0;
    parent->children[parent->children_i].children_size = 1;
    printf("Inserted %s to %s\n", parent->children[parent->children_i].name, parent->name);
    parent->children_i++;
    return &parent->children[parent->children_i-1];
}

struct Node* name_is_child(struct Node *node, char *name) {
    struct Node *child;
    for (int i=0; i < node->children_i; i++) {
        child = &node->children[i];
        if (strcmp(child->name, name) == 0) return child;
    }
    return NULL;
}


int insert_str(struct Node *parent, char *path) {
    if (!path) return 0;
    char *token, *string, *tofree;
    tofree = string = strdup(path);
    token = strsep(&string, ".");
    if (token) {
        printf("Inserting node %s to parent %s\n", token, parent->name);
        insert(parent, token);
        struct Node *node = &parent->children[parent->children_i];
        return insert_str(node, string);
    }
    free(tofree);
}

struct Node* build_index(char *paths[]) {
    struct Node *root = init_node();
    struct Node *node, *temp = NULL;
    temp = root;
    size_t i = 0;
    char *path = paths[i];
    while (path) {
        node = insert(temp, path);
        i++;
        path = paths[i];
        temp = node;
    }
    return root;
}

void insert_paths(struct Node *node, char *paths[]) {
    size_t i = 0;
    char *path = paths[i];
    struct Node *child;
    while (path) {
        child = name_is_child(node, path);
        if (child == NULL) {
            child = insert(node, path);
        }
        else {
            printf("Name %s already child of %s\n", path, node->name);
        }
        node = child;
        i++;
        path = paths[i];
    }
}

struct Node* init_node() {
    struct Node *node = malloc(sizeof(struct Node));
    node->name = NULL;
    node->children_i = 0;
    node->children_size = 1;
    node->children = NULL;
    return node;
}

int is_leaf(struct Node *parent) {
    if (!parent) return 0;
    return parent->children_i == 0;
}

int get_children_size(struct Node *node) {
    if (node == NULL) return 0;
    return node->children_i;
}

/*

void insert_all_paths(struct Node *root, char **paths) {
    if(!paths) return;
    size_t i = 0;
    size_t j = 0;
    char *sub_paths = paths[i];
    char *path = sub_paths[j];
    while(path) {
        printf("%s\n", path);
    }
 }*/
