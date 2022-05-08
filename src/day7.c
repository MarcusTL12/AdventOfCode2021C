#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "aoc_util/array_util.h"
#include "aoc_util/file_util.h"

static int64_t *parse_input(char *filename, size_t *amt_nums_) {
    char *inp = file_read_full(filename);
    size_t amt_nums = 1;
    for (char *c = inp; *c; c++) amt_nums += *c == ',';

    int64_t *nums = malloc(sizeof(int64_t) * amt_nums);

    char *c = inp;
    for (size_t i = 0; i < amt_nums; i++) {
        nums[i] = atoll(c);
        while (isdigit(*c)) c++;
        while (*c && !isdigit(*c)) c++;
    }

    *amt_nums_ = amt_nums;
    free(inp);
    return nums;
}

static int64_t cost1(int64_t *nums, size_t amt_nums, int64_t x) {
    int64_t cost = 0;
    for (size_t i = 0; i < amt_nums; i++) {
        cost += llabs(nums[i] - x);
    }
    return cost;
}

static int64_t dir1(int64_t *nums, size_t amt_nums, int64_t x) {
    return cost1(nums, amt_nums, x + 1) - cost1(nums, amt_nums, x);
}

void d7p1() {
    size_t amt_nums;
    int64_t *nums = parse_input("input/day7/input", &amt_nums);

    minmax_t mm = minmax(nums, amt_nums);

    int64_t l = mm.min, h = mm.max;

    while (h - l > 1) {
        int64_t m = (l + h) / 2;

        int64_t d = dir1(nums, amt_nums, m);

        if (d > 0) {
            h = m;
        } else if (d < 0) {
            l = m;
        } else {
            break;
        }
    }

    int64_t ans = cost1(nums, amt_nums, h);

    printf("%ld\n", ans);

    free(nums);
}

static int64_t trignum(int64_t n) {
    return (n * (n + 1)) / 2;
}

static int64_t cost2(int64_t *nums, size_t amt_nums, int64_t x) {
    int64_t cost = 0;
    for (size_t i = 0; i < amt_nums; i++) {
        cost += trignum(llabs(nums[i] - x));
    }
    return cost;
}

static int64_t dir2(int64_t *nums, size_t amt_nums, int64_t x) {
    return cost2(nums, amt_nums, x + 1) - cost2(nums, amt_nums, x);
}

void d7p2() {
    size_t amt_nums;
    int64_t *nums = parse_input("input/day7/input", &amt_nums);

    minmax_t mm = minmax(nums, amt_nums);

    int64_t l = mm.min, h = mm.max;

    while (h - l > 1) {
        int64_t m = (l + h) / 2;

        int64_t d = dir2(nums, amt_nums, m);

        if (d > 0) {
            h = m;
        } else if (d < 0) {
            l = m;
        } else {
            break;
        }
    }

    int64_t ans = cost2(nums, amt_nums, h);

    printf("%ld\n", ans);

    free(nums);
}
