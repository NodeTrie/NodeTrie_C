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

#ifndef NODE_H
#define NODE_H

// Forward declaration to be able to use Node type inside struct
typedef struct _Node Node;

struct _Node {
    size_t children_i;
    size_t children_size;
    char *name;
    Node *children;
};

void print_index(Node *node);
Node* clear(Node *node);
Node* insert(Node *parent, const char *path);
Node* name_is_child(Node *node, const char *name);
// int insert_str(Node *parent, const char *path);
// Node* build_index(const char **paths);
void insert_paths(Node *node, const char **paths);
Node* init_node(void);
int is_leaf(Node *node);
int is_pattern(const char *pattern);
// char** match_entries(const char **keys, const char *query);
// static char patterns[4];

#endif /* NODE_H */
