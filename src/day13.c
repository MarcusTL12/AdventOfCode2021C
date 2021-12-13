#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "../AoC_C_utils/src/file_util.h"
#include "../AoC_C_utils/src/show.h"
#include "../AoC_C_utils/src/vector.h"

static void parse_input(char *filename, vec_t *coords, vec_t *folds) {
    *coords = vec_create(2 * sizeof(size_t));
    *folds = vec_create(2 * sizeof(size_t));

    char *inp = file_read_full(filename);

    char *c = inp;
    while (*c != '\n') {
        size_t xy[2];
        xy[0] = atoll(c);
        while (isdigit(*c)) c++;
        c++;
        xy[1] = atoll(c);
        while (isdigit(*c)) c++;
        c++;
        vec_push(coords, &xy);
    }

    while (*c) {
        while (*c != 'x' && *c != 'y') c++;
        size_t cnn[2];
        cnn[0] = *c - 'x';
        c += 2;
        cnn[1] = atoll(c);
        while (isdigit(*c)) c++;
        while (*c && !isdigit(*c)) c++;
    }

    free(inp);
}

void d13p1() {
    vec_t coords, folds;
    parse_input("input/day13/ex1", &coords, &folds);

    size_t *cnn = vec_get(&folds, 0);
    for (size_t i = 0; i < coords.len; i++) {
        size_t *coord = vec_get(&coords, i);
        if (coord[cnn[0]] > cnn[1]) {
            coord[cnn[0]] = 2 * cnn[1] - coord[cnn[0]];
        }
    }

    // TODO: make bitfield

    vec_free(&coords);
    vec_free(&folds);
}

void d13p2() {}
