#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/src/bitfield.h"
#include "../AoC_C_utils/src/file_util.h"

static uint64_t *load_inputs(char *filename, size_t *bits, size_t *lines,
                             size_t *bitints) {
    char *inp = file_read_full(filename);

    *bits = 0;
    *lines = 0;

    while (isdigit(inp[*bits])) (*bits)++;
    while (isdigit(inp[*lines * (*bits + 1)])) (*lines)++;

    *bitints = bitfield_ints(*lines);
    uint64_t *allbits = malloc(*bits * *bitints * sizeof(uint64_t));
    memset(allbits, 0, *bits * *bitints * sizeof(uint64_t));

    for (size_t line = 0; line < *lines; line++) {
        for (size_t bit = 0; bit < *bits; bit++) {
            bool val = inp[bit + line * (*bits + 1)] == '1';
            bitfield_set(allbits + bit * *bitints, line, val);
        }
    }

    free(inp);
    return allbits;
}

void d3p1() {
    size_t bits, lines, bitints;
    uint64_t *inp = load_inputs("input/day3/input", &bits, &lines, &bitints);

    uint64_t g = 0;

    for (size_t bit = 0; bit < bits; bit++) {
        bool val = 2 * bitfield_count(inp + bit * bitints, bitints) > lines;
        g = (g << 1) | val;
    }

    uint64_t mask = ~0;
    mask >>= (64 - bits);

    uint64_t ans = g * (~g & mask);

    printf("%lu\n", ans);

    free(inp);
}

void d3p2() {}
