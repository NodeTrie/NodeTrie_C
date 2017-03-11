#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../src/node.h"

START_TEST(test_create_index) {

    Node *root = init_node();
    ck_assert_int_eq(root->children_i, 0);
    ck_assert(root->name == NULL);
    root = clear(root);
    ck_assert(root == NULL);
}
END_TEST

void test_node_children(Node *parent, char **name) {
    while (*name) {
        printf("Checking name %s\n", *name);
        Node *child = name_is_child(parent, *name);
        ck_assert(child != NULL);
        ck_assert_str_eq(child->name, *name);
        parent = child;
        name++;
    }
}

START_TEST(test_create_index_tree) {
    char *paths[] = {"b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "b9", NULL};
    Node *root = init_node();
    insert_paths(root, paths);
    ck_assert_int_eq(root->children_i, 1);
    for (size_t i = 0; i < 1; i++) {
        ck_assert_int_eq(root->children[i].children_i, 1);
    }
    char *new_paths[] = {"b1", "b22", "b3", "b44", "b5", "b66", "b7", "b88", "b9", NULL};
    insert_paths(root, new_paths);
    for (size_t i = 0; i < 1; i++) {
        if (i+1 % 2 == 1) {
            ck_assert_int_eq(root->children[i].children_i, 2);
        }
        else if (i+1 % 2 == 0) {
            ck_assert_int_eq(root->children[i].children_i, 1);
        }
    }
    ck_assert(!is_leaf(root));

    // Check children
    test_node_children(root, &paths[0]);
    test_node_children(root, &new_paths[0]);

    // Clearing
    root = clear(root);
    ck_assert(root == NULL);
}
END_TEST

START_TEST(test_match_entries) {
    char *keys[] = {"b1", "b2", "b3", "b4", NULL};
    char **matches = match_entries(keys, "b*");
    size_t i = 0;
    char *key = keys[i];
    while (key) {
        ck_assert_str_eq(matches[i], key);
        i++;
        key = keys[i];
    }
}
END_TEST

Suite * node_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("node");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_create_index);
    tcase_add_test(tc_core, test_create_index_tree);
    // tcase_add_test(tc_core, test_match_entries);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = node_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
