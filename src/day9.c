#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "aoc_util/file_util.h"

static const int64_t dirs[8] = {1, 0, -1, 0, 0, 1, 0, -1};

void d9p1() {
    char *inp = file_read_full("input/day9/input");
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;
    for (char *c = inp; *c; c++) *c -= '0';

    size_t width = stride - 1, height = len / stride;

    int64_t ans = 0;

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            int64_t curheight = inp[i * stride + j];
            bool ismin = true;
            for (size_t k = 0; k < 4; k++) {
                size_t ni = i + dirs[2 * k], nj = j + dirs[2 * k + 1];
                if (ni < height && nj < width) {
                    ismin &= curheight < inp[ni * stride + nj];
                }
            }
            ans += ismin ? curheight + 1 : 0;
        }
    }

    printf("%ld\n", ans);

    free(inp);
}

static size_t traverse_from(size_t i, size_t j, char *m, size_t width,
                            size_t height, size_t stride) {
    size_t s = 1;

    m[i * stride + j] = 9;

    for (size_t k = 0; k < 4; k++) {
        size_t ni = i + dirs[2 * k], nj = j + dirs[2 * k + 1];
        if (ni < height && nj < width && m[ni * stride + nj] < 9) {
            s += traverse_from(ni, nj, m, width, height, stride);
        }
    }

    return s;
}

void d9p2() {
    char *inp = file_read_full("input/day9/input");
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;
    for (char *c = inp; *c; c++) *c -= '0';

    size_t width = stride - 1, height = len / stride;

    const int64_t dirs[8] = {1, 0, -1, 0, 0, 1, 0, -1};

    size_t sizes[3] = {0, 0, 0};

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            if (inp[i * stride + j] < 9) {
                size_t s = traverse_from(i, j, inp, width, height, stride);
                if (s > sizes[0]) {
                    sizes[0] = s;
                    for (size_t k = 0; k < 2; k++) {
                        bool swapfirst = sizes[k] > sizes[k + 1];
                        size_t a = swapfirst ? sizes[k + 1] : sizes[k],
                               b = swapfirst ? sizes[k] : sizes[k + 1];
                        sizes[k] = a;
                        sizes[k + 1] = b;
                    }
                }
            }
        }
    }

    size_t ans = sizes[0] * sizes[1] * sizes[2];

    printf("%zu\n", ans);

    free(inp);
}
