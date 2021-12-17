#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../AoC_C_utils/src/file_util.h"

typedef struct {
    int64_t minx, maxx, miny, maxy;
} box_t;

static box_t parse_input(char *filename) {
    char *inp = file_read_full(filename);

    box_t ret;

    char *c = inp;
    while (!isdigit(*c) && *c != '-') c++;
    ret.minx = atoll(c);
    while (isdigit(*c) || *c == '-') c++;
    while (!isdigit(*c) && *c != '-') c++;
    ret.maxx = atoll(c);
    while (isdigit(*c) || *c == '-') c++;
    while (!isdigit(*c) && *c != '-') c++;
    ret.miny = atoll(c);
    while (isdigit(*c) || *c == '-') c++;
    while (!isdigit(*c) && *c != '-') c++;
    ret.maxy = atoll(c);

    free(inp);

    return ret;
}

void d17p1() {
    box_t inp = parse_input("input/day17/input");

    int64_t max_max_y = 0;

    for (int64_t vx0 = 1; vx0 <= inp.maxx; vx0++) {
        for (int64_t vy0 = 1; vy0 <= 200; vy0++) {
            int64_t vx = vx0, vy = vy0, x = 0, y = 0, max_y = 0;
            bool hit = false;
            while (x <= inp.maxx && y >= inp.miny) {
                x += vx, y += vy;
                vx -= vx ? vx > 0 ? 1 : -1 : 0, vy -= 1;
                max_y = y > max_y ? y : max_y;
                if (inp.minx <= x && x <= inp.maxx && inp.miny <= y &&
                    y <= inp.maxy) {
                    hit = true;
                    break;
                }
            }
            if (hit) {
                max_max_y = max_y > max_max_y ? max_y : max_max_y;
            }
        }
    }

    printf("%ld\n", max_max_y);
}

void d17p2() {
    box_t inp = parse_input("input/day17/input");

    size_t amt_hit = 0;

    for (int64_t vx0 = 1; vx0 <= inp.maxx; vx0++) {
        for (int64_t vy0 = inp.miny; vy0 <= 200; vy0++) {
            int64_t vx = vx0, vy = vy0, x = 0, y = 0;
            while (x <= inp.maxx && y >= inp.miny) {
                x += vx, y += vy;
                vx -= vx ? vx > 0 ? 1 : -1 : 0, vy -= 1;
                if (inp.minx <= x && x <= inp.maxx && inp.miny <= y &&
                    y <= inp.maxy) {
                    amt_hit++;
                    break;
                }
            }
        }
    }

    printf("%zu\n", amt_hit);
}
