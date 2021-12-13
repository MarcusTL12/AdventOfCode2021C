#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "../AoC_C_utils/src/bitfield.h"
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
        while (*c && !isalpha(*c)) c++;
        vec_push(folds, &cnn);
    }

    free(inp);
}

void d13p1() {
    vec_t coords, folds;
    parse_input("input/day13/input", &coords, &folds);

    size_t *cnn = vec_get(&folds, 0);
    for (size_t i = 0; i < coords.len; i++) {
        size_t *coord = vec_get(&coords, i);
        if (coord[cnn[0]] > cnn[1]) {
            coord[cnn[0]] = 2 * cnn[1] - coord[cnn[0]];
        }
    }

    size_t maxx = 0, maxy = 0;

    for (size_t i = 0; i < coords.len; i++) {
        size_t *coord = vec_get(&coords, i);
        maxx = coord[0] > maxx ? coord[0] : maxx;
        maxy = coord[0] > maxy ? coord[0] : maxy;
    }

    size_t width = maxx + 1, height = maxy + 1;

    size_t bitints = bitfield_ints(width * height);
    uint64_t *grid = bitfield_create(width * height);

    for (size_t i = 0; i < coords.len; i++) {
        size_t *coord = vec_get(&coords, i);
        bitfield_set(grid, coord[0] + coord[1] * width, true);
    }

    size_t ans = bitfield_count(grid, bitints);

    printf("%zu\n", ans);

    vec_free(&coords);
    vec_free(&folds);
}

void d13p2() {
    vec_t coords, folds;
    parse_input("input/day13/input", &coords, &folds);

    for (size_t i = 0; i < folds.len; i++) {
        size_t *cnn = vec_get(&folds, i);
        for (size_t j = 0; j < coords.len; j++) {
            size_t *coord = vec_get(&coords, j);
            if (coord[cnn[0]] > cnn[1]) {
                coord[cnn[0]] = 2 * cnn[1] - coord[cnn[0]];
            }
        }
    }

    size_t maxx = 0, maxy = 0;

    for (size_t i = 0; i < coords.len; i++) {
        size_t *coord = vec_get(&coords, i);
        maxx = coord[0] > maxx ? coord[0] : maxx;
        maxy = coord[1] > maxy ? coord[1] : maxy;
    }

    size_t width = maxx + 1, height = maxy + 1;

    size_t bitints = bitfield_ints(width * height);
    uint64_t *grid = bitfield_create(width * height);

    for (size_t i = 0; i < coords.len; i++) {
        size_t *coord = vec_get(&coords, i);
        bitfield_set(grid, coord[0] + coord[1] * width, true);
    }

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            printf("%s", bitfield_get(grid, x + y * width) ? "██" : "  ");
        }
        printf("\n");
    }

    vec_free(&coords);
    vec_free(&folds);
}
