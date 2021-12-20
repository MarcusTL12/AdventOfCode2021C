#include <stdio.h>

#include "../AoC_C_utils/src/bitfield.h"
#include "../AoC_C_utils/src/file_util.h"

static uint64_t *parse_input(char *filename, uint64_t *rules, size_t *w_,
                             size_t *h_) {
    char *inp = file_read_full(filename);

    char *c = inp;

    for (size_t i = 0; i < 512; i++) {
        bitfield_set(rules, i, *(c++) == '#');
    }
    c += 2;

    size_t w = 0;
    while (c[w] != '\n') w++;

    size_t h = 0;
    while (c[h * (w + 1)]) h++;

    uint64_t *img = bitfield_create(w * h);

    size_t i = 0;
    for (size_t i = 0; i < w * h; i++) {
        bitfield_set(img, i, *(c++) == '#');
        c += *c == '\n';
    }

    free(inp);

    *w_ = w;
    *h_ = h;

    return img;
}

static size_t do_iters(uint64_t *rules, uint64_t *img, size_t w, size_t h,
                       size_t its) {
    size_t stride = w + 3 * 4 * (its + 1);
    size_t big_h = h + 3 * 4 * (its + 1);
    size_t amt_bits = stride * big_h;
    uint64_t *img_a = bitfield_create(amt_bits);
    uint64_t *img_b = bitfield_create(amt_bits);
    if (bitfield_get(rules, 0)) {
        bitfield_not(img_b, amt_bits);
    }

    size_t x_start = 3 * 2 * (its + 1), y_start = x_start, x_end = x_start + w,
           y_end = y_start + h;

    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            bitfield_set(img_a, (i + y_start) * stride + j + x_start,
                         bitfield_get(img, i * w + j));
        }
    }

    for (size_t k = 0; k < its; k++) {
        x_start -= 3;
        x_end += 3;
        y_start -= 3;
        y_end += 3;
        for (size_t i = y_start; i < y_end; i++) {
            for (size_t j = x_start; j < x_end; j++) {
                size_t ind = 0;
                for (size_t ni = i - 1; ni <= i + 1; ni++) {
                    for (size_t nj = j - 1; nj <= j + 1; nj++) {
                        ind =
                            (ind << 1) + bitfield_get(img_a, ni * stride + nj);
                    }
                }
                bitfield_set(img_b, i * stride + j, bitfield_get(rules, ind));
            }
        }
        x_start -= 3;
        x_end += 3;
        y_start -= 3;
        y_end += 3;
        for (size_t i = y_start; i < y_end; i++) {
            for (size_t j = x_start; j < x_end; j++) {
                size_t ind = 0;
                for (size_t ni = i - 1; ni <= i + 1; ni++) {
                    for (size_t nj = j - 1; nj <= j + 1; nj++) {
                        ind =
                            (ind << 1) + bitfield_get(img_b, ni * stride + nj);
                    }
                }
                bitfield_set(img_a, i * stride + j, bitfield_get(rules, ind));
            }
        }
    }

    return bitfield_count(img_a, bitfield_ints(amt_bits));
}

void d20p1() {
    size_t w, h;
    uint64_t rules[8] = {0};
    uint64_t *img = parse_input("input/day20/input", rules, &w, &h);

    size_t ans = do_iters(rules, img, w, h, 1);

    printf("%zu\n", ans);
}

void d20p2() {
    size_t w, h;
    uint64_t rules[8] = {0};
    uint64_t *img = parse_input("input/day20/input", rules, &w, &h);

    size_t ans = do_iters(rules, img, w, h, 25);

    printf("%zu\n", ans);
}
