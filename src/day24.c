#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "aoc_util/file_util.h"

typedef struct {
    bool a;
    int64_t b, c;
} param_t;

static void get_parameters(char *filename, param_t *params) {
    char *inp = file_read_full(filename);

    char *c = inp;

    for (size_t i = 0; i < 14; i++, params++) {
        c += 37;
        params->a = *c == '2';
        c += params->a + 8;
        params->b = atoll(c);
        while (*c != '\n') c++;
        c += 80;
        params->c = atoll(c);
        while (*c != '\n') c++;
        c += 17;
    }

    free(inp);
}

static int64_t rec(int64_t z, param_t *params, size_t i, int64_t n,
                   int64_t *ds) {
    if (i < 14) {
        bool a = params[i].a;
        int64_t b = params[i].b, c = params[i].c;
        if (a) {
            int64_t d = z % 26 + b;
            if (1 <= d && d <= 9) {
                return rec(z / 26, params, i + 1, 10 * n + d, ds);
            } else {
                return -1;
            }
        } else {
            for (size_t j = 0; j < 9; j++) {
                int64_t d = ds[j];
                int64_t res =
                    rec(26 * z + c + d, params, i + 1, 10 * n + d, ds);
                if (res != -1) {
                    return res;
                }
            }
            return -1;
        }
    } else if (z == 0) {
        return n;
    } else {
        return -1;
    }
}

void d24p1() {
    param_t params[14];
    get_parameters("input/day24/input", params);

    int64_t ds[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    int64_t ans = rec(0, params, 0, 0, ds);

    printf("%ld\n", ans);
}

void d24p2() {
    param_t params[14];
    get_parameters("input/day24/input", params);

    int64_t ds[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    int64_t ans = rec(0, params, 0, 0, ds);

    printf("%ld\n", ans);
}
