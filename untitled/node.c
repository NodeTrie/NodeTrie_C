#include <stdio.h>
#include <stdlib.h>

struct Node {
    char name[127];
    size_t children_n;
    size_t children_i;
    struct Node *parent;
    struct Node *children;
};

int insert(struct Node *parent, struct Node *node) {
    if (parent->children_i > parent->children_n) {
        parent->children_n = parent->children_n * 2;
        if (realloc(parent->children, parent->children_n) != 0) {
            return 1;
        }
    }
    parent->children[parent->children_i] = *node;
    return 0;
}

int main(int argc, const char* argv[]) {
    struct Node children[10];
    size_t n = 5;
    struct Node node1;
    struct Node node2 = {"root", n, 0, &node1, malloc (n * sizeof (struct Node))};
    struct Node node3;
    node2.parent = &node1;
    node1.children = malloc (n * sizeof (struct Node));
    node1.children[0] = node2;
    node1.children[1] = node3;
    // printf("%d", node2.parent->array[0]);
    printf("%s\n", node1.children[0].name);
    printf("%s\n", node2.name);
    return 0;
}
