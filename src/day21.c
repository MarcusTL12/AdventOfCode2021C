#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/hashmap.c/hashmap.h"

const size_t p1_start = 5, p2_start = 8;

void d21p1() {
    size_t pos[] = {p1_start, p2_start}, score[] = {0, 0}, inds[] = {1, 0},
           i = 0, amt_rolls = 0, die = 1;

    while (score[0] < 1000 && score[1] < 1000) {
        amt_rolls += 3;
        size_t n = 0;
        for (size_t j = 0; j < 3; j++) {
            n += die;
            die = die % 100 + 1;
        }
        pos[i] = (pos[i] + n - 1) % 10 + 1;
        score[i] += pos[i];
        i = inds[i];
    }

    size_t ans = (score[0] < score[1] ? score[0] : score[1]) * amt_rolls;

    printf("%zu\n", ans);
}

typedef struct {
    size_t a, b;
} point_t;

typedef struct {
    point_t pos, score;
    bool turn;
    point_t universes;
} key_t;

static uint64_t key_hash(const void *k, uint64_t s0, uint64_t s1) {
    return hashmap_sip(k, sizeof(point_t) * 2 + sizeof(bool), s0, s1);
}

static int key_cmp(const void *a, const void *b, void *udata) {
    return memcmp(a, b, sizeof(point_t) * 2 + sizeof(bool));
}

static point_t rec(key_t k, struct hashmap *memo) {
    key_t *memo_res = hashmap_get(memo, &k);
    if (memo_res) {
        return memo_res->universes;
    } else if (k.score.a >= 21) {
        return (point_t){.a = 1, .b = 0};
    } else if (k.score.b >= 21) {
        return (point_t){.a = 0, .b = 1};
    } else {
        point_t acc = {0, 0};

        for (size_t d1 = 1; d1 <= 3; d1++) {
            for (size_t d2 = 1; d2 <= 3; d2++) {
                for (size_t d3 = 1; d3 <= 3; d3++) {
                    size_t n = d1 + d2 + d3;
                    key_t nk;
                    nk.pos.a = k.turn ? k.pos.a : (k.pos.a + n - 1) % 10 + 1;
                    nk.pos.b = !k.turn ? k.pos.b : (k.pos.b + n - 1) % 10 + 1;
                    nk.score.a = k.score.a + (k.turn ? 0 : nk.pos.a);
                    nk.score.b = k.score.b + (!k.turn ? 0 : nk.pos.b);
                    nk.turn = !k.turn;
                    nk.universes = rec(nk, memo);
                    acc.a += nk.universes.a;
                    acc.b += nk.universes.b;
                }
            }
        }

        k.universes = acc;
        hashmap_set(memo, &k);

        return acc;
    }
}

void d21p2() {
    struct hashmap *memo =
        hashmap_new(sizeof(key_t), 0, 0, 0, key_hash, key_cmp, NULL, NULL);

    point_t p = rec(
        (key_t){(point_t){p1_start, p2_start}, (point_t){0, 0}, false}, memo);

    size_t ans = p.a > p.b ? p.a : p.b;

    printf("%zu\n", ans);
}
