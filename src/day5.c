#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/src/bitfield.h"
#include "../AoC_C_utils/src/file_util.h"

const size_t N = 1000;

void d5p1() {
    char *inp = file_read_full("input/day5/input");
    char *grid = malloc(N * N);
    memset(grid, 0, N * N);

    for (char *c = inp; *c;) {
        int coords[4];
        for (size_t i = 0; i < 4; i++) {
            coords[i] = atoi(c);
            while (isdigit(*c)) c++;
            while (*c && !isdigit(*c)) c++;
        }

        int dx = coords[2] - coords[0], dy = coords[3] - coords[1];
        dx = dx ? dx > 0 ? 1 : -1 : 0;
        dy = dy ? dy > 0 ? 1 : -1 : 0;

        if (dx && dy) continue;

        for (int x = coords[0] - dx, y = coords[1] - dy;
             x != coords[2] || y != coords[3];) {
            x += dx;
            y += dy;
            char *p = grid + x + N * y;

            *p = *p ? 2 : 1;
        }
    }

    size_t counter = 0;

    for (size_t i = 0; i < N * N; i++) {
        counter += grid[i] == 2;
    }

    printf("%zu\n", counter);

    free(grid);
    free(inp);
}

void d5p2() {
    char *inp = file_read_full("input/day5/input");
    char *grid = malloc(N * N * 2);
    memset(grid, 0, N * N);

    for (char *c = inp; *c;) {
        int coords[4];
        for (size_t i = 0; i < 4; i++) {
            coords[i] = atoi(c);
            while (isdigit(*c)) c++;
            while (*c && !isdigit(*c)) c++;
        }

        int dx = coords[2] - coords[0], dy = coords[3] - coords[1];
        dx = dx ? dx > 0 ? 1 : -1 : 0;
        dy = dy ? dy > 0 ? 1 : -1 : 0;

        for (int x = coords[0] - dx, y = coords[1] - dy;
             x != coords[2] || y != coords[3];) {
            x += dx;
            y += dy;
            char *p = grid + x + N * y;

            *p = *p ? 2 : 1;
        }
    }

    size_t counter = 0;

    for (size_t i = 0; i < N * N; i++) {
        counter += grid[i] == 2;
    }

    printf("%zu\n", counter);

    free(grid);
    free(inp);
}
