#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "aoc_types.h"
#include "aoc_utils.h"
#include "aoc_string.h"
#include "aoc_array.h"
#include "aoc_timer.h"

typedef struct {
    int board[5][5];
    int hits;
} Board;


AocArrayPtr clean_input(AocArrayPtr data) {
    char *line;
    char **split_line;
    AocArrayPtr boards;
    AocArrayPtr numbers;

    AocArrayPtr return_data;
    Board *board;

    numbers = aoc_array_new(sizeof(int));
    return_data = aoc_array_new(sizeof(AocArrayPtr ));
    boards = aoc_array_new(sizeof(Board *));

    line = aoc_str_array_index(data, 0);
    split_line = aoc_str_split(line, ",", -1);
    int i = 0;
    while(split_line[i] != NULL) {
        aoc_int_array_append(numbers, atoi(split_line[i++]));
    }
    aoc_array_append(return_data, numbers);

    i = 2;
    for (size_t b = 2; b + 2 < aoc_array_length(data); b += 6) {
        board = (Board *)malloc(sizeof(Board));
        board->hits = 0;
        for (int j = 0; j < 5; j++) {
            int index = j + b;
            line = aoc_str_array_index(data, index);
            sscanf(line, "%d %d %d %d %d",
                    &(board->board[j][0]), &(board->board[j][1]),
                    &(board->board[j][2]), &(board->board[j][3]),
                    &(board->board[j][4]));
        }
        aoc_array_append(boards, board);
    }

    aoc_array_append(return_data, boards);
    aoc_str_freev(split_line);

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

void *solve_part_1(AocData_t *data) {
    Board *board;
    AocArrayPtr numbers = aoc_array_index(aoc_data_get(data), 0);
    AocArrayPtr boards = aoc_array_index(aoc_data_get(data), 1);

    for (unsigned int i = 0; i < aoc_array_length(numbers); i++) {
        int number = aoc_int_array_index(numbers, i);
        for (unsigned int b = 0; b < aoc_array_length(boards); b++) {
            board = (Board *)aoc_array_index(boards, b);
            if (check_board(board, number)) {
                return strdup_printf("%d", sum_board(board) * number);
            }
        }
    }

    return strdup("Not found");
}

void *solve_part_2(AocData_t *data) {
    Board *board;
    AocArrayPtr numbers = aoc_array_index(aoc_data_get(data), 0);
    AocArrayPtr boards = aoc_array_index(aoc_data_get(data), 1);
    AocArrayPtr winners = aoc_array_new(sizeof(int));
    int winner;
    int number;
    int winner_sum = 0;

    size_t i = 0;
    while ((aoc_array_length(boards) > 0) && (i < aoc_array_length(numbers))) {
        number = aoc_int_array_index(numbers, i++);
        for (unsigned int b = 0; b < aoc_array_length(boards); b++) {
            board = (Board *)aoc_array_index(boards, b);
            if (check_board(board, number)) {
                winner = b;
                aoc_int_array_append(winners, winner);
            }
        }
        if (aoc_array_length(winners) > 0) {
            for (int j = aoc_array_length(winners) - 1; j >= 0; j--) {
                winner = aoc_int_array_index(winners, j);
                board = (Board *)aoc_array_index(boards, winner);
                winner_sum = sum_board(board) * number;
                boards = aoc_array_remove_index(boards, winner);
            }
            aoc_array_free(winners);
            winners = aoc_array_new(sizeof(int));
        }
    }
    aoc_array_free(winners);
    return strdup_printf("%d", winner_sum);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }
    return NULL;
}

int main(int argc, char **argv) {
    AocData_t *data;

    char sourcefile[20];
    int year, day;

    strcpy(sourcefile, aoc_basename(__FILE__));
    sscanf(sourcefile, "aoc_%4d_%02d.c", &year, &day);

    if (argc > 1) {
        data = aoc_data_new_clean(argv[1], year, day, clean_input);
    } else {
        data = aoc_data_new_clean("input.txt", year, day, clean_input);
    }

    printf("================================================\n");
    printf("Solution for %d, day %02d\n", year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return 0;
}
