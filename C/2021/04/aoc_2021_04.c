#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"

typedef struct {
    int board[5][5];
    int hits;
} Board;

void print_board(Board *);

GArray *clean_input(GArray *data) {
    char *line;
    char **split_line;
    GArray *boards;
    GArray *numbers;
    int value;
    GArray *return_data;
    Board *board;

    numbers = g_array_new(TRUE, FALSE, sizeof(int));
    return_data = g_array_new(TRUE, FALSE, sizeof(GArray *));
    boards = g_array_new(TRUE, FALSE, sizeof(Board *));

    line = g_array_index(data, char *, 0);
    split_line = g_strsplit(line, ",", -1);
    int i = 0;
    while(split_line[i] != NULL) {
        value = atoi(split_line[i]);
        g_array_append_val(numbers, value);
        i++;
    }
    g_array_append_val(return_data, numbers);

    i = 2;
    for (size_t b = 2; b + 2 < data->len; b += 6) {
        board = g_new(Board, 1);
        board->hits = 0;
        for (int j = 0; j < 5; j++) {
            int index = j + b;
            line = g_array_index(data, char *, index);
            sscanf(line, "%d %d %d %d %d",
                    &(board->board[j][0]), &(board->board[j][1]),
                    &(board->board[j][2]), &(board->board[j][3]),
                    &(board->board[j][4]));
        }
        g_array_append_val(boards, board);
    }

    g_array_append_val(return_data, boards);

    return return_data;
}

bool check_board(Board *board, int number) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            if (board->board[row][col] == number) {
                board->board[row][col] = -1;
                board->hits++;
            }
        }
    }
    for (int row = 0; row < 5; row++) {
        int rowsum = 0;
        for (int col = 0; col < 5; col++) {
            rowsum += board->board[row][col];
        }
        if (rowsum == -5) {
            return TRUE;
        }
    }
    for (int col = 0; col < 5; col++) {
        int colsum = 0;
        for (int row = 0; row < 5; row++) {
            colsum += board->board[row][col];
        }
        if (colsum == -5) {
            return TRUE;
        }
    }
    return FALSE;
}

int sum_board(Board *board) {
    int board_sum = 0;
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            board_sum += board->board[row][col];
        }
    }
    return board_sum + board->hits;
}

void print_board(Board *board) {
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 5; col++) {
            g_print("%4d", board->board[row][col]);
        }
        g_print("\n");
    }
}

void *solve_part_1(AocData_t *data) {
    Board *board;
    GArray *numbers = g_array_index(data->data, GArray *, 0);
    GArray *boards = g_array_index(data->data, GArray *, 1);

    for (guint i = 0; i < numbers->len; i++) {
        int number = g_array_index(numbers, int, i);
        for (guint b = 0; b < boards->len; b++) {
            board = g_array_index(boards, Board *, b);
            if (check_board(board, number)) {
                return strdup_printf("%d", sum_board(board) * number);
            }
        }
    }

    return strdup_printf("");
}

void *solve_part_2(AocData_t *data) {
    Board *board;
    GArray *numbers = g_array_index(data->data, GArray *, 0);
    GArray *boards = g_array_index(data->data, GArray *, 1);
    GArray *winners = g_array_new(FALSE, FALSE, sizeof(int));
    int winner;
    int number;
    int winner_sum = 0;

    size_t i = 0;
    while ((boards->len > 0) && (i < numbers->len)) {
        number = g_array_index(numbers, int, i++);
        for (guint b = 0; b < boards->len; b++) {
            board = g_array_index(boards, Board *, b);
            if (check_board(board, number)) {
                winner = b;
                g_array_append_val(winners, winner);
            }
        }
        if (winners->len > 0) {
            for (int j = winners->len - 1; j >= 0; j--) {
                winner = g_array_index(winners, int, j);
                board = g_array_index(boards, Board *, winner);
                winner_sum = sum_board(board) * number;
                boards = g_array_remove_index(boards, winner);
            }
            g_array_free(winners, TRUE);
            winners = g_array_new(FALSE, FALSE, sizeof(int));
        }
    }
    return strdup_printf("%d", winner_sum);
}

void *solve_all(AocData_t *data) {
    data->data = clean_input(get_input(data->filename, data->year, data->day));

    if (data->data) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;
    char *filename;

    char *sourcefile;
    int year, day;

    sourcefile = basename(__FILE__);
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);
    free(sourcefile);

    if (argc > 1) {
        filename = strdup(argv[1]);
    } else {
        filename = strdup("input.txt");
    }

    data = aoc_data_new(filename, year, day);
    free(filename);

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
