#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../AoC_C_utils/src/file_util.h"
#include "../AoC_C_utils/src/show.h"
#include "../AoC_C_utils/src/vector.h"

static char close_bracket(char c) {
    switch (c) {
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
        case '<':
            return '>';

        default:
            return 0;
    }
}

static int64_t bracket_score1(char c) {
    switch (c) {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;

        default:
            return 0;
    }
}

void d10p1() {
    char *inp = file_read_full("input/day10/input");
    vec_t stack = vec_create(1);

    int64_t total = 0;

    for (char *c = inp; *c;) {
        vec_clear(&stack);
        do {
            if (close_bracket(*c)) {
                vec_push(&stack, c);
            } else {
                char opener;
                vec_pop(&stack, &opener);
                if (*c != close_bracket(opener)) {
                    total += bracket_score1(*c);
                    while (*c && *c != '\n') c++;
                    break;
                }
            }
        } while (*++c && *c != '\n');

        if (*c == '\n') c++;
    }

    printf("%ld\n", total);

    vec_free(&stack);
    free(inp);
}

static int64_t bracket_score2(char c) {
    switch (c) {
        case '(':
            return 1;
        case '[':
            return 2;
        case '{':
            return 3;
        case '<':
            return 4;

        default:
            return 0;
    }
}

static int cmp(const void *a_, const void *b_) {
    int64_t a = *(int64_t *)a_, b = *(int64_t *)b_;
    return a != b ? a > b ? 1 : -1 : 0;
}

void d10p2() {
    char *inp = file_read_full("input/day10/input");
    vec_t stack = vec_create(1);
    vec_t all_points = vec_create(sizeof(int64_t));

    for (char *c = inp; *c;) {
        vec_clear(&stack);
        bool corrupted = false;
        do {
            if (close_bracket(*c)) {
                vec_push(&stack, c);
            } else {
                char opener;
                vec_pop(&stack, &opener);
                if (*c != close_bracket(opener)) {
                    corrupted = true;
                    while (*c && *c != '\n') c++;
                    break;
                }
            }
        } while (*++c && *c != '\n');

        if (*c == '\n') c++;

        if (!corrupted && stack.len) {
            int64_t score = 0;
            while (stack.len) {
                char opener;
                vec_pop(&stack, &opener);
                score = score * 5 + bracket_score2(opener);
            }
            vec_push(&all_points, &score);
        }
    }

    qsort(all_points.data, all_points.len, all_points.el_size, cmp);

    int64_t ans = ((int64_t *)(all_points.data))[all_points.len / 2];

    printf("%ld\n", ans);

    vec_free(&all_points);
    vec_free(&stack);
    free(inp);
}
