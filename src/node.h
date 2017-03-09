#ifndef NODE_H
#define NODE_H

#define NullNode(...) { .name = NULL, .children_i = 0, .children_size = 1, .children = NULL, ## __VA_ARGS__ }

struct Node {
    size_t children_i;
    size_t children_size;
    char *name;
    struct Node *children;
};

void print_index(struct Node *node);
struct Node* clear(struct Node *node);
struct Node* insert(struct Node *parent, char *path);
struct Node* name_is_child(struct Node *node, char *name);
int insert_str(struct Node *parent, char *path);
struct Node* build_index(char *paths[]);
void insert_paths(struct Node *node, char *paths[]);
struct Node* init_node();
int is_leaf(struct Node *parent);
char** match_entries(char **keys, char *query);

#endif /* NODE_H */
