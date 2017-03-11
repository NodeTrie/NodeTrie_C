#ifndef NODE_H
#define NODE_H

#define NullNode(...) { .name = NULL, .children_i = 0, .children_size = 1, .children = NULL, ## __VA_ARGS__ }

typedef struct _Node Node;

typedef struct _Node {
    size_t children_i;
    size_t children_size;
    char *name;
    Node *children;
} Node;

void print_index(Node *node);
Node* clear(Node *node);
Node* insert(Node *parent, char *path);
Node* name_is_child(Node *node, char *name);
int insert_str(Node *parent, char *path);
Node* build_index(char **paths);
void insert_paths(Node *node, char **paths);
Node* init_node();
int is_leaf(Node *parent);
char** match_entries(char **keys, char *query);

#endif /* NODE_H */
