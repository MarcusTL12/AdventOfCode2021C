#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "../AoC_C_utils/src/file_util.h"

static int *get_nums(char *inp, size_t *amt_nums) {
    *amt_nums = 1;
    for (char *c = inp; *c != '\n'; c++) *amt_nums += *c == ',';
    int *nums = malloc(*amt_nums * sizeof(int));
    for (size_t i = 0, j = 0; inp[i] != '\n'; j++) {
        nums[j] = atoi(inp + i);
        while (isdigit(inp[i])) i++;
        i++;
    }
    return nums;
}

static char *next_board(char *c, int *board) {
    for (size_t i = 0; i < 25; i++) {
        *board = atoi(c);
        board++;
        while (*c && isdigit(*c)) c++;
        while (*c && !isdigit(*c)) c++;
    }

    return c;
}

static int get_score(int *board) {
    int acc = 0;

    bool any = false;

    for (size_t i = 0; i < 5; i++) {
        bool row = true, col = true;
        for (size_t j = 0; j < 5; j++) {
            row &= board[j + i * 5] == -1;
            col &= board[i + j * 5] == -1;
            acc += board[j + i * 5] == -1 ? 0 : board[j + i * 5];
        }
        any |= row | col;
    }

    return acc * any;
}

static int play_board(int *nums, int *board, size_t *moves) {
    while (true) {
        (*moves)++;
        for (size_t i = 0; i < 25; i++) {
            board[i] = board[i] == *nums ? -1 : board[i];
        }

        int score = get_score(board);

        if (score) {
            return score * *nums;
        }

        nums++;
    }
}

void d4p1() {
    char *inp = file_read_full("input/day4/input");

    size_t amt_nums;
    int *nums = get_nums(inp, &amt_nums);

    char *c = inp;
    while (*c != '\n') c++;
    while (*c == '\n') c++;

    int board[5 * 5];

    size_t lowest_steps = -1;
    int score;

    while (*c) {
        c = next_board(c, board);

        size_t moves = 0;
        int cur_score = play_board(nums, board, &moves);
        if (moves < lowest_steps) {
            lowest_steps = moves;
            score = cur_score;
        }
    }

    printf("%i\n", score);

    free(nums);
    free(inp);
}

void d4p2() {
    char *inp = file_read_full("input/day4/input");

    size_t amt_nums;
    int *nums = get_nums(inp, &amt_nums);

    char *c = inp;
    while (*c != '\n') c++;
    while (*c == '\n') c++;

    int board[5 * 5];

    size_t highest_steps = 0;
    int score;

    while (*c) {
        c = next_board(c, board);

        size_t moves = 0;
        int cur_score = play_board(nums, board, &moves);
        if (moves > highest_steps) {
            highest_steps = moves;
            score = cur_score;
        }
    }

    printf("%i\n", score);

    free(nums);
    free(inp);
}
