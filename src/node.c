/* This file is part of NodeTrie. */

/* Copyright (C) 2017 Panos Kittenis */

/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation, version 2.1. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <fnmatch.h>
#include "node.h"

static char patterns[4] = "*?[{";

/*
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
*/

void print_index(Node *node) {
    if (node->children_i > 0) {
        for (size_t i = 0; i < node->children_i; i++) {
           print_index(&node->children[i]);
        }
    }
    printf("Node %s\n", node->name);
}

Node* clear(Node *node) {
    if(!node) return node;
    if (node->children_i > 0) {
        for (size_t i = 0; i < node->children_i; i++) {
            clear(&node->children[i]);
        }
    }
    // printf("Freeing node %s children\n", node->name);
    free(node->children);
    free(node->name);
    node->children = NULL;
    node->children_i = 0;
    node->children_size = 0;
    // Clear root node if all sub-tree children have been cleared
    if(node != NULL && (node->name == NULL)) {
        free(node);
        node = NULL;
        return node;
    }
    return node;
}

Node* insert(Node *parent, const char *path) {
    if (!parent->children) {
        parent->children = calloc(parent->children_size, sizeof(Node));
    }
    if (parent->children_i == parent->children_size) {
        parent->children_size *= 2;
        // printf("Resizing children of %s to %zu\n", parent->name, parent->children_size);
        Node *new_children = realloc(parent->children, parent->children_size * sizeof(Node));
        if (new_children) {
            parent->children = new_children;
            memset(&parent->children[parent->children_i], 0,
                   sizeof(Node) * (parent->children_size - parent->children_i));
        }
        else return NULL;
    }
    parent->children[parent->children_i].name = malloc(strlen(path)+1 * sizeof(char));
    if (strcpy(parent->children[parent->children_i].name, path) == NULL) return NULL;
    parent->children[parent->children_i].children_i = 0;
    parent->children[parent->children_i].children_size = 1;
    // printf("Inserted %s to %s\n", parent->children[parent->children_i].name, parent->name);
    parent->children_i++;
    return &parent->children[parent->children_i-1];
}

Node* name_is_child(Node *node, const char *name) {
    for (size_t i=0; i < node->children_i; i++) {
        if (strcmp(node->children[i].name, name) == 0) return &node->children[i];
    }
    return NULL;
}


/*
int insert_str(Node *parent, char *path) {
    if (!path) return 0;
    char *token, *string, *tofree;
    tofree = string = strdup(path);
    token = strsep(&string, ".");
    if (token) {
        // printf("Inserting node %s to parent %s\n", token, parent->name);
        insert(parent, token);
        Node *node = &parent->children[parent->children_i];
        return insert_str(node, string);
    }
    free(tofree);
}
*/

Node* build_index(const char **paths) {
    Node *root = init_node();
    Node *node, *temp = NULL;
    temp = root;
    size_t i = 0;
    const char *path = paths[i];
    while (path) {
        node = insert(temp, path);
        i++;
        path = paths[i];
        temp = node;
    }
    return root;
}

void insert_paths(Node *node, const char **paths) {
    Node *child;
    while (*paths) {
        child = name_is_child(node, *paths);
        if (child == NULL) {
            child = insert(node, *paths);
        }
/*
        else {
            printf("Name %s already child of %s\n", *paths, node->name);
        }
*/
        node = child;
        paths++;
    }
}

Node* init_node(void) {
    Node *node = malloc(sizeof(Node));
    node->name = NULL;
    node->children_i = 0;
    node->children_size = 1;
    node->children = NULL;
    return node;
}

int is_leaf(Node *node) {
    if (node == NULL) return 0;
    return node->children_i == 0;
}

int is_pattern(const char *pattern) {
    char *_patterns = patterns;
    while (*_patterns) {
        if (strchr(pattern, *(_patterns)++)) return 1;
    }
    return 0;
}
