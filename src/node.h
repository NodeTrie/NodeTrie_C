#ifndef NODE_H
#define NODE_H

#define NullNode(...) { .name = NULL, .children_i = 0, .children_size = 1, .children = NULL, ## __VA_ARGS__ }

// Forward declaration to be able to use Node type inside struct
typedef struct _Node Node;

struct _Node {
    size_t children_i;
    size_t children_size;
    unsigned char *name;
    Node *children;
};

void print_index(Node *node);
Node* clear(Node *node);
Node* insert(Node *parent, unsigned char *path);
Node* name_is_child(Node *node, unsigned char *name);
// int insert_str(Node *parent, static unsigned char *path);
// Node* build_index(unsigned char **paths);
void insert_paths(Node *node, unsigned char **paths);
Node* init_node(void);
int is_leaf(Node *node);
// unsigned char** match_entries(unsigned char **keys, unsigned char *query);

#endif /* NODE_H */
