#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_utils.h"

typedef struct {
    int board[5][5];
    int hits;
} Board;

void print_board(Board *);

GArray *clean_input(GArray *data) {
    gchar *line;
    gchar **split_line;
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
    for (guint b = 2; b + 2 < data->len; b += 6) {
        board = g_new(Board, 1);
        board->hits = 0;
        for (gint j = 0; j < 5; j++) {
            gint index = j + b;
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

gboolean check_board(Board *board, int number) {
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

int solve_part_1(GArray *data) {
    Board *board;
    GArray *numbers = g_array_index(data, GArray *, 0);
    GArray *boards = g_array_index(data, GArray *, 1);

    for (guint i = 0; i < numbers->len; i++) {
        int number = g_array_index(numbers, int, i);
        for (guint b = 0; b < boards->len; b++) {
            board = g_array_index(boards, Board *, b);
            if (check_board(board, number)) {
                return sum_board(board) * number;
            }
        }
    }

    return 0;
}

int solve_part_2(GArray *data) {
    Board *board;
    GArray *numbers = g_array_index(data, GArray *, 0);
    GArray *boards = g_array_index(data, GArray *, 1);
    GArray *winners = g_array_new(FALSE, FALSE, sizeof(int));
    int winner;
    int number;
    int winner_sum;

    guint i = 0;
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
    return winner_sum;
}

int solve_all(gchar *filename, int year, int day) {
    GArray *data;

    data = clean_input(get_input(filename, year, day));

    if (data) {
        TIMER(1, solve_part_1(data), INT, 1);
        TIMER(2, solve_part_2(data), INT, 1);

        g_array_free(data, TRUE);
    }

    return 0;
}

int main(int argc, char **argv) {
    gchar *filename;

    if (argc > 1) {
        filename = g_strdup(argv[1]);
    } else {
        filename = g_strdup("input.txt");
    }

    TIMER(0, solve_all(filename, 2021, 4), INT, 0);
    g_free(filename);

    return 0;
}
