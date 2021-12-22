#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "../AoC_C_utils/hashmap.c/hashmap.h"
#include "../AoC_C_utils/src/file_util.h"

typedef struct {
    int64_t x, y, z;
} point_t;

typedef struct {
    point_t *points;
    size_t len;
} scanner_t;

static void parse_input(char *filename, scanner_t **scanners_,
                        point_t **points_, size_t *amt_scanners_) {
    char *inp = file_read_full(filename);

    size_t amt_scanners = 0, amt_pts = 0;

    for (char *c = inp; *c;) {
        amt_scanners += 1;
        while (*c != '\n') c++;
        c++;
        while (*c && *c != '\n') {
            amt_pts++;
            while (*c && *c != '\n') c++;
            c++;
        }
        if (*c) c++;
    }

    *amt_scanners_ = amt_scanners;

    scanner_t *scanners = malloc(sizeof(scanner_t) * amt_scanners);
    point_t *points = malloc(sizeof(point_t) * amt_pts);

    size_t scanner_ind = 0, point_ind = 0;
    for (char *c = inp; *c; scanner_ind++) {
        while (*c != '\n') c++;
        c++;
        scanners[scanner_ind].points = points + point_ind;
        size_t amt_pts_in_scanner = 0;
        while (*c && *c != '\n') {
            point_t p;
            p.x = atoll(c);
            while (*c == '-' || isdigit(*c)) c++;
            c++;
            p.y = atoll(c);
            while (*c == '-' || isdigit(*c)) c++;
            c++;
            p.z = atoll(c);
            while (*c == '-' || isdigit(*c)) c++;
            c++;
            amt_pts_in_scanner++;
            points[point_ind++] = p;
        }
        scanners[scanner_ind].len = amt_pts_in_scanner;
        if (*c) c++;
    }

    free(inp);

    *scanners_ = scanners;
    *points_ = points;
}

static point_t rotate(point_t p, size_t i) {
    switch (i) {
        case 0:
            return p;
            break;
        case 1:
            return (point_t){.x = p.x, .y = -p.z, .z = p.y};
            break;
        case 2:
            return (point_t){.x = p.z, .y = p.y, .z = -p.x};
            break;
        case 3:
            return (point_t){.x = -p.z, .y = p.y, .z = p.x};
            break;
        case 4:
            return (point_t){.x = p.z, .y = -p.y, .z = p.x};
            break;

        default:
            return p;
            break;
    }
}

static const size_t ROT_GEN[] = {
    0, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1,
};

static void rotate_scanner(scanner_t scanner, size_t i) {
    for (size_t j = 0; j < scanner.len; j++) {
        scanner.points[j] = rotate(scanner.points[j], i);
    }
}

static point_t add_pts(point_t a, point_t b) {
    return (point_t){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z};
}

