#include <stdio.h>
#include <string.h>

#include "aoc_util/bitfield.h"
#include "aoc_util/file_util.h"

static char *parse_input(char *filename, char *rules, size_t *w_, size_t *h_) {
    char *inp = file_read_full(filename);

    char *c = inp;

    for (size_t i = 0; i < 512; i++) {
        rules[i] = *(c++) == '#';
    }
    c += 2;

    size_t w = 0;
    while (c[w] != '\n') w++;

    size_t h = 0;
    while (c[h * (w + 1)]) h++;

    char *img = malloc(w * h);

    size_t i = 0;
    for (size_t i = 0; i < w * h; i++) {
        img[i] = *(c++) == '#';
        c += *c == '\n';
    }

    free(inp);

    *w_ = w;
    *h_ = h;

    return img;
}

static size_t do_iters(char *rules, char *img, size_t w, size_t h, size_t its) {
    size_t stride = w + 3 * 4 * (its + 1);
    size_t big_h = h + 3 * 4 * (its + 1);
    size_t amt_bits = stride * big_h;
    char *img_a = malloc(amt_bits);
    char *img_b = malloc(amt_bits);
    memset(img_a, 0, amt_bits);
    memset(img_b, *rules, amt_bits);

    size_t x_start = 3 * 2 * (its + 1), y_start = x_start, x_end = x_start + w,
           y_end = y_start + h;

    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            img_a[(i + y_start) * stride + j + x_start] = img[i * w + j];
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
                        ind = (ind << 1) + img_a[ni * stride + nj];
                    }
                }
                img_b[i * stride + j] = rules[ind];
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
                        ind = (ind << 1) + img_b[ni * stride + nj];
                    }
                }
                img_a[i * stride + j] = rules[ind];
            }
        }
    }

    size_t ans = 0;

    for (size_t i = 0; i < amt_bits; i++) {
        ans += img_a[i];
    }

    free(img_a);
    free(img_b);

    return ans;
}

void d20p1() {
    size_t w, h;
    char rules[512] = {0};
    char *img = parse_input("input/day20/input", rules, &w, &h);

    size_t ans = do_iters(rules, img, w, h, 1);

    printf("%zu\n", ans);

    free(img);
}

void d20p2() {
    size_t w, h;
    char rules[512] = {0};
    char *img = parse_input("input/day20/input", rules, &w, &h);

    size_t ans = do_iters(rules, img, w, h, 25);

    printf("%zu\n", ans);

    free(img);
}
