#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/src/file_util.h"
#include "../AoC_C_utils/src/priority_queue.h"

static const int64_t dirs[8] = {1, 0, -1, 0, 0, 1, 0, -1};

static uint64_t point_hash(const void *item, uint64_t s0, uint64_t s1) {
    return hashmap_sip(item, sizeof(size_t) * 2, s0, s1);
}

static int point_cmp(const void *a, const void *b, void *udata) {
    return memcmp(a, b, sizeof(size_t) * 2);
}

void d15p1() {
    char *inp = file_read_full("input/day15/input");
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;
    for (char *c = inp; *c; c++) *c -= '0';

    size_t width = stride - 1, height = len / stride;

    priqueue_t queue =
        priqueue_create(sizeof(size_t) * 2, point_hash, point_cmp);
    struct hashmap *visited = hashmap_new(2 * sizeof(size_t), 0, 0, 0,
                                          point_hash, point_cmp, NULL, NULL);

    size_t point[] = {0, 0};
    priqueue_insert(&queue, point, 0);
    hashmap_set(visited, point);

    int64_t ans = 0;

    for (int64_t l; priqueue_pop(&queue, point, &l);) {
        hashmap_set(visited, point);

        if (point[0] == height - 1 && point[1] == width - 1) {
            ans = -l;
            break;
        }

        for (size_t k = 0; k < 4; k++) {
            size_t i = point[0] + dirs[2 * k], j = point[1] + dirs[2 * k + 1];
            size_t npoint[] = {i, j};
            if (i < height && j < width && !hashmap_get(visited, npoint)) {
                priqueue_insert_increase(&queue, npoint,
                                         l - inp[i * stride + j]);
            }
        }
    }

    printf("%ld\n", ans);

    hashmap_free(visited);
    priqueue_free(&queue);
    free(inp);
}

void d15p2() {
    char *inp = file_read_full("input/day15/input");
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;
    for (char *c = inp; *c; c++) *c -= '0';

    size_t width = stride - 1, height = len / stride;

    char *m = malloc(width * height * 5 * 5);

    for (size_t i = 0; i < 5 * height; i++) {
        for (size_t j = 0; j < 5 * width; j++) {
            lldiv_t idiv = lldiv(i, height), jdiv = lldiv(j, width);
            size_t sub_i = idiv.rem, sub_j = jdiv.rem,
                   adder = idiv.quot + jdiv.quot;

            m[i * width * 5 + j] =
                ((inp[sub_i * stride + sub_j] + adder) - 1) % 9 + 1;
        }
    }

    free(inp);

    inp = m;
    width *= 5;
    height *= 5;
    stride = width;

    priqueue_t queue =
        priqueue_create(sizeof(size_t) * 2, point_hash, point_cmp);
    struct hashmap *visited = hashmap_new(2 * sizeof(size_t), 0, 0, 0,
                                          point_hash, point_cmp, NULL, NULL);

    size_t point[] = {0, 0};
    priqueue_insert(&queue, point, 0);
    hashmap_set(visited, point);

    int64_t ans = 0;

    for (int64_t l; priqueue_pop(&queue, point, &l);) {
        hashmap_set(visited, point);

        if (point[0] == height - 1 && point[1] == width - 1) {
            ans = -l;
            break;
        }

        for (size_t k = 0; k < 4; k++) {
            size_t i = point[0] + dirs[2 * k], j = point[1] + dirs[2 * k + 1];
            size_t npoint[] = {i, j};
            if (i < height && j < width && !hashmap_get(visited, npoint)) {
                priqueue_insert_increase(&queue, npoint,
                                         l - inp[i * stride + j]);
            }
        }
    }

    printf("%ld\n", ans);

    hashmap_free(visited);
    priqueue_free(&queue);
    free(inp);
}
