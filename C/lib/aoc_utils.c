#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "aoc_utils.h"
#include "aoc_array.h"
#include "aoc_string.h"
#include "aoc_list.h"
#include "aoc_types.h"

AocData_t *aoc_data_set_data(AocData_t *aoc, AocArrayPtr data) {
    if(aoc) {
        aoc->data = data;
        return aoc;
    }
    return NULL;
}

// AocArrayPtr aoc_data_data(AocData_t *data) {
//     if(data) {
//         return data->data;
//     }
//     return NULL;
// }

AocData_t *aoc_data_new_clean(gchar *filename, int year, int day, AocArray *(*clean_function)(AocArray *)) {
    AocData_t *data = (AocData_t *)malloc(sizeof (AocData_t));

    data->filename = strdup(filename);
    data->year = year;
    data->day = day;

    if(clean_function) {
        data->data = clean_function(get_input(filename, year, day));
    } else {
        data->data = get_input(filename, year, day);
    }
    return data;
}

void aoc_data_free(AocData_t *data) {
    if (data->filename) {
        free(data->filename);
    }

    if (data->data) {
        aoc_array_free(data->data, 0);
    }
    free(data);
}



AocSList *get_input_list(char *filename, int year, int day) {
    FILE *fp;
    AocSList *data = NULL;
    char *line = NULL;
    size_t line_length = 0;
    char *data_line;
    char *path;
    char *file = NULL;

    path = strdup_printf("../../../data/%d/%02d/", year, day);
    file = strconcat(path, filename);

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file!\n");
        return NULL;
    }

    while ((getline(&line, &line_length, fp)) != -1) {
        data_line = str_trim(strdup(line));
        data = aoc_slist_prepend(data, data_line);
    }

    free(file);
    free(path);

    return aoc_slist_reverse(data);
}

AocArrayPtr get_input_new(char *filename, int year, int day) {
    FILE *fp;
    AocArrayPtr data;
    char line[10000];
    char *data_line;
    char path[255];
    char *file = NULL;

    sprintf(path, "../../data/%d/%02d/", year, day);
    data = aoc_str_array_new();
    file = strconcat(path, filename);

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file!\n");
        return NULL;
    }

    while (fgets(line, 10000, fp)) {
        data_line = str_trim(strdup(line));
        aoc_str_array_append(data, data_line);
    }

    if (file) {
        free(file);
    }

    return data;
}

AocArrayPtr get_input(char *filename, int year, int day) {
    FILE *fp;
    AocArrayPtr data;
    gchar *line = NULL;
    size_t line_length = 0;
    gchar *data_line;
    gchar *path;
    gchar *file = NULL;
    char wd[255];
    path = strdup_printf("../../data/%d/%02d/", year, day);
    data = aoc_str_array_new();
    if (!strcmp(filename, "input.txt")) {
        file = strconcat(path, filename);
    } else {
        file = filename;
    }

#ifdef DEBUG
    printf("%s\n", file);
#endif

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file! (%s)\nCurrent working directory = %s\n",
               file, getcwd(wd ,255));
        return NULL;
    }

    while ((getline(&line, &line_length, fp)) != -1) {
        data_line = str_trim(strdup(line));
        aoc_str_array_append(data, data_line);
    }

    if (file != filename) {
        free(file);
    }

    free(path);

    return data;
}

