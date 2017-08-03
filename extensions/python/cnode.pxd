# This file is part of NodeTrie.
# Copyright (C) 2017 Panos Kittenis

# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, version 2.1.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

cdef extern from "node.h" nogil:
    ctypedef struct Node:
        size_t children_i
        size_t children_size
        const char *name
        Node *children
    Node* clear(Node *node)
    Node* insert(Node *parent, const char *path)
    void insert_paths(Node *node, const char **paths)
    Node* init_node()
    bint is_leaf(Node *node)
    bint is_pattern(char *pattern)
