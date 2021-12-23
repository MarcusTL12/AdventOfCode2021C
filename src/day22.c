#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../AoC_C_utils/src/file_util.h"
#include "../AoC_C_utils/src/vector.h"

typedef struct {
    int64_t x0, x1, y0, y1, z0, z1;
} box_t;

static void printbox(box_t *box) {
    printf("[[%ld, %ld], [%ld, %ld], [%ld, %ld]]\n", box->x0, box->x1, box->y0,
           box->y1, box->z0, box->z1);
}

static bool is_any_overlap(box_t *a, box_t *b) {
    return !(a->x0 > b->x1 || a->x1 < b->x0 || a->y0 > b->y1 || a->y1 < b->y0 ||
             a->z0 > b->z1 || a->z1 < b->z0);
}

static bool get_overlap(box_t *a, box_t *b, box_t *target) {
    if (is_any_overlap(a, b)) {
        target->x0 = a->x0 > b->x0 ? a->x0 : b->x0;
        target->x1 = a->x1 < b->x1 ? a->x1 : b->x1;
        target->y0 = a->y0 > b->y0 ? a->y0 : b->y0;
        target->y1 = a->y1 < b->y1 ? a->y1 : b->y1;
        target->z0 = a->z0 > b->z0 ? a->z0 : b->z0;
        target->z1 = a->z1 < b->z1 ? a->z1 : b->z1;
        return true;
    } else {
        return false;
    }
}

static void box_diff(box_t *a, box_t *b, vec_t *buf) {
    box_t c;
    if (get_overlap(a, b, &c)) {
        if (a->x0 < c.x0) {
            vec_push(buf,
                     &(box_t){a->x0, c.x0 - 1, a->y0, a->y1, a->z0, a->z1});
        }
        if (a->x1 > c.x1) {
            vec_push(buf,
                     &(box_t){c.x1 + 1, a->x1, a->y0, a->y1, a->z0, a->z1});
        }
        if (a->y0 < c.y0) {
            vec_push(buf, &(box_t){c.x0, c.x1, a->y0, c.y0 - 1, a->z0, a->z1});
        }
        if (a->y1 > c.y1) {
            vec_push(buf, &(box_t){c.x0, c.x1, c.y1 + 1, a->y1, a->z0, a->z1});
        }
        if (a->z0 < c.z0) {
            vec_push(buf, &(box_t){c.x0, c.x1, c.y0, c.y1, a->z0, c.z0 - 1});
        }
        if (a->z1 > c.z1) {
            vec_push(buf, &(box_t){c.x0, c.x1, c.y0, c.y1, c.z1 + 1, a->z1});
        }
    } else {
        vec_push(buf, a);
    }
}

static void many_box_diff(box_t *boxes, size_t amt_boxes, box_t *subbox,
                          vec_t *target) {
    for (size_t i = 0; i < amt_boxes; i++) {
        box_diff(&boxes[i], subbox, target);
    }
}

static int64_t volume(box_t *b) {
    return (b->x1 - b->x0 + 1) * (b->y1 - b->y0 + 1) * (b->z1 - b->z0 + 1);
}

void d22p1() {
    char *inp = file_read_full("input/day22/input");

    vec_t screen = vec_create(sizeof(box_t)),
          screen_buf = vec_create(sizeof(box_t)),
          box_frags = vec_create(sizeof(box_t)),
          box_frags_buf = vec_create(sizeof(box_t));

    for (char *c = inp; *c; c++) {
        bool state = c[1] == 'n';
        c += 6 - state;

        box_t curbox;
        int64_t *box_ptr = (int64_t *)&curbox;
        bool hasbig = false;
        for (size_t i = 0; i < 6; i++) {
            box_ptr[i] = atoll(c);
            hasbig |= llabs(box_ptr[i]) > 50;
            while (isdigit(*c) || *c == '-') c++;
            while (*c && *c != '\n' && !isdigit(*c) && *c != '-') c++;
        }

        if (hasbig) break;

        if (state) {
            vec_clear(&box_frags);
            vec_push(&box_frags, &curbox);
            for (size_t i = 0; i < screen.len; i++) {
                vec_clear(&box_frags_buf);
                many_box_diff(box_frags.data, box_frags.len,
                              vec_get(&screen, i), &box_frags_buf);
                vec_t tmp = box_frags;
                box_frags = box_frags_buf;
                box_frags_buf = tmp;
            }
            for (size_t i = 0; i < box_frags.len; i++) {
                vec_push(&screen, vec_get(&box_frags, i));
            }
        } else {
            vec_clear(&screen_buf);
            many_box_diff(screen.data, screen.len, &curbox, &screen_buf);
            vec_t tmp = screen;
            screen = screen_buf;
            screen_buf = tmp;
        }
    }

    int64_t ans = 0;

    for (size_t i = 0; i < screen.len; i++) {
        ans += volume(vec_get(&screen, i));
    }

    printf("%ld\n", ans);

    vec_free(&screen);
    vec_free(&screen_buf);
    vec_free(&box_frags);
    vec_free(&box_frags_buf);
    free(inp);
}

void d22p2() {
    char *inp = file_read_full("input/day22/input");

    vec_t screen = vec_create(sizeof(box_t)),
          screen_buf = vec_create(sizeof(box_t)),
          box_frags = vec_create(sizeof(box_t)),
          box_frags_buf = vec_create(sizeof(box_t));

    for (char *c = inp; *c; c++) {
        bool state = c[1] == 'n';
        c += 6 - state;

        box_t curbox;
        int64_t *box_ptr = (int64_t *)&curbox;
        for (size_t i = 0; i < 6; i++) {
            box_ptr[i] = atoll(c);
            while (isdigit(*c) || *c == '-') c++;
            while (*c && *c != '\n' && !isdigit(*c) && *c != '-') c++;
        }

        if (state) {
            vec_clear(&box_frags);
            vec_push(&box_frags, &curbox);
            for (size_t i = 0; i < screen.len; i++) {
                vec_clear(&box_frags_buf);
                many_box_diff(box_frags.data, box_frags.len,
                              vec_get(&screen, i), &box_frags_buf);
                vec_t tmp = box_frags;
                box_frags = box_frags_buf;
                box_frags_buf = tmp;
            }
            for (size_t i = 0; i < box_frags.len; i++) {
                vec_push(&screen, vec_get(&box_frags, i));
            }
        } else {
            vec_clear(&screen_buf);
            many_box_diff(screen.data, screen.len, &curbox, &screen_buf);
            vec_t tmp = screen;
            screen = screen_buf;
            screen_buf = tmp;
        }
    }

    int64_t ans = 0;

    for (size_t i = 0; i < screen.len; i++) {
        ans += volume(vec_get(&screen, i));
    }

    printf("%ld\n", ans);

    vec_free(&screen);
    vec_free(&screen_buf);
    vec_free(&box_frags);
    vec_free(&box_frags_buf);
    free(inp);
}
