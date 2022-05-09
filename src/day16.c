#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "aoc_util/file_util.h"

static void set_nibble(uint8_t *dest, char digit) {
    switch (digit) {
        case '0':
            dest[0] = 0, dest[1] = 0, dest[2] = 0, dest[3] = 0;
            break;
        case '1':
            dest[0] = 0, dest[1] = 0, dest[2] = 0, dest[3] = 1;
            break;
        case '2':
            dest[0] = 0, dest[1] = 0, dest[2] = 1, dest[3] = 0;
            break;
        case '3':
            dest[0] = 0, dest[1] = 0, dest[2] = 1, dest[3] = 1;
            break;
        case '4':
            dest[0] = 0, dest[1] = 1, dest[2] = 0, dest[3] = 0;
            break;
        case '5':
            dest[0] = 0, dest[1] = 1, dest[2] = 0, dest[3] = 1;
            break;
        case '6':
            dest[0] = 0, dest[1] = 1, dest[2] = 1, dest[3] = 0;
            break;
        case '7':
            dest[0] = 0, dest[1] = 1, dest[2] = 1, dest[3] = 1;
            break;
        case '8':
            dest[0] = 1, dest[1] = 0, dest[2] = 0, dest[3] = 0;
            break;
        case '9':
            dest[0] = 1, dest[1] = 0, dest[2] = 0, dest[3] = 1;
            break;
        case 'A':
            dest[0] = 1, dest[1] = 0, dest[2] = 1, dest[3] = 0;
            break;
        case 'B':
            dest[0] = 1, dest[1] = 0, dest[2] = 1, dest[3] = 1;
            break;
        case 'C':
            dest[0] = 1, dest[1] = 1, dest[2] = 0, dest[3] = 0;
            break;
        case 'D':
            dest[0] = 1, dest[1] = 1, dest[2] = 0, dest[3] = 1;
            break;
        case 'E':
            dest[0] = 1, dest[1] = 1, dest[2] = 1, dest[3] = 0;
            break;
        case 'F':
            dest[0] = 1, dest[1] = 1, dest[2] = 1, dest[3] = 1;
            break;
    }
}

static uint8_t *parse_input(char *filename) {
    char *inp = file_read_full(filename);

    size_t len = 0;
    while (inp[len] && inp[len] != '\n') len++;

    uint8_t *bits = malloc(len * 4);

    for (size_t i = 0; i < len; i++) {
        set_nibble(&bits[4 * i], inp[i]);
    }

    free(inp);

    return bits;
}

static int64_t collect_binary(uint8_t *bits, size_t n) {
    int64_t x = 0;
    for (size_t i = 0; i < n; i++) {
        x = (x << 1) | *(bits++);
    }
    return x;
}

typedef struct {
    int64_t n;
    size_t amt_bits;
} packet_t;

static packet_t parse_packet(uint8_t *bits, int64_t *vernumsum) {
    *vernumsum += collect_binary(bits, 3);
    bits += 3;

    int64_t t = collect_binary(bits, 3);
    bits += 3;

    size_t amt_bits = 6;

    if (t == 4) {
        int64_t n = 0;
        while (*(bits++)) {
            amt_bits += 5;
            n = (n << 4) | collect_binary(bits, 4);
            bits += 4;
        }
        amt_bits += 5;
        n = (n << 4) | collect_binary(bits, 4);
        bits += 4;
        return (packet_t){.n = n, .amt_bits = amt_bits};
    } else {
        amt_bits++;
        bool bits_or_packets = *(bits++);
        size_t n_bits_num, n_things;
        if (!bits_or_packets) {
            n_bits_num = 15;
        } else {
            n_bits_num = 11;
        }
        n_things = collect_binary(bits, n_bits_num);
        bits += n_bits_num;
        amt_bits += n_bits_num;
        bool first = true;
        int64_t n;
        switch (t) {
            case 0:
                n = 0;
                break;
            case 1:
                n = 1;
                break;
            case 2:
                n = INT64_MAX;
                break;
            case 3:
                n = INT64_MIN;
                break;
        }
        for (size_t cur_amt_things = 0; cur_amt_things < n_things;
             first = false) {
            packet_t p = parse_packet(bits, vernumsum);
            bits += p.amt_bits;
            amt_bits += p.amt_bits;
            if (bits_or_packets) {
                cur_amt_things++;
            } else {
                cur_amt_things += p.amt_bits;
            }

            switch (t) {
                case 0:
                    n += p.n;
                    break;
                case 1:
                    n *= p.n;
                    break;
                case 2:
                    n = p.n < n ? p.n : n;
                    break;
                case 3:
                    n = p.n > n ? p.n : n;
                    break;
                case 5:
                    if (first) {
                        n = p.n;
                    } else {
                        n = n > p.n;
                    }
                    break;
                case 6:
                    if (first) {
                        n = p.n;
                    } else {
                        n = n < p.n;
                    }
                    break;
                case 7:
                    if (first) {
                        n = p.n;
                    } else {
                        n = n == p.n;
                    }
                    break;
            }
        }
        return (packet_t){.n = n, .amt_bits = amt_bits};
    }
}

void d16p1() {
    uint8_t *bits = parse_input("input/day16/input");

    int64_t vernumsum = 0;
    parse_packet(bits, &vernumsum);

    printf("%ld\n", vernumsum);

    free(bits);
}

void d16p2() {
    uint8_t *bits = parse_input("input/day16/input");

    int64_t vernumsum = 0;
    packet_t p = parse_packet(bits, &vernumsum);

    printf("%ld\n", p.n);

    free(bits);
}
