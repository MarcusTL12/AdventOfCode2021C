#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/src/file_util.h"

void d9p1() {
    char *inp = file_read_full("input/day9/input");
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;
    for (char *c = inp; *c; c++) *c -= '0';

    size_t width = stride - 1, height = len / stride;

    int64_t dirs[8] = {1, 0, -1, 0, 0, 1, 0, -1};

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

void d9p2() {}
