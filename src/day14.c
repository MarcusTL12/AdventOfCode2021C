#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/src/file_util.h"

static uint8_t parse_input(char *filename, size_t *init, uint8_t *insertions) {
    char *inp = file_read_full(filename);

    uint8_t last;

    char *c = inp;

    for (;; c++) {
        if (c[1] == '\n') {
            last = *c - 'A';
            break;
        }
        size_t a = c[0] - 'A', b = c[1] - 'A';
        init[a * 26 + b]++;
    }

    c += 3;

    for (; *c; c += 8) {
        size_t i = c[0] - 'A', j = c[1] - 'A';
        insertions[i * 26 + j] = c[6] - 'A';
    }

    free(inp);

    return last;
}

static void do_step(uint8_t *insertions, size_t *counts, size_t *new_counts) {
    memset(new_counts, 0, 26 * 26 * sizeof(size_t));

    for (size_t i = 0; i < 26; i++) {
        for (size_t j = 0; j < 26; j++) {
            uint8_t ins = insertions[i * 26 + j];
            size_t c = counts[i * 26 + j];
            if (ins) {
                new_counts[i * 26 + ins] += c;
                new_counts[ins * 26 + j] += c;
            } else {
                new_counts[i * 26 + j] = c;
            }
        }
    }
}

void d14p1() {
    size_t counts[26 * 26] = {0}, counts_buf[26 * 26] = {0};
    uint8_t insertions[26 * 26] = {0};
    uint8_t last = parse_input("input/day14/input", counts, insertions);

    size_t *counts_a = counts, *counts_b = counts_buf;

    for (size_t i = 0; i < 10; i++) {
        do_step(insertions, counts_a, counts_b);
        size_t *tmp = counts_a;
        counts_a = counts_b;
        counts_b = tmp;
    }

    size_t char_counters[26] = {0};
    char_counters[last] = 1;

    for (size_t i = 0; i < 26; i++) {
        for (size_t j = 0; j < 26; j++) {
            char_counters[i] += counts_a[i * 26 + j];
        }
    }

    size_t min = SIZE_MAX, max = 0;

    for (size_t i = 0; i < 26; i++) {
        size_t c = char_counters[i];
        if (c) {
            min = c < min ? c : min;
            max = c > max ? c : max;
        }
    }

    size_t ans = max - min;

    printf("%zu\n", ans);
}

void d14p2() {
    size_t counts[26 * 26] = {0}, counts_buf[26 * 26] = {0};
    uint8_t insertions[26 * 26] = {0};
    uint8_t last = parse_input("input/day14/input", counts, insertions);

    size_t *counts_a = counts, *counts_b = counts_buf;

    for (size_t i = 0; i < 40; i++) {
        do_step(insertions, counts_a, counts_b);
        size_t *tmp = counts_a;
        counts_a = counts_b;
        counts_b = tmp;
    }

    size_t char_counters[26] = {0};
    char_counters[last] = 1;

    for (size_t i = 0; i < 26; i++) {
        for (size_t j = 0; j < 26; j++) {
            char_counters[i] += counts_a[i * 26 + j];
        }
    }

    size_t min = SIZE_MAX, max = 0;

    for (size_t i = 0; i < 26; i++) {
        size_t c = char_counters[i];
        if (c) {
            min = c < min ? c : min;
            max = c > max ? c : max;
        }
    }

    size_t ans = max - min;

    printf("%zu\n", ans);
}