int max(int *arr, int length) {
    int max = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int min(int *arr, int length) {
    int min = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int int_array_max(int *arr, int length) {
    int max = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int int_array_min(int *arr, int length) {
    int min = arr[0];
    int i;

    for (i = 1; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int min_non_zero(int *arr, int length) {
    int min = length;
    int i;

    for (i = 0; i < length; i++) {
        if ((arr[i] < min) && (arr[i] != 0)) {
            min = arr[i];
        }
    }
    return min;
}

#ifdef __MINGW32__
ssize_t getline(char **buf, size_t *bufsiz, FILE *fp) {
	return getdelim(buf, bufsiz, '\n', fp);
}

ssize_t getdelim(char **buf, size_t *bufsiz, int delimiter, FILE *fp) {
	char *ptr, *eptr;


	if (*buf == NULL || *bufsiz == 0) {
		*bufsiz = BUFSIZ;
		if ((*buf = malloc(*bufsiz)) == NULL)
			return -1;
	}

	for (ptr = *buf, eptr = *buf + *bufsiz;;) {
		int c = fgetc(fp);
		if (c == -1) {
			if (feof(fp)) {
				ssize_t diff = (ssize_t)(ptr - *buf);
				if (diff != 0) {
					*ptr = '\0';
					return diff;
				}
			}
			return -1;
		}
		*ptr++ = c;
		if (c == delimiter) {
			*ptr = '\0';
			return ptr - *buf;
		}
		if (ptr + 2 >= eptr) {
			char *nbuf;
			size_t nbufsiz = *bufsiz * 2;
			ssize_t d = ptr - *buf;
			if ((nbuf = realloc(*buf, nbufsiz)) == NULL)
				return -1;
			*buf = nbuf;
			*bufsiz = nbufsiz;
			eptr = nbuf + nbufsiz;
			ptr = nbuf + d;
		}
	}
}

#endif

void print_line(Line line) {
    Point diff;
    Point point;

    diff = point_difference(line.p0, line.p1);

    printf(
        "Line from (%d, %d) to (%d, %d) - distance (%d, %d) - step (%d, %d)\n",
        line.p0.x, line.p0.y, line.p1.x, line.p1.y, diff.x, diff.y, line.stepx,
        line.stepy);
    for (point = line.p0; (point.x != (line.p1.x + line.stepx)) ||
                          (point.y != (line.p1.y + line.stepy));
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

int point_manhattan_distance(Point p0,  Point p1) {
    return abs(p0.x - p1.x) + abs(p0.y - p1.y);
}

int point_distance(Point p0,  Point p1) {
    return sqrt((p0.x - p1.x)*(p0.x - p1.x) + (p0.y - p1.y)*(p0.y - p1.y));
}

void point_print(Point p) {
    printf("Point (%d, %d)\n", p.x, p.y);
    return;
}

char *point_to_string(Point p, char *buf) {
    sprintf(buf, "(%d, %d)", p.x, p.y);
    return buf;
}

unsigned int point_hash(const void *p) {
    Point *point = (Point *)p;
    uint64_t *int_hash = (uint64_t *)malloc(sizeof(uint64_t));
    *int_hash = point->x;
    *int_hash <<= sizeof(UINT_MAX) * 4;
    *int_hash ^= point->y;

    unsigned int return_value = g_int64_hash(int_hash);
    free(int_hash);
    return return_value;
}

int point_equal(gconstpointer pp1, gconstpointer pp2) {
    Point *p1, *p2;
    p1 = (Point *)pp1;
    p2 = (Point *)pp2;
    return (p1->x == p2->x) && (p1->y == p2->y);
}


// Legacy function to be removed later
char *basename(const char *path) {
#if (defined (__WIN32__) && !(defined __MINGW32__))
    char pathsep = '\\';
#else
    char pathsep = '/';
#endif
    char *ptr = strrchr(path, pathsep);
    if (!ptr)
        return strdup(path);
    return strdup(ptr + 1);
}

char *basename_new(const char *path) {
#if (defined (__WIN32__) && !(defined __MINGW32__))
    char pathsep = '\\';
#else
    char pathsep = '/';
#endif
    char *ptr = strrchr(path, pathsep);
    if (!ptr)
        return (char *)path;
    return (ptr + 1);
}

char *_aoc_basename(const char *path, const char pathsep) {
    char *s = strrchr(path, pathsep);
    if (!s) {
        return strdup(path);
    } else {
        return strdup(s + 1);
    }
}

bool is_horisontal(Line line) { return line.p0.y == line.p1.y; }

bool is_vertical(Line line) { return line.p0.x == line.p1.x; }

bool is_parallel(Line line1, Line line2) {
    if (((line1.p0.x - line1.p1.x) == 0) && ((line2.p0.x - line2.p1.x) == 0))
        return TRUE;
    if (((line1.p0.y - line1.p1.y) == 0) && ((line2.p0.y - line2.p1.y) == 0))
        return TRUE;
    return FALSE;

}

bool is_diagonal(Line line) {
    if(is_vertical(line))
        return FALSE;
    return (abs((line.p1.y - line.p0.y) / (line.p1.x - line.p0.x)) == 1);
}

void line_print(Line line) {
    printf(
        "(%d, %d) to (%d, %d)\n",
        line.p0.x, line.p0.y, line.p1.x, line.p1.y);
}

Line line_new(Point p0, Point p1) {
    Line line;
    line.p0 = p0;
    line.p1 = p1;
    line.stepx = p1.x - p0.x;
    line.stepy = p1.y - p0.y;
    return line;
}

Point point_new(int x, int y) {
    Point point;

    point.x = x;
    point.y = y;

    return point;
}

Point *point_new_m(int x, int y) {
    Point *p = (Point *)malloc(sizeof(Point));
    p->x = x;
    p->y = y;

    return p;
}

Point *line_intersection(Line line1, Line line2, Point *intersection_point) {
    float u, t;
    int x1, x2, x3, x4;
    int y1, y2, y3, y4;

    if (is_parallel(line1, line2))
        return NULL;

    x1 = line1.p0.x;
    y1 = line1.p0.y;
    x2 = line1.p1.x;
    y2 = line1.p1.y;
    x3 = line2.p0.x;
    y3 = line2.p0.y;
    x4 = line2.p1.x;
    y4 = line2.p1.y;

    t = (float)((x1 - x3)*(y3 - y4) - (y1 - y3)*(x3 - x4)) /
        (float)((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

    u = (float)((x1 - x3)*(y1 - y2) - (y1 - y3)*(x1 - x2)) /
        (float)((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

    #ifndef NDEBUG
    printf("t = %f, u = %f\n", t, u);
    #endif /* ifdef ndef NDEBUG */

    if (!((0 <= t) && (t <= 1.0)) || !((0 <= u) && (u <= 1.0))) {
        return NULL;
    }

    intersection_point->x = x1 + t*(x2 - x1);
    intersection_point->y = y1 + t*(y2 - y1);

    return intersection_point;
}

void line_array_print(AocArrayPtr lines) {
    for (size_t i = 0; i < aoc_array_length(lines); i++) {
        line_print(aoc_line_array_index(lines, i));
#define aoc_uint32_array_index(arr_, index_)    (*(uint32_t *)(aoc_array_index(arr_, index_)))
#define aoc_uint32_array_append(arr_, value_)   do { \
                                                    int val_ = value_; \
                                                    aoc_array_append(arr_, &val_); \
                                                } while (0)
#define aoc_uint32_array_free(arr_)             (aoc_array_free(arr_, false))
#define aoc_uint32_array_free_all(arr_)         (aoc_array_free(arr_, true))
#define aoc_uint32_array_sort(_arr, func)       (aoc_array_sort(_arr, func))
    }
}

bool point_on_line(Point p, Line line) {
    // int d1 = sqrt(pow(p.x - line.p0.x, 2) + pow(p.y - line.p0.y, 2));
    // int d2 = sqrt(pow(p.x - line.p1.x, 2) + pow(p.y - line.p0.y, 2));
    // int d = sqrt(pow(line.p1.x - line.p0.x, 2) + pow(line.p1.y - line.p0.y, 2));
    // printf("Distance diff: %d\n", d1+d2 - d);
    // return d == d1 + d2;
    if (is_vertical(line)) {
        return ((MIN(line.p0.y, line.p1.y) <= p.y) && (p.y <= MAX(line.p0.y, line.p1.y)) && (line.p0.x == p.x));
    } else if (is_horisontal(line)) {
        return ((MIN(line.p0.x, line.p1.x) <= p.x) && (p.x <= MAX(line.p0.x, line.p1.x)) && (line.p0.y == p.y));
    } else {
        int y = (line.p1.y - line.p0.y) / (line.p1.x - line.p0.x) * (p.x - line.p0.x) + line.p0.y;
        return p.y == y;
    }
}

int line_length(Line line) {
    return point_distance(line.p0, line.p1);
}
