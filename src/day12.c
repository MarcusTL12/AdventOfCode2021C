#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/src/bitfield.h"
#include "../AoC_C_utils/src/file_util.h"
#include "../AoC_C_utils/hashmap.c/hashmap.h"

typedef struct {
    char *s;
    size_t ind;
} node_t;

static uint64_t node_hash(const void *node_, uint64_t s0, uint64_t s1) {
    const node_t *node = node_;
    size_t len = 0;
    while (isalpha(node->s[len])) len++;
    return hashmap_sip(node->s, len, s0, s1);
}

static int node_cmp(const void *a_, const void *b_, void *udata) {
    const node_t *a = a_, *b = b_;
    size_t len_a = 0, len_b = 0;
    while (isalpha(a->s[len_a])) len_a++;
    while (isalpha(b->s[len_b])) len_b++;
    if (len_a == len_b) {
        return memcmp(a->s, b->s, len_a);
    } else {
        return len_a - len_b;
    }
}

static uint64_t *parse_input(char *filename, size_t *amt_nodes_) {
    char *input = file_read_full(filename);
    struct hashmap *node_translation =
        hashmap_new(sizeof(node_t), 0, 0, 0, node_hash, node_cmp, NULL, NULL);

    hashmap_set(node_translation, &(node_t){.s = "start", .ind = 0});
    hashmap_set(node_translation, &(node_t){.s = "end", .ind = 1});

    size_t amt_nodes = 2;

    for (char *c = input; *c;) {
        node_t node = {.s = c, .ind = amt_nodes};
        if (!hashmap_get(node_translation, &node)) {
            hashmap_set(node_translation, &node);
            amt_nodes++;
        }
        while (isalpha(*c)) c++;
        while (*c && !isalpha(*c)) c++;
    }

    uint64_t *graph = bitfield_create(amt_nodes * amt_nodes);

    for (char *c = input; *c;) {
        size_t a =
            ((node_t *)(hashmap_get(node_translation, &(node_t){.s = c})))->ind;

        bool is_small = true;

        while (isalpha(*c)) {
            is_small &= (bool)islower(*c);
            c++;
        }
        while (*c && !isalpha(*c)) c++;

        bitfield_set(graph, a * (amt_nodes + 1), is_small);

        size_t b =
            ((node_t *)(hashmap_get(node_translation, &(node_t){.s = c})))->ind;

        is_small = true;

        while (isalpha(*c)) {
            is_small &= (bool)islower(*c);
            c++;
        }
        while (*c && !isalpha(*c)) c++;

        bitfield_set(graph, b * (amt_nodes + 1), is_small);

        bitfield_set(graph, a * amt_nodes + b, true);
        bitfield_set(graph, b * amt_nodes + a, true);
    }

    bitfield_set(graph, 0, false);
    bitfield_set(graph, amt_nodes + 1, false);

    hashmap_free(node_translation);
    free(input);

    *amt_nodes_ = amt_nodes;
    return graph;
}

static size_t remaining_paths_from1(uint64_t *graph, size_t amt_nodes,
                                    size_t curpos, uint64_t remaining_nodes) {
    size_t amt = 0;

    for (size_t node = 0; node < amt_nodes; node++) {
        if (bitfield_get(graph, curpos * amt_nodes + node)) {
            if (node == 1) {
                amt++;
            } else if (bitfield_get(&remaining_nodes, node)) {
                if (bitfield_get(graph, node * (amt_nodes + 1))) {
                    bitfield_set(&remaining_nodes, node, false);
                }
                amt += remaining_paths_from1(graph, amt_nodes, node,
                                             remaining_nodes);
                bitfield_set(&remaining_nodes, node, true);
            }
        }
    }

    return amt;
}

void d12p1() {
    size_t amt_nodes;
    uint64_t *graph = parse_input("input/day12/input", &amt_nodes);

    uint64_t remaining = 0;
    remaining = (~remaining) << 1;

    size_t ans = remaining_paths_from1(graph, amt_nodes, 0, remaining);

    printf("%zu\n", ans);

    free(graph);
}

static size_t remaining_paths_from2(uint64_t *graph, size_t amt_nodes,
                                    size_t curpos, uint64_t remaining_nodes,
                                    bool spent_double) {
    size_t amt = 0;

    for (size_t node = 0; node < amt_nodes; node++) {
        if (node != curpos && bitfield_get(graph, curpos * amt_nodes + node)) {
            if (node == 1) {
                amt++;
            } else if (node && (!spent_double ||
                                bitfield_get(&remaining_nodes, node))) {
                bool n_spent_double = spent_double;
                uint64_t n_remaining_nodes = remaining_nodes;
                if (bitfield_get(graph, node * (amt_nodes + 1))) {
                    if (!bitfield_get(&n_remaining_nodes, node)) {
                        n_spent_double = true;
                    }
                    bitfield_set(&n_remaining_nodes, node, false);
                }
                amt += remaining_paths_from2(graph, amt_nodes, node,
                                             n_remaining_nodes, n_spent_double);
            }
        }
    }

    return amt;
}

void d12p2() {
    size_t amt_nodes;
    uint64_t *graph = parse_input("input/day12/input", &amt_nodes);

    uint64_t remaining = 0;
    remaining = (~remaining) << 1;

    size_t ans = remaining_paths_from2(graph, amt_nodes, 0, remaining, false);

    printf("%zu\n", ans);

    free(graph);
}
