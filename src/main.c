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
#include "node.h"

int main(int argc, const char *argv[]) {
    char *my_patterns[5] = {"adsfasdf", "?", "[", "{", NULL};
    char **pattern = &my_patterns[0];
    while(*pattern) {
        printf("Pattern %s found: %d\n", *pattern, is_pattern(*pattern));
        pattern++;
    }
    char *paths[4];
    paths[0] = "b1";
    paths[1] = "b2";
    paths[2] = "b3";
    paths[3] = NULL;

    Node *root = init_node();
    printf("Root node %s, index %zu\n", root->name, root->children_i);
    insert_paths(root, paths);
    paths[0] = "b1";
    paths[1] = "b12";
    paths[2] = "b13";
    paths[3] = NULL;
    insert_paths(root, paths);
    paths[0] = "b1";
    paths[1] = "b22";
    paths[2] = "b23";
    paths[3] = NULL;
    insert_paths(root, paths);
    print_index(root);
    printf("Root index before clear %zu\n", root->children_i);
    clear(root);
    if(!root) printf("Index cleared");
    return 0;
}
