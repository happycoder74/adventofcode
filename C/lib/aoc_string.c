#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "aoc_string.h"
/* Note: This function returns a pointer to a substring of the original string.
If the given string was allocated dynamically, the caller must not overwrite
that pointer with the returned value, since the original pointer must be
deallocated using the same allocator with which it was allocated.  The return
value must NOT be deallocated using free() etc. */

char *str_trim(char *str) {
    char *end;

    /* Trim leading space */
    while (isspace((unsigned char)*str)) str++;

    if (*str == '\0') /* All spaces? */
        return str;

    /* Trim trailing space */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

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
        return strdup("");
    }

    res_length = strlen(str_list[0]);

    for (i = 1; (i < length) && (str_list[i] != NULL); i++) {
        res_length += strlen(str_list[i]);
    }
    res_length += (length - 1) * strlen(delimiter) + 1;

    result = (char *)malloc(sizeof(char) * res_length);
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
            count++;
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

    substr = (char *)malloc(sizeof(char) * (end - start + 1));
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

char *strdup_printf(const char *format, ...) {
    va_list args;
    char *string;
    int length;

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

#ifdef __MINGW32__

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
char *stpcpy(char *__restrict__ dest, const char *__restrict__ src) {
    while ((*dest++ = *src++) != '\0') /* nothing */
        ;
    return --dest;
}

#endif

