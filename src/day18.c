#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "aoc_util/file_util.h"
#include "aoc_util/vector.h"

// type = 0: Leaf. Value saved as (size_t)left;
// type = 1: Branch. left and right point to children nodes.
typedef struct node {
    char is_branch;
    struct node *left, *right;
} node_t;

static size_t *get_val(node_t *node) { return (size_t *)(&node->left); }

static node_t *parse_node(char **c) {
    node_t *node = malloc(sizeof(node_t));
    if (**c == '[') {
        node->is_branch = 1;
        ++*c;
        node->left = parse_node(c);
        while (**c == ']' || **c == ',' || **c == ' ') ++*c;
        node->right = parse_node(c);
        ++*c;
    } else {
        node->is_branch = 0;
        size_t n = 0;
        while (isdigit(**c)) {
            n = 10 * n + (**c - '0');
            ++*c;
        }
        *get_val(node) = n;
        ++*c;
    }
    return node;
}

static void print_tree(node_t *node) {
    if (node->is_branch) {
        printf("[");
        print_tree(node->left);
        printf(", ");
        print_tree(node->right);
        printf("]");
    } else {
        printf("%zu", *get_val(node));
    }
}

static void free_tree(node_t *node) {
    if (node->is_branch) {
        free_tree(node->left);
        free_tree(node->right);
    }
    free(node);
}

static node_t *node_add(node_t *a, node_t *b) {
    node_t *node = malloc(sizeof(node_t));

    node->is_branch = 1;
    node->left = a;
    node->right = b;

    return node;
}

static void add_first_right(node_t *node, size_t val) {
    if (node->is_branch) {
        add_first_right(node->left, val);
    } else {
        *get_val(node) += val;
    }
}

static void add_first_left(node_t *node, size_t val) {
    if (node->is_branch) {
        add_first_left(node->right, val);
    } else {
        *get_val(node) += val;
    }
}

typedef struct {
    bool is_some, has_left, has_right;
    size_t left, right;
} expl_res_t;

static expl_res_t node_explode(node_t *node, size_t depth) {
    if (node->is_branch) {
        if (!node->left->is_branch && !node->right->is_branch && depth >= 4) {
            size_t l = *get_val(node->left), r = *get_val(node->right);
            free(node->left);
            free(node->right);
            node->is_branch = 0;
            *get_val(node) = 0;
            return (expl_res_t){.is_some = true,
                                .has_left = true,
                                .has_right = true,
                                .left = l,
                                .right = r};
        } else {
            expl_res_t explode = node_explode(node->left, depth + 1);
            if (explode.is_some) {
                if (explode.has_right) {
                    add_first_right(node->right, explode.right);
                }
                explode.has_right = false;
                return explode;
            }
            explode = node_explode(node->right, depth + 1);
            if (explode.is_some) {
                if (explode.has_left) {
                    add_first_left(node->left, explode.left);
                }
                explode.has_left = false;
            }
            return explode;
        }
    } else {
        return (expl_res_t){.is_some = false};
    }
}

static bool node_split(node_t *node) {
    if (node->is_branch) {
        if (node_split(node->left)) {
            return true;
        } else {
            return node_split(node->right);
        }
    } else {
        size_t x = *get_val(node);
        if (x >= 10) {
            size_t a = x / 2;
            size_t b = a + x % 2;
            node->is_branch = 1;
            node->left = malloc(sizeof(node_t));
            node->left->is_branch = 0;
            *get_val(node->left) = a;
            node->right = malloc(sizeof(node_t));
            node->right->is_branch = 0;
            *get_val(node->right) = b;
            return true;
        }
    }
    return false;
}

static void node_reduce(node_t *node) {
    do {
        while (node_explode(node, 0).is_some)
            ;
    } while (node_split(node));
}

static size_t node_magnitude(node_t *node) {
    if (node->is_branch) {
        return 3 * node_magnitude(node->left) + 2 * node_magnitude(node->right);
    } else {
        return *get_val(node);
    }
}

void d18p1() {
    char *inp = file_read_full("input/day18/input");
    char *c = inp;

    node_t *acc = parse_node(&c);

    while (*c) {
        node_t *node = parse_node(&c);
        acc = node_add(acc, node);
        node_reduce(acc);
    }

    size_t ans = node_magnitude(acc);

    printf("%zu\n", ans);

    free_tree(acc);
    free(inp);
}

static node_t *node_clone(node_t *node) {
    node_t *new_node = malloc(sizeof(node_t));
    if (node->is_branch) {
        new_node->is_branch = 1;
        new_node->left = node_clone(node->left);
        new_node->right = node_clone(node->right);
    } else {
        new_node->is_branch = 0;
        *get_val(new_node) = *get_val(node);
    }
    return new_node;
}

void d18p2() {
    char *inp = file_read_full("input/day18/input");
    char *c = inp;

    vec_t snails = vec_create(sizeof(node_t *));

    while (*c) {
        node_t *node = parse_node(&c);
        vec_push(&snails, &node);
    }
    free(inp);

    size_t ans = 0;

    for (size_t i = 0; i < snails.len; i++) {
        for (size_t j = 0; j < snails.len; j++) {
            if (i != j) {
                node_t *sum =
                    node_add(node_clone(*(node_t **)vec_get(&snails, i)),
                             node_clone(*(node_t **)vec_get(&snails, j)));
                node_reduce(sum);
                size_t mag = node_magnitude(sum);
                ans = mag > ans ? mag : ans;
                free_tree(sum);
            }
        }
    }

    printf("%zu\n", ans);

    vec_free(&snails);
}
