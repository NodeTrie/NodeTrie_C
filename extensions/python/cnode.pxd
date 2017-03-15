cdef extern from "node.h":
    ctypedef struct Node:
        size_t children_i
        size_t children_size
        unsigned char *name
        Node *children
    Node* clear(Node *node) nogil
    Node* insert(Node *parent, unsigned char *path) nogil
    void insert_paths(Node *node, unsigned char **paths) nogil
    Node* init_node() nogil
    bint is_leaf(Node *node) nogil
