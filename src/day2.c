#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../AoC_C_utils/src/file_util.h"

void d2p1() {
    char *inp = file_read_full("input/day2/input");

    int64_t depth = 0, x = 0;

    for (char *c = inp; *c;) {
        char d = *c;
        while (!isdigit(*c)) c++;
        int64_t n = atoll(c);

        switch (d) {
            case 'f':
                x += n;
                break;
            case 'd':
                depth += n;
                break;
            case 'u':
                depth -= n;
                break;
        }

        while (*c && !isalpha(*c)) c++;
    }

    printf("%ld\n", depth * x);

    free(inp);
}

void d2p2() {
    char *inp = file_read_full("input/day2/input");

    int64_t depth = 0, x = 0, aim = 0;

    for (char *c = inp; *c;) {
        char d = *c;
        while (!isdigit(*c)) c++;
        int64_t n = atoll(c);

        switch (d) {
            case 'f':
                x += n;
                depth += aim * n;
                break;
            case 'd':
                aim += n;
                break;
            case 'u':
                aim -= n;
                break;
        }

        while (*c && !isalpha(*c)) c++;
    }

    printf("%ld\n", depth * x);

    free(inp);
}
