#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "aoc_util/file_util.h"

static uint8_t *parse_input(char *filename, size_t *width_, size_t *height_) {
    char *inp = file_read_full(filename);
    size_t len = strlen(inp);

    size_t stride = 1;
    for (char *c = inp; *c != '\n'; c++) stride++;

    size_t width = stride - 1, height = len / stride;

    uint8_t *m = malloc(width * height);

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            char c = inp[i * stride + j];
            m[i * width + j] = c != '.' ? (c == '>' ? 1 : 2) : 0;
        }
    }

    free(inp);

    *width_ = width;
    *height_ = height;
    return m;
}

void d25p1() {
    size_t width, height;
    uint8_t *m = parse_input("input/day25/input", &width, &height);
    uint8_t *m_buf = malloc(width * height);

    bool done = false;
    size_t i = 0;

    while (!done) {
        i++;
        done = true;
        memcpy(m_buf, m, width * height);
        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                uint8_t a = m[i * width + j];
                uint8_t b = m[i * width + (j + 1) % width];
                if (a == 1 && !b) {
                    done = false;
                    m_buf[i * width + j] = 0;
                    m_buf[i * width + (j + 1) % width] = 1;
                }
            }
        }

        uint8_t *tmp = m;
        m = m_buf;
        m_buf = tmp;
        memcpy(m_buf, m, width * height);

        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                if (m[i * width + j] == 2 &&
                    !m[((i + 1) % height) * width + j]) {
                    done = false;
                    m_buf[i * width + j] = 0;
                    m_buf[((i + 1) % height) * width + j] = 2;
                }
            }
        }

        tmp = m;
        m = m_buf;
        m_buf = tmp;
    }

    printf("%zu\n", i);

    free(m_buf);
    free(m);
}

void d25p2() { printf("Merry Christmas!\n"); }
