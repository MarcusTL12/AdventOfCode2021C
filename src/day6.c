#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "aoc_util/file_util.h"

void d6p1() {
    char *inp = file_read_full("input/day6/input");

    uint64_t fish[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (char *c = inp; *c;) {
        size_t i = atoll(c);
        fish[i] += 1;
        while (isdigit(*c)) c++;
        while (*c && !isdigit(*c)) c++;
    }

    for (size_t i = 0; i < 80; i++) {
        uint64_t new_fish = fish[0];
        for (size_t j = 0; j < 8; j++) {
            fish[j] = fish[j + 1];
        }
        fish[6] += new_fish;
        fish[8] = new_fish;
    }

    uint64_t ans = 0;

    for (size_t i = 0; i < 9; i++) {
        ans += fish[i];
    }

    printf("%ld\n", ans);

    free(inp);
}

void d6p2() {
    char *inp = file_read_full("input/day6/input");

    uint64_t fish[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (char *c = inp; *c;) {
        size_t i = atoll(c);
        fish[i] += 1;
        while (isdigit(*c)) c++;
        while (*c && !isdigit(*c)) c++;
    }

    for (size_t i = 0; i < 256; i++) {
        uint64_t new_fish = fish[0];
        for (size_t j = 0; j < 8; j++) {
            fish[j] = fish[j + 1];
        }
        fish[6] += new_fish;
        fish[8] = new_fish;
    }

    uint64_t ans = 0;

    for (size_t i = 0; i < 9; i++) {
        ans += fish[i];
    }

    printf("%ld\n", ans);

    free(inp);
}
