#define _XOPEN_SOURCE 600 // To get hold of clock_gettime etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void free_matrix(char **matrix, const int dimension, const int rotation) {
    unsigned int rot_dim = dimension;
    if ((rotation % 90) != 0) {
        rot_dim = 2 * dimension - 1;
    }
    for (unsigned int i = 0; i < rot_dim; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

char **rotate_matrix(const char **matrix, const size_t dimension, const int degrees) {
    size_t rotated_dimension;
    char **rotated_matrix = NULL;

    unsigned int line;

    switch (degrees) {
        case 45:
            rotated_dimension = 2 * dimension - 1;
            rotated_matrix = (char **)calloc(rotated_dimension, sizeof(char *));

            line = 0;
            for (unsigned int i = 0; i < dimension; i++) {
                rotated_matrix[line] = (char *)calloc(dimension, sizeof(char));
                for (unsigned j = 0; j < i + 1; j++) {
                    rotated_matrix[line][j] = matrix[i - j][j];
                }
                line++;
            }
            for (unsigned int j = 1; j < dimension; j++) {
                rotated_matrix[line] = (char *)calloc(dimension, sizeof(char));
                unsigned int col = 0;
                for (unsigned int i = dimension - 1; i >= j; i--) {
                    rotated_matrix[line][col++] = matrix[i][j + dimension - 1 - i];
                }
                line++;
            }

            return rotated_matrix;
            break;
        case -45:
            rotated_dimension = 2 * dimension - 1;
            rotated_matrix = (char **)calloc(rotated_dimension, sizeof(char *));

            line = 0;
            for (unsigned int j = 0; j < dimension; j++) {
                rotated_matrix[line] = (char *)calloc(dimension, sizeof(char));
                unsigned int col = 0;
                for (unsigned i = 0; i < j + 1; i++) {
                    rotated_matrix[line][col++] = matrix[i][dimension - j - 1 + i];
                }
                line++;
            }
            for (unsigned int i = 1; i < dimension; i++) {
                rotated_matrix[line] = (char *)calloc(dimension, sizeof(char));
                unsigned int col = 0;
                for (unsigned int j = 0; j < dimension - i; j++) {
                    rotated_matrix[line][col++] = matrix[i + j][j];
                }
                line++;
            }

            return rotated_matrix;
            break;
        case 90:
            rotated_dimension = dimension;
            rotated_matrix = (char **)calloc(rotated_dimension, sizeof(char *));

            line = 0;
            for (unsigned int j = 0; j < dimension; j++) {
                rotated_matrix[line] = (char *)calloc(dimension, sizeof(char));
                unsigned int col = 0;
                for (unsigned int i = 0; i < dimension; i++) {
                    rotated_matrix[line][col] = matrix[i][dimension - 1 - j];
                    col++;
                }
                line++;
            }

            return rotated_matrix;
            break;
        default:
            return NULL;
            break;
    }
}

unsigned int count_xmas(const char **matrix, const unsigned int dimension, const int rotation) {
    unsigned int count = 0;
    unsigned int rot_dim = dimension;
    if ((rotation % 90) != 0) {
        rot_dim = 2 * dimension - 1;
    }

    for (unsigned int i = 0; i < rot_dim; i++) {
        char *pointer = (char *)matrix[i];
        while ((pointer = strstr(pointer, "XMAS")) != NULL) {
            count++;
            pointer += 4;
        }
        pointer = (char *)matrix[i];
        while ((pointer = strstr(pointer, "SAMX")) != NULL) {
            count++;
            pointer += 4;
        }
    }

    return count;
}

int solve_part_1(char **matrix, size_t dimension) {

    unsigned int count = 0;

    count += count_xmas((const char **)matrix, dimension, 0);
    char **rot_matrix = rotate_matrix((const char **)matrix, dimension, 45);
    count += count_xmas((const char **)rot_matrix, dimension, 45);
    free_matrix(rot_matrix, dimension, 45);
    rot_matrix = rotate_matrix((const char **)matrix, dimension, 90);
    count += count_xmas((const char **)rot_matrix, dimension, 90);
    free_matrix(rot_matrix, dimension, 90);
    rot_matrix = rotate_matrix((const char **)matrix, dimension, -45);
    count += count_xmas((const char **)rot_matrix, dimension, -45);
    free_matrix(rot_matrix, dimension, -45);

    return count;
}

int solve_part_2(char **matrix, size_t dimension) {
    unsigned int count = 0;

    char pattern[4][5] = {
        {'M', 'M', 'S', 'S'},
        {'S', 'M', 'S', 'M'},
        {'S', 'S', 'M', 'M'},
        {'M', 'S', 'M', 'S'}
    };

    for (unsigned int i = 1; i < dimension - 1; i++) {
        for (unsigned int j = 1; j < dimension - 1; j++) {
            if (matrix[i][j] != 'A') {
                continue;
            }
            for (unsigned int i_pattern = 0; i_pattern < 4; i_pattern++) {
                short int match = (matrix[i - 1][j - 1] == pattern[i_pattern][0]);
                match = match && (matrix[i - 1][j + 1] == pattern[i_pattern][1]);
                match = match && (matrix[i + 1][j - 1] == pattern[i_pattern][2]);
                match = match && (matrix[i + 1][j + 1] == pattern[i_pattern][3]);
                if (match) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

int main(void) {

    FILE           *fp = NULL;
    char            filename[255];
    char          **matrix = NULL;
    size_t          dimension = 200;
    struct timespec start, stop;

    clock_gettime(CLOCK_REALTIME, &start);

    matrix = (char **)malloc(dimension * sizeof(char *));

    sprintf(filename, "%s/2024/04/input.txt", getenv("AOC_DATA_LOCATION"));
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Could not open input file\n");
        exit(EXIT_FAILURE);
    }

    char   line[1000];
    size_t line_counter = 0;

    while (fgets(line, 1000, fp) != NULL) {
        matrix[line_counter] = (char *)calloc(strlen(line), sizeof(char));
        memmove(matrix[line_counter], line, strlen(line) * sizeof(char));
        line_counter++;
    }

    clock_gettime(CLOCK_REALTIME, &stop);

    fprintf(stdout, "====================== SOLUTION ========================\n");
    fprintf(stdout, "Preparation time:   ");
    fprintf(stdout, "%20.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 1: %10d", solve_part_1(matrix, line_counter));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    clock_gettime(CLOCK_REALTIME, &start);
    fprintf(stdout, "Solution to part 2: %10d", solve_part_2(matrix, line_counter));
    clock_gettime(CLOCK_REALTIME, &stop);
    fprintf(stdout, "%10.3lf ms (%lu ns)\n",
            (stop.tv_sec * 1e3 + stop.tv_nsec * 1e-6) - (start.tv_sec * 1e3 + start.tv_nsec * 1e-6),
            (stop.tv_nsec - start.tv_nsec));
    fprintf(stdout, "--------------------------------------------------------\n");

    free(matrix);
    return 0;
}
