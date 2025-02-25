#include "aoc_string.h"
#include "aoc_alloc.h"
#include "aoc_array.h"
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup(const char *s) {
    size_t size = (strlen(s) + 1) * sizeof(char);
    char  *p = (char *)malloc(size);
    if (p) {
        memcpy(p, s, size);
    }
    return p;
}

char *strconcat(const char *s1, const char *s2) {
    char *return_string = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
    char *pointer;

    pointer = aoc_stpcpy(return_string, s1);
    aoc_stpcpy(pointer, s2);

    return return_string;
}

/* Note: This function returns a pointer to a substring of the original string.
If the given string was allocated dynamically, the caller must not overwrite
that pointer with the returned value, since the original pointer must be
deallocated using the same allocator with which it was allocated.  The return
value must NOT be deallocated using free() etc. */

char *str_trim(char *str) {
    char *end;

    /* Trim leading space */
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') { /* All spaces? */
        return str;
    }

    /* Trim trailing space */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    /* Write new null terminator character */
    end[1] = '\0';

    return str;
}

char *str_join(const char *delimiter, char **str_list, size_t length) {
    char  *result;
    size_t res_length;
    size_t i;
    char  *ptr;

    if (!*str_list) {
        return strdup("");
    }

    res_length = strlen(str_list[0]);

    for (i = 1; (i < length) && (str_list[i] != NULL); i++) {
        res_length += strlen(str_list[i]);
    }
    res_length += (length - 1) * strlen(delimiter) + 1;

    result = (char *)malloc(sizeof(char) * res_length);
    ptr = aoc_stpcpy(result, str_list[0]);
    for (i = 1; (i < length) && (str_list[i] != NULL); i++) {
        ptr = aoc_stpcpy(ptr, delimiter);
        ptr = aoc_stpcpy(ptr, str_list[i]);
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
            count++;
        }
    }
    return count;
}

char *substr(char *str, int start, int end) {
    char *sstr;
    int   i;
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

    sstr = (char *)malloc(sizeof(char) * (end - start + 1));
    for (i = 0; i < (end - start); i++) {
        sstr[i] = str[start + i];
    }
    sstr[i] = '\0';
    return sstr;
}

int str_startswith(char *str, char *start_str) {
    char *sstr;
    int   result;

    sstr = substr(str, 0, (int)strlen(start_str));
    result = !strcmp(start_str, sstr);
    free(sstr);
    return result;
}

int str_endswith(char *str, char *end_str) {
    char *sstr;
    int   result;

    sstr = substr(str, (int)strlen(end_str), (int)strlen(str));
    result = !strcmp(end_str, sstr);
    free(sstr);
    return result;
}

char *strdup_printf(const char *format, ...) {
    va_list args;
    char   *string;
    int     length;

    va_start(args, format);
    length = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (length < 0) {
        return NULL;
    }
    string = (char *)malloc(sizeof(char) * (length + 1));
    va_start(args, format);
    length = vsnprintf(string, length + 1, format, args);
    va_end(args);
    return string;
}

char *strdup_vprintf(const char *format, va_list args) {
    char *string;
    int   length;

    length = vsnprintf(NULL, 0, format, args);
    if (length < 0) {
        return NULL;
    }
    string = (char *)malloc(sizeof(char) * (length + 1));
    length = vsnprintf(string, length + 1, format, args);
    return string;
}

char **str_split(const char *str, const char *delimiter, uint32_t max_tokens) {
    char       *s = NULL;
    const char *remainder;
    AocArrayPtr return_split = NULL;

    if (max_tokens < 1) {
        max_tokens = INT_MAX;
        return_split = aoc_ptr_array_new();
    } else {
        return_split = aoc_array_new(AOC_PTR, max_tokens + 1);
    }

    remainder = str;

    s = (char *)strstr(remainder, delimiter);
    if (s) {
        size_t delimiter_length = strlen(delimiter);
        while (--max_tokens && s) {
            size_t length = s - remainder;
            char  *new_string = strndup(remainder, length);
            aoc_ptr_array_append(return_split, new_string);
            remainder = s + delimiter_length;
            s = (char *)strstr(remainder, delimiter);
        }
    }

    if (*remainder) {
        char *new_string = strdup(remainder);
        aoc_ptr_array_append(return_split, new_string);
    }

    char *end_ptr = NULL;
    aoc_ptr_array_append(return_split, end_ptr);

    char **return_value = (char **)aoc_array_get_data(return_split);

    free(return_split);
    return return_value;
}

void aoc_str_freev(char **str_array) {
    if (str_array) {
        for (size_t i = 0; str_array[i] != NULL; i++) {
            free(str_array[i]);
        }
        free(str_array);
    }
}
/**
 * stpcpy - copy a string from src to dest returning a pointer to the new end
 *          of dest, including src's %NUL-terminator. May overrun dest.
 * @dest: pointer to end of string being copied into. Must be large enough
 *        to receive copy.
 * @src: pointer to the beginning of string being copied from. Must not overlap
 *       dest.
 *
 * stpcpy differs from strcpy in a key way: the return value is the new
 * %NUL-terminated character. (for strcpy, the return value is a pointer to
 * src. This interface is considered unsafe as it doesn't perform bounds
 * checking of the inputs. As such it's not recommended for usage. Instead,
 * its definition is provided in case the compiler lowers other libcalls to
 * stpcpy.
 */
char *aoc_stpcpy(char *__restrict__ dest, const char *__restrict__ src) {
    while ((*dest++ = *src++) != '\0') {
        /* nothing */
        ;
    }
    return --dest;
}

char *strndup(const char *str, size_t n) {
    char *new_str;

    if (str) {
        new_str = (char *)calloc(n + 1, sizeof(char));
        strncpy(new_str, str, n);
        new_str[n] = '\0';
    } else {
        new_str = NULL;
    }

    return new_str;
}
