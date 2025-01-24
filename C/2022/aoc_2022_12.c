#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_grid.h"
#include "aoc_header.h"
#include "aoc_sets.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static volatile bool keep_running = true;

void interupt_handler(int var) {
    fprintf(stderr, "You pressed CTRL-C, you fool\n");
    keep_running = false;
}

typedef enum ActionCommand {
    A_UP,
    A_DOWN,
    A_LEFT,
    A_RIGHT,
    A_NONE
} ActionCommand;

typedef struct Node {
    Point        *state;
    struct Node  *parent;
    ActionCommand action;
} Node;

typedef struct Trail {
    int32_t     height;
    int32_t     width;
    AocArrayPtr start;
    Point       goal;
    AocGrid    *contents;
    AocArrayPtr solution;
    AocSet     *explored;
} Trail;

typedef struct Action {
    ActionCommand command;
    Point         state;
} Action;

Node *new_node(Point *state, Node *parent, ActionCommand action) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->state = state;
    node->parent = parent;
    node->action = action;

    return node;
}

Trail *init_trail(AocGrid *data, AocArrayPtr start, Point end) {
    Trail *trail = (Trail *)malloc(sizeof(Trail));

    trail->height = data->rows;
    trail->width = data->columns;
    trail->start = start;
    trail->contents = data;
    trail->solution = NULL;
    trail->goal = end;

    return trail;
}

void free_trail(Trail *trail) {
    if (!trail)
        return;
    if (trail->contents)
        aoc_grid_free(trail->contents);
    if (trail->explored)
        aoc_set_free(trail->explored);
    if (trail->solution)
        aoc_ptr_array_free_all(trail->solution);
}

AocArrayPtr neighbors(Trail *trail, const Point *state) {
    AocArrayPtr result = aoc_ptr_array_new();
    int32_t     row, col;
    row = state->x;
    col = state->y;

    Action candidates[] = {
        {A_UP,    {row - 1, col}},
        {A_DOWN,  {row + 1, col}},
        {A_LEFT,  {row, col - 1}},
        {A_RIGHT, {row, col + 1}}
    };

    for (unsigned i = 0; i < 4; i++) {
        Action  ac = candidates[i];
        int32_t r = candidates[i].state.x;
        int32_t c = candidates[i].state.y;
        if ((0 <= r) && (r < trail->height)) {
            if ((0 <= c) && (c < trail->width)) {
                int height = (int)(int64_t)aoc_grid_get(trail->contents, r, c) -
                             (int)(int64_t)aoc_grid_get(trail->contents, row, col);
                if (height <= 1) {
                    Action *action = malloc(sizeof(Action));
                    action->command = ac.command;
                    action->state = ac.state;
                    aoc_ptr_array_append(result, action);
                }
            }
        }
    }
    return result;
}

void solve(Trail *trail) {
    AocArrayPtr queue = aoc_ptr_array_new();

    for (unsigned i = 0; i < trail->start->length; i++) {
        Node *n = new_node((Point *)aoc_ptr_array_index(trail->start, i), NULL, A_NONE);
        aoc_ptr_array_append(queue, n);
    }

    trail->explored = aoc_set_new(AOC_POINT);

    signal(SIGINT, interupt_handler);

    int counter = 0;
    while (keep_running) {
        if (queue->length == 0) {
            trail->solution = NULL;
            return;
        }

        Node *n = (Node *)aoc_array_pop_index(queue, 0);
        if (point_equal(n->state, &trail->goal)) {
            AocArrayPtr actions = aoc_ptr_array_new();
            while (n->parent != NULL) {
                Action *action = (Action *)malloc(sizeof(Action));
                action->command = n->action;
                action->state = *n->state;
                aoc_ptr_array_append(actions, action);
                n = n->parent;
            }
            trail->solution = aoc_array_reverse(actions);
            aoc_ptr_array_free(actions);

            return;
        }

        aoc_set_add(trail->explored, n->state);
        AocArrayPtr nb = neighbors(trail, n->state);
        for (unsigned in = 0; in < nb->length; in++) {
            Action *action = aoc_ptr_array_index(nb, in);
            bool    in_queue = false;
            for (unsigned index = 0; index < queue->length && !in_queue; index++) {
                Node *n = (Node *)aoc_ptr_array_index(queue, index);
                in_queue = point_equal(n->state, &action->state);
            }
            if ((!in_queue) && (!aoc_set_in(trail->explored, &action->state))) {
                Node *child = (Node *)malloc(sizeof(Node));
                child->state = &action->state;
                child->parent = n;
                child->action = action->command;
                aoc_ptr_array_append(queue, child);
            } else {
                free(action);
            }
        }
        aoc_ptr_array_free(nb);
    }

    // After interrupt
    printf("Queue length: %d\n", queue->length);
    Node *current = (Node *)aoc_array_last(queue);
    printf("Current point: (%d, %d)\n", current->state->x, current->state->y);
    return;
}

AocArray *clean_input(AocArray *data) {
    AocArray *return_data = aoc_ptr_array_new();
    AocGrid  *grid = NULL;
    Point    *start;
    Point    *end;
    for (unsigned i = 0; i < data->length; i++) {
        char *row = aoc_str_array_index(data, i);
        if (!grid) {
            GridDimensions dim = {data->length, strlen(row)};
            grid = aoc_grid_new(&dim);
        }
        for (unsigned j = 0; j < strlen(row); j++) {
            int32_t value;
            char    c = row[j];
            if (c == 'S') {
                value = 'a';
                start = point_new_m(i, j);
            } else if (c == 'E') {
                value = 'z';
                end = point_new_m(i, j);
            } else {
                value = c;
            }
            aoc_grid_set(grid, i, j, (void *)(int64_t)value);
        }
    }
    aoc_ptr_array_append(return_data, grid);
    aoc_ptr_array_append(return_data, start);
    aoc_ptr_array_append(return_data, end);
    return return_data;
}

void *solve_part_1(AocData_t *data) {
    AocArrayPtr traildata = aoc_data_get(data);
    AocGrid    *grid = aoc_ptr_array_index(traildata, 0);
    Point      *start = aoc_ptr_array_index(traildata, 1);
    Point      *end = aoc_ptr_array_index(traildata, 2);
    AocArrayPtr start_list = aoc_ptr_array_new();
    aoc_ptr_array_append(start_list, start);
    Trail *trail = init_trail(grid, start_list, *end);

    solve(trail);
    if (trail->solution) {
        return strdup_printf("%u", trail->solution->length);
    }
    return NULL;
}

void *solve_part_2(AocData_t *data) {
    return NULL;
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2022;
    const unsigned day = 12;

    AocData_t *data = get_data(argc, argv, year, day, clean_input);

    aoc_header(year, day);
    timer_func(0, solve_all, data, 0);

    aoc_data_free(data);

    return aoc_mem_gc();
}
