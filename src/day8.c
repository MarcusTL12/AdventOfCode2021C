#include <ctype.h>
#include <stdint.h>
#include <stdio.h>

#include "../AoC_C_utils/src/combinatorics.h"
#include "../AoC_C_utils/src/file_util.h"

void d8p1() {
    char *inp = file_read_full("input/day8/input");

    size_t total = 0;

    for (char *c = inp; *c;) {
        while (*c != '|') c++;
        c++;
        for (size_t i = 0; i < 4; i++) {
            size_t j = 0;
            while (isalpha(*++c)) j++;
            switch (j) {
                case 2:
                case 3:
                case 4:
                case 7:
                    total += 1;
                default:
                    break;
            }
        }
        if (*c == '\n') c++;
    }

    printf("%zu\n", total);

    free(inp);
}

void d8p2() {
    uint8_t valid_segments_bytes[10 * 8] = {
        1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1,
        1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0,
        1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0,
        0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0,
    };

    uint64_t *valid_segments = (uint64_t *)valid_segments_bytes;

    char *inp = file_read_full("input/day8/input");

    int64_t ans = 0;

    for (char *c = inp; *c;) {
        size_t permstate[7] = {0, 0, 0, 0, 0, 0, 0},
               perm[7] = {0, 0, 0, 0, 0, 0, 0};

        do {
            get_perm(perm, permstate, 7);

            bool all_good = true;
            char *cc = c;
            for (size_t i = 0; i < 10; i++) {
                uint64_t segments_int = 0;
                uint8_t *segments = (uint8_t *)&segments_int;

                do {
                    segments[perm[*cc - 'a']] = 1;
                } while (isalpha(*++cc));
                cc++;

                bool this_good = false;
                for (size_t j = 0; j < 10; j++) {
                    this_good |= segments_int == valid_segments[j];
                    if (this_good) break;
                }
                all_good &= this_good;
                if (!all_good) break;
            }
            if (all_good) break;
        } while (next_permstate(permstate, 7));

        while (*c != '|') c++;
        c += 2;

        int64_t n = 0;
        for (size_t i = 0; i < 4; i++) {
            uint64_t segments_int = 0;
            uint8_t *segments = (uint8_t *)&segments_int;

            do {
                segments[perm[*c - 'a']] = 1;
            } while (isalpha(*++c));
            c++;

            int64_t d = 0;
            while (segments_int != valid_segments[d]) d++;

            n = 10 * n + d;
        }
        ans += n;
    }

    printf("%ld\n", ans);

    free(inp);
}
