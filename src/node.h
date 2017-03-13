#ifndef NODE_H
#define NODE_H

#define NullNode(...) { .name = NULL, .children_i = 0, .children_size = 1, .children = NULL, ## __VA_ARGS__ }

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
Node* insert(Node *parent, char *path);
Node* name_is_child(Node *node, char *name);
int insert_str(Node *parent, char *path);
Node* build_index(char **paths);
void insert_paths(Node *node, char **paths);
Node* init_node(void);
int is_leaf(Node *node);
char** match_entries(char **keys, char *query);

#endif /* NODE_H */
