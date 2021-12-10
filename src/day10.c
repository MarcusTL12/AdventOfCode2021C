#include <stdint.h>
#include <stdio.h>

#include "../AoC_C_utils/src/file_util.h"
#include "../AoC_C_utils/src/vector.h"

char close_bracket(char c) {
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

int64_t bracket_score1(char c) {
    switch (c) {
        case '(':
            return 3;
        case '[':
            return 57;
        case '{':
            return 1197;
        case '<':
            return 25137;

        default:
            return 0;
    }
}

void d10p1() {
    char *inp = file_read_full("input/day10/input");
    vec_t stack = vec_create(1);

    free(&stack);
    free(inp);
}

void d10p2() {}
