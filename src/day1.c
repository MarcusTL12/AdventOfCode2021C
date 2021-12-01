#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../AoC_C_utils/src/file_util.h"

void d1p1() {
    char *inp = file_read_full("input/day1/input");

    int prev_num = atoi(inp);

    char *c = inp;

    while (isdigit(*c)) c++;
    while (!isdigit(*c)) c++;

    size_t counter = 0;

    while (*c) {
        int cur_num = atoi(c);

        counter += cur_num > prev_num;
        prev_num = cur_num;

        while (isdigit(*c)) c++;
        while (!isdigit(*c) && *c) c++;
    }

    printf("%zu\n", counter);

    free(inp);
}

void d1p2() {
    char *inp = file_read_full("input/day1/input");

    char *c = inp;

    int prev_sum = atoi(c);

    while (isdigit(*c)) c++;
    while (!isdigit(*c)) c++;

    int prev_prev_num = atoi(c);

    while (isdigit(*c)) c++;
    while (!isdigit(*c)) c++;

    int prev_num = atoi(c);
    prev_sum += prev_prev_num + prev_num;

    while (isdigit(*c)) c++;
    while (!isdigit(*c)) c++;

    size_t counter = 0;

    while (*c) {
        int cur_num = atoi(c);
        int cur_sum = prev_prev_num + prev_num + cur_num;

        counter += cur_sum > prev_sum;

        prev_prev_num = prev_num;
        prev_num = cur_num;
        prev_sum = cur_sum;

        while (isdigit(*c)) c++;
        while (!isdigit(*c) && *c) c++;
    }

    printf("%zu\n", counter);

    free(inp);
}
