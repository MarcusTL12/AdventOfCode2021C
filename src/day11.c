#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "aoc_util/file_util.h"

static const int64_t dirs[16] = {
    0, 1, 1, 1, 1, 0, 1, -1, 0, -1, -1, -1, -1, 0, -1, 1,
};

void d11p1() {
    char *inp = file_read_full("input/day11/input");
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;
    for (char *c = inp; *c; c++) *c -= '0';

    size_t width = stride - 1, height = len / stride;

    size_t total = 0;

    for (size_t itr = 0; itr < 100; itr++) {
        for (size_t i = 0; i < len; i++) inp[i]++;

        bool didflash;

        do {
            didflash = false;
            for (size_t i = 0; i < height; i++) {
                for (size_t j = 0; j < width; j++) {
                    if (inp[i * stride + j] > 9) {
                        inp[i * stride + j] = 0;
                        didflash = true;
                        total++;
                        for (size_t k = 0; k < 8; k++) {
                            int64_t di = dirs[2 * k];
                            int64_t dj = dirs[2 * k + 1];
                            size_t ni = i + di, nj = j + dj;
                            if (ni < height && nj < width &&
                                inp[ni * stride + nj]) {
                                inp[ni * stride + nj]++;
                            }
                        }
                    }
                }
            }
        } while (didflash);
    }

    printf("%zu\n", total);

    free(inp);
}

void d11p2() {
    char *inp = file_read_full("input/day11/input");
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;
    for (char *c = inp; *c; c++) *c -= '0';

    size_t width = stride - 1, height = len / stride;

    size_t steps = 0;

    while (true) {
        steps++;
        for (size_t i = 0; i < len; i++) inp[i]++;

        bool didflash;

        do {
            didflash = false;
            for (size_t i = 0; i < height; i++) {
                for (size_t j = 0; j < width; j++) {
                    if (inp[i * stride + j] > 9) {
                        inp[i * stride + j] = 0;
                        didflash = true;
                        for (size_t k = 0; k < 8; k++) {
                            int64_t di = dirs[2 * k];
                            int64_t dj = dirs[2 * k + 1];
                            size_t ni = i + di, nj = j + dj;
                            if (ni < height && nj < width &&
                                inp[ni * stride + nj]) {
                                inp[ni * stride + nj]++;
                            }
                        }
                    }
                }
            }
        } while (didflash);

        bool allflash = false;
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                allflash |= inp[i * stride + j];
            }
        }
        if (!allflash) {
            break;
        }
    }

    printf("%zu\n", steps);

    free(inp);
}
