#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/hashmap.c/hashmap.h"
#include "../AoC_C_utils/src/file_util.h"
#include "../AoC_C_utils/src/priority_queue.h"

typedef struct {
    uint8_t data[4];
} floor_t;

typedef struct {
    uint8_t data[11];
} hallway_t;

static void parse_input(char *filename, floor_t *dest) {
    char *inp = file_read_full(filename);

    for (char *c = inp, *n = (char *)dest; *c; c++) {
        if (isalpha(*c)) {
            *(n++) = *c - 'A' + 1;
        }
    }

    free(inp);
}

static void print_state(hallway_t *hallway, floor_t *floors,
                        size_t amt_floors) {
    printf("#############\n#");
    for (size_t i = 0; i < 11; i++) {
        char c = hallway->data[i];
        printf("%c", c ? 'A' + c - 1 : '.');
    }
    printf("#\n###");
    for (size_t i = 0; i < 4; i++) {
        char c = floors->data[i];
        printf("%c#", c ? 'A' + c - 1 : '.');
    }
    printf("#\n");
    for (size_t i = 1; i < amt_floors; i++) {
        printf("  #");
        for (size_t j = 0; j < 4; j++) {
            char c = floors[i].data[j];
            printf("%c#", c ? 'A' + c - 1 : '.');
        }
        printf("\n");
    }
    printf("  #########  \n");
}

static uint64_t key_hash(const void *k, uint64_t s0, uint64_t s1) {
    return hashmap_sip(k, *(size_t *)k, s0, s1);
}

static int key_cmp(const void *a, const void *b, void *udata) {
    return memcmp(a, b, *(size_t *)a);
}

static size_t pow10(size_t n) {
    size_t acc = 1;
    for (size_t i = 0; i < n; i++) {
        acc *= 10;
    }
    return acc;
}

static size_t room_inds(size_t n) { return (n + 1) * 2; }

static size_t abs_diff(size_t a, size_t b) { return a > b ? a - b : b - a; }

static size_t solve(floor_t *_floors, size_t amt_floors) {
    size_t elsize =
        sizeof(size_t) + sizeof(hallway_t) + amt_floors * sizeof(floor_t);

    void *k = malloc(elsize);

    *(size_t *)k = elsize;
    hallway_t *hallway = k + sizeof(size_t);
    floor_t *floors = k + sizeof(size_t) + sizeof(hallway_t);

    memset(hallway, 0, sizeof(hallway_t));
    for (size_t i = 0; i < amt_floors; i++) {
        floors[i] = _floors[i];
    }

    priqueue_t queue = priqueue_create(elsize, key_hash, key_cmp);
    priqueue_insert(&queue, k, 0);

    struct hashmap *visited =
        hashmap_new(elsize, 0, 0, 0, key_hash, key_cmp, NULL, NULL);

    size_t ans = -1;

    for (int64_t energy; priqueue_pop(&queue, k, &energy);) {
        hashmap_set(visited, k);

        bool done = true;
        for (size_t i = 0; done && i < 11; i++) {
            done &= hallway->data[i] == 0;
        }
        for (size_t i = 0; done && i < amt_floors; i++) {
            done &= floors[i].data[0] == 1 && floors[i].data[1] == 2 &&
                    floors[i].data[2] == 3 && floors[i].data[3] == 4;
        }
        if (done) {
            ans = -energy;
            break;
        }

        for (size_t i = 0; i < 4; i++) {
            size_t depth = 0;
            while (depth < amt_floors && !floors[depth].data[i]) {
                depth++;
            }
            if (depth < amt_floors) {
                bool need_to_move = false;
                for (size_t j = depth; !need_to_move && j < amt_floors; j++) {
                    need_to_move |= floors[j].data[i] != i + 1;
                }
                if (need_to_move) {
                    size_t its[] = {room_inds(i) - 1, 0, room_inds(i) + 1, 10};
                    for (size_t it = 0; it < 2; it++) {
                        for (size_t j = its[2 * it];; j += it ? 1 : -1) {
                            if (hallway->data[j]) {
                                break;
                            } else if (j != 2 && j != 4 && j != 6 && j != 8) {
                                hallway->data[j] = floors[depth].data[i];
                                floors[depth].data[i] = 0;

                                int64_t new_energy =
                                    energy -
                                    (depth + 1 + abs_diff(room_inds(i), j)) *
                                        pow10(hallway->data[j] - 1);

                                if (!hashmap_get(visited, k)) {
                                    priqueue_insert_increase(&queue, k,
                                                             new_energy);
                                }

                                floors[depth].data[i] = hallway->data[j];
                                hallway->data[j] = 0;
                            }

                            if (j == its[2 * it + 1]) break;
                        }
                    }
                }
            }
        }

        for (size_t i = 0; i < 11; i++) {
            if (hallway->data[i]) {
                size_t pod_ind = hallway->data[i] - 1,
                       room_ind = room_inds(pod_ind);
                hallway->data[i] = 0;

                bool free_way = true;
                for (size_t j = i < room_ind ? i : room_ind;
                     j <= (i < room_ind ? room_ind : i) && free_way; j++) {
                    free_way &= hallway->data[j] == 0;
                }

                bool free_space = true;
                for (size_t j = 0; free_space && j < amt_floors; j++) {
                    uint8_t x = floors[j].data[pod_ind];
                    free_space &= x == 0 || x == pod_ind + 1;
                }

                if (free_way && free_space) {
                    size_t depth = amt_floors - 1;
                    while (depth && floors[depth].data[pod_ind]) {
                        depth--;
                    }
                    if (!floors[depth].data[pod_ind]) {
                        int64_t new_energy =
                            energy - (depth + 1 + abs_diff(room_ind, i)) *
                                         pow10(pod_ind);

                        floors[depth].data[pod_ind] = pod_ind + 1;

                        if (!hashmap_get(visited, k)) {
                            priqueue_insert_increase(&queue, k, new_energy);
                        }

                        floors[depth].data[pod_ind] = 0;
                    }
                }

                hallway->data[i] = pod_ind + 1;
            }
        }
    }

    hashmap_free(visited);
    priqueue_free(&queue);
    free(k);

    return ans;
}

void d23p1() {
    floor_t floors[2];
    parse_input("input/day23/input", floors);

    size_t ans = solve(floors, 2);

    printf("%zu\n", ans);
}

void d23p2() {
    floor_t floors[2];
    parse_input("input/day23/input", floors);

    floor_t aug_floors[4] = {floors[0], {4, 3, 2, 1}, {4, 2, 1, 3}, floors[1]};

    size_t ans = solve(aug_floors, 4);

    printf("%zu\n", ans);
}
