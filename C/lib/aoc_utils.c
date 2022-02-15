#include <glib.h>
#include <aoc_utils.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

/* Note: This function returns a pointer to a substring of the original string.
If the given string was allocated dynamically, the caller must not overwrite
that pointer with the returned value, since the original pointer must be
deallocated using the same allocator with which it was allocated.  The return
value must NOT be deallocated using free() etc. */

char *str_trim(char *str) {
  char *end;

  /* Trim leading space */
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  /* All spaces? */
    return str;

  /* Trim trailing space */
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  /* Write new null terminator character */
  end[1] = '\0';

  return str;
}


char *str_join(const char *delimiter, char **str_list, size_t length) {
    char *result;
    int res_length;
    size_t i;
    char *ptr;

    if (!*str_list) {
        return  strdup("");
    }

    res_length = strlen(str_list[0]);

    for (i = 1; (i < length) && (str_list[i] != NULL); i++) {
        res_length += strlen(str_list[i]);
    }
    res_length += (length - 1) * strlen(delimiter) + 1;

    result = malloc(sizeof(char) * res_length);
    ptr = stpcpy(result, str_list[0]);
    for (i = 1; (i < length) && (str_list[i] != NULL); i++) {
        ptr = stpcpy(ptr, delimiter);
        ptr = stpcpy(ptr, str_list[i]);
    }
    return result;
}


int str_count(char *str, char needle, int start, int end) {
    int i;
    int count = 0;
    if (end < 0) {
        end = (int)strlen(str) - 1 - end;
    }
    if (start < 0) {
        start = (int)strlen(str) - 1 - start;
    }

    for (i = start; i < end; i++) {
        if (needle == str[i]) {
            count ++;
        }
    }
    return count;
}

char *substr(char *str, int start, int end) {
    char *substr;
    int i;
    if (end < 0) {
        end = (int)strlen(str) - 1 + end + 1;
    }
    if (start < 0) {
        start = (int)strlen(str) - 1 + start + 1;
    }

    assert(end <= (int)strlen(str));
    assert(start >= 0);
    assert(end >= 0);
    assert(start < (int)strlen(str));
    assert(start <= end);

    substr = malloc(sizeof(char) * (end - start + 1));
    for (i = 0; i < (end - start); i++) {
        substr[i] = str[start + i];
    }
    substr[i] = '\0';
    return substr;
}

int str_startswith(char *str, char *start_str) {
    char *sstr;
    int result;

    sstr = substr(str, 0, strlen(start_str));
    result = !strcmp(start_str, sstr);
    free(sstr);
    return result;
}

int str_endswith(char *str, char *end_str) {
    char *sstr;
    int result;

    sstr = substr(str, -strlen(end_str), strlen(str));
    result = !strcmp(end_str, sstr);
    free(sstr);
    return result;
}


GArray *get_input_new(char *filename, int year, int day) {
    FILE *fp;
    GArray *data;
    gchar *line = NULL;
    size_t line_length = 0;
    gchar *data_line;
    gchar *path;
    gchar *file = NULL;

    path = g_strdup_printf("../../../data/%d/%02d/", year, day);
    data = g_array_new(TRUE, FALSE, sizeof(char *));
    file = g_strconcat(path, filename, NULL);

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file!\n");
        return NULL;
    }

    while ((getline(&line, &line_length, fp)) != -1 ) {
        data_line = g_strstrip(g_strdup(line));
        g_array_append_val(data, data_line);
    }

    if (file) {
        g_free(file);
    }
    g_free(path);

    return data;;
}

GArray *get_input(char *filename, int year, int day) {
    FILE *fp;
    GArray *data;
    gchar *line = NULL;
    size_t line_length = 0;
    gchar *data_line;
    gchar *path;
    gchar *file = NULL;

    path = g_strdup_printf("../../../data/%d/%02d/", year, day);
    data = g_array_new(FALSE, FALSE, sizeof(char *));
    file = g_strconcat(path, filename, NULL);

#ifdef DEBUG
    g_print("%s\n", file);
#endif

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file!\n");
        return NULL;
    }

    while ((getline(&line, &line_length, fp)) != -1 ) {
        data_line = g_strstrip(g_strdup(line));
        g_array_append_val(data, data_line);
    }

    if (file) {
        g_free(file);
    }
    g_free(path);

    return data;;
}

gint max(gint *arr, gint length) {
    gint max = arr[0];
    gint i;

    for (i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

gint min(gint *arr, gint length) {
    gint min = arr[0];
    gint i;

    for (i = 1; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

gint min_non_zero(gint *arr, gint length) {
    gint min = length;
    gint i;

    for (i = 0; i < length; i++) {
        if ((arr[i] < min) && (arr[i] != 0)) {
            min = arr[i];
        }
    }
    return min;
}


Grid *grid_new(int rows, int columns) {
    Grid *grid = malloc(sizeof(Grid));
    grid->grid = malloc(sizeof(int) * rows * columns);
    grid->rows = rows;
    grid->columns = columns;

    return grid;
}

int grid_index(Grid *grid, int row, int column) {
    int index = row * grid->columns + column;
    return grid->grid[index];
}

void grid_index_set(Grid *grid, int row, int column, int value) {
    int index = row * grid->columns + column;
    grid->grid[index] = value;
}


void print_line(Line line) {
    Point diff;
    Point point;

    diff = point_difference(line.p0, line.p1);

    printf("Line from (%d, %d) to (%d, %d) - distance (%d, %d) - step (%d, %d)\n",
            line.p0.x, line.p0.y,
            line.p1.x, line.p1.y,
            diff.x, diff.y,
            line.stepx, line.stepy);
    for (point = line.p0;
            (point.x != (line.p1.x + line.stepx)) || (point.y != (line.p1.y + line.stepy));
            point.x += line.stepx, point.y += line.stepy) {
        printf("\t(%d, %d)\n", point.x, point.y);
    }


    return;
}


Point point_difference(Point p0, Point p1) {
    Point diff;

    diff.x = p1.x - p0.x;
    diff.y = p1.y - p0.y;

    return diff;
}

Point points_on_line(Line line) {
    Point diff;

    diff = point_difference(line.p0, line.p1);

    return diff;
}

gboolean is_horisontal(Line line) {
    return line.p0.y == line.p1.y;
}

gboolean is_vertical(Line line) {
    return line.p0.x == line.p1.x;
}


guint point_hash(gconstpointer p) {
    Point *point = (Point *)p;
    gchar *str = g_strdup_printf("(%d,%d)", point->x, point->y);

    return g_str_hash(str);
}

gboolean point_equal(gconstpointer pp1, gconstpointer pp2) {
    Point *p1, *p2;
    p1 = (Point *)pp1;
    p2 = (Point *)pp2;
    return (p1->x == p2->x) && (p1->y == p2->y);
}
