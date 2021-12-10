#include <ctype.h>
#include <stdio.h>

#include "../AoC_C_utils/src/file_util.h"

void d8p1() {
    char *inp = file_read_full("input/day8/input");

    size_t total = 0;

    for (char *c = inp; *c;) {
        while (*c != '|') c++;
        c++;
        for (size_t i = 0; i < 4; i++) {
            size_t j = 0;
            while (isalpha(*(++c))) j++;
            switch (j) {
                case 2:
                case 3:
                case 4:
                case 7:
                    total += 1;
                default:
                    break;
            }
        }
        if (*c == '\n') c++;
    }

    printf("%zu\n", total);

    free(inp);
}

void d8p2() {}
