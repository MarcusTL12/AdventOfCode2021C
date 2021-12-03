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
        g = (g << 1) |
            (2 * bitfield_count(inp + bit * bitints, bitints) > lines);
    }

    uint64_t mask = ~0;
    mask >>= (64 - bits);

    uint64_t ans = g * (~g & mask);

    printf("%lu\n", ans);

    free(inp);
}

uint64_t single_out(uint64_t *inp, uint64_t *filtered, uint64_t *buffer,
                    size_t bits, size_t lines, size_t bitints, bool inverted) {
    memset(filtered, 0, bitints * sizeof(uint64_t));
    bitfield_not(filtered, lines);

    for (size_t bit = 0; bit < bits && bitfield_count(filtered, bitints) > 1;
         bit++) {
        memcpy(buffer, inp + bit * bitints, bitints * sizeof(uint64_t));

        bitfield_and(buffer, filtered, bitints);
        size_t ones = bitfield_count(buffer, bitints),
               total = bitfield_count(filtered, bitints);

        bool bitval = 2 * ones >= total;

        if (inverted ^ !bitval) {
            bitfield_not(buffer, lines);
        }

        bitfield_and(filtered, buffer, bitints);
    }

    size_t index = bitfield_findfirst_true(filtered, bitints);

    uint64_t n = 0;

    for (size_t bit = 0; bit < bits; bit++) {
        n = (n << 1) | bitfield_get(inp + bit * bitints, index);
    }

    return n;
}

void d3p2() {
    printf("THIS SOLUTION DOES NOT WORK!\n");

    size_t bits, lines, bitints;
    uint64_t *inp = load_inputs("input/day3/input", &bits, &lines, &bitints);
    uint64_t *filtered = bitfield_create(lines),
             *buffer = bitfield_create(lines);

    uint64_t ox =
        single_out(inp, filtered, buffer, bits, lines, bitints, false);
    uint64_t co2 =
        single_out(inp, filtered, buffer, bits, lines, bitints, true);

    printf("%ld * %ld = %ld\n", ox, co2, ox * co2);

    bitfield_free(buffer);
    bitfield_free(filtered);
    free(inp);
}