static point_t sub_pts(point_t a, point_t b) {
    return (point_t){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
}

static void offset_scanner(scanner_t scanner, point_t offset) {
    for (size_t i = 0; i < scanner.len; i++) {
        scanner.points[i] = add_pts(scanner.points[i], offset);
    }
}

static bool find_overlap(scanner_t s1, scanner_t s2, point_t *result) {
    for (size_t rot_ind = 0; rot_ind < 24; rot_ind++) {
        rotate_scanner(s2, ROT_GEN[rot_ind]);
        for (size_t i = 0; i < s1.len; i++) {
            for (size_t j = 0; j < s2.len; j++) {
                point_t s2_pos = sub_pts(s1.points[i], s2.points[j]);
                size_t amt_in_range = 0;
                for (size_t k = 0; k < s1.len; k++) {
                    point_t p = sub_pts(s1.points[k], s2_pos);
                    p.x = labs(p.x);
                    p.y = labs(p.y);
                    p.z = labs(p.z);
                    size_t m = p.x > p.y ? p.x : p.y;
                    m = m > p.z ? m : p.z;
                    amt_in_range += m <= 1000;
                }
                if (amt_in_range == 12) {
                    size_t amt_overlap = 0;
                    for (size_t k = 0; k < s1.len; k++) {
                        for (size_t l = 0; l < s2.len; l++) {
                            point_t pk = s1.points[k],
                                    pl = add_pts(s2.points[l], s2_pos);
                            amt_overlap +=
                                pk.x == pl.x && pk.y == pl.y && pk.z == pl.z;
                            if (amt_overlap >= 12) {
                                offset_scanner(s2, s2_pos);
                                *result = s2_pos;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    rotate_scanner(s2, 4);
    return false;
}

static size_t amt_fixed(char *fixed, size_t n) {
    size_t counter = 0;
    for (size_t i = 0; i < n; i++) {
        counter += fixed[i];
    }
    return counter;
}

static uint64_t point_hash(const void *p, uint64_t s0, uint64_t s1) {
    return hashmap_sip(p, sizeof(point_t), s0, s1);
}

static int point_cmp(const void *a, const void *b, void *udata) {
    return memcmp(a, b, sizeof(point_t));
}

void d19p1() {
    scanner_t *scanners;
    point_t *points;
    size_t amt_scanners;
    parse_input("input/day19/input", &scanners, &points, &amt_scanners);
    char *fixed = malloc(amt_scanners);
    memset(fixed, 0, amt_scanners);

    fixed[0] = 1;

    while (amt_fixed(fixed, amt_scanners) < amt_scanners) {
        for (size_t i = 0; i < amt_scanners; i++) {
            if (fixed[i]) {
                for (size_t j = 0; j < amt_scanners; j++) {
                    if (i != j && !fixed[j]) {
                        point_t p;
                        if (find_overlap(scanners[i], scanners[j], &p)) {
                            fixed[j] = 1;
                        }
                    }
                }
            }
        }
    }

    struct hashmap *set = hashmap_new(sizeof(point_t), 0, 0, 0, point_hash,
                                      point_cmp, NULL, NULL);

    for (size_t i = 0; i < amt_scanners; i++) {
        for (size_t j = 0; j < scanners[i].len; j++) {
            point_t p = scanners[i].points[j];
            hashmap_set(set, &p);
        }
    }

    size_t ans = hashmap_count(set);

    printf("%zu\n", ans);

    hashmap_free(set);
    free(fixed);
    free(scanners);
    free(points);
}

void d19p2() {
    scanner_t *scanners;
    point_t *points;
    size_t amt_scanners;
    parse_input("input/day19/input", &scanners, &points, &amt_scanners);
    char *fixed = malloc(amt_scanners);
    memset(fixed, 0, amt_scanners);

    fixed[0] = 1;

    point_t *scanner_locs = malloc(sizeof(point_t) * amt_scanners);
    scanner_locs[0] = (point_t){0, 0, 0};
    point_t *cur_scanner_loc = scanner_locs + 1;

    while (amt_fixed(fixed, amt_scanners) < amt_scanners) {
        for (size_t i = 0; i < amt_scanners; i++) {
            if (fixed[i]) {
                for (size_t j = 0; j < amt_scanners; j++) {
                    if (i != j && !fixed[j]) {
                        point_t p;
                        if (find_overlap(scanners[i], scanners[j], &p)) {
                            fixed[j] = 1;
                            *(cur_scanner_loc++) = p;
                        }
                    }
                }
            }
        }
    }

    size_t ans = 0;

    for (size_t i = 0; i < amt_scanners; i++) {
        for (size_t j = i + 1; j < amt_scanners; j++) {
            point_t p = sub_pts(scanner_locs[i], scanner_locs[j]);
            size_t d = llabs(p.x) + llabs(p.y) + llabs(p.z);
            ans = d > ans ? d : ans;
        }
    }

    printf("%zu\n", ans);

    free(fixed);
    free(scanners);
    free(points);
}
