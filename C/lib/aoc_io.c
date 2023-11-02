#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_list.h"
#include "aoc_string.h"
#include "aoc_types.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>

int download_input(int year, int day) {
    FILE *fp = NULL;

    const char *filename = ".cookie";
    char        cookie_contents[200];

    char *input_url = strdup_printf("https://adventofcode.com/%d/day/%d/input", year, day);

    char *data_home = NULL;
    if (!(data_home = getenv("AOC_DATA_LOCATION"))) {
        fprintf(stderr, "Could not find data location. Please set environment variable AOC_DATA_LOCATION\n");
        return EXIT_FAILURE;
    }
    char *path = strdup_printf("%s/%s", data_home, filename);

    if (!(fp = fopen(path, "r"))) {
        fprintf(stderr, "Could not open cookie-file\n");
        aoc_free(path);
        return EXIT_FAILURE;
    }

    fgets(cookie_contents, sizeof(cookie_contents) / sizeof(char), fp);
    fclose(fp);

    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        FILE    *output_file = NULL;

        char *cookie = strdup_printf("session=%s", cookie_contents);

        char *output_filename = strdup_printf("%s/%d/%02d/input.txt", data_home, year, day);
        output_file = fopen(output_filename, "w");

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
        curl_easy_setopt(curl, CURLOPT_URL, input_url);
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);

        res = curl_easy_perform(curl);

        aoc_free(cookie);
        aoc_free(input_url);
        aoc_free(output_filename);
        fclose(output_file);

        if (res != CURLE_OK) {
            fprintf(stderr, "Error in Curl response, %d\n", res);
            return EXIT_FAILURE;
        }
        curl_easy_cleanup(curl);
    }
    return EXIT_SUCCESS;
}

AocSList *get_input_list(char *filename, int year, int day) {
    FILE     *fp;
    AocSList *data = NULL;
    char     *line = NULL;
    size_t    line_length = 0;
    char     *data_line;
    char     *path;
    char     *file = NULL;

    char *data_location = NULL;
    if ((data_location = getenv("AOC_DATA_LOCATION")))
        path = strdup_printf("%s/%d/%02d/", data_location, year, day);
    else
        path = strdup_printf("../../data/%d/%02d/", year, day);
    file = strconcat(path, filename);

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file!\n");
        return NULL;
    }

    while ((getline(&line, &line_length, fp)) != -1) {
        data_line = str_trim(strdup(line));
        data = aoc_slist_prepend(data, data_line);
    }

    aoc_free(file);
    aoc_free(path);

    return aoc_slist_reverse(data);
}

AocArrayPtr get_input_new(char *filename, int year, int day) {
    FILE       *fp;
    AocArrayPtr data;
    char        line[10000];
    char       *data_line;
    char       *path;
    char       *file = NULL;

    char *data_location;
    if ((data_location = getenv("AOC_DATA_LOCATION")))
        path = strdup_printf("%s/%d/%02d/", data_location, year, day);
    else
        path = strdup_printf("../../data/%d/%02d/", year, day);

    file = strconcat(path, filename);

    if (!(fp = fopen(file, "r"))) {
        printf("Can not open file!\n");
        return NULL;
    }

    data = aoc_str_array_new();
    while (fgets(line, 10000, fp)) {
        data_line = str_trim(strdup(line));
        aoc_str_array_append(data, data_line);
    }

    if (file) {
        aoc_free(file);
    }

    return data;
}

AocArrayPtr get_input(char *filename, int year, int day) {
    FILE       *fp;
    AocArrayPtr data;
    gchar      *line = NULL;
    size_t      line_length = 0;
    gchar      *data_line;
    gchar      *path;
    gchar      *file = NULL;
    char        wd[255];
    char       *data_location = NULL;
    if ((data_location = getenv("AOC_DATA_LOCATION")))
        path = strdup_printf("%s/%d/%02d/", data_location, year, day);
    else
        path = strdup_printf("../../data/%d/%02d/", year, day);

    if ((!strcmp(filename, "test_input.txt")) || (!strcmp(filename, "input.txt"))) {
        file = strconcat(path, filename);
    } else {
        file = filename;
    }

    if (!(fp = fopen(file, "r"))) {
        fprintf(stderr, "Can not open file! (%s)\nCurrent working directory = %s\n", file, getcwd(wd, 255));
        return NULL;
    }

    data = aoc_str_array_new();

    while ((getline(&line, &line_length, fp)) != -1) {
        char *to_trim = strdup(line);
        data_line = strdup(str_trim(to_trim));
        aoc_str_array_append(data, data_line);
        aoc_free(to_trim);
        aoc_free(line);
    }

    if (file != filename) {
        aoc_free(file);
    }

    aoc_free(path);

    return data;
}

#ifdef __MINGW32__
ssize_t getline(char **buf, size_t *bufsiz, FILE *fp) {
    return getdelim(buf, bufsiz, '\n', fp);
}

ssize_t getdelim(char **buf, size_t *bufsiz, int delimiter, FILE *fp) {
    char *ptr, *eptr;

    if (*buf == NULL || *bufsiz == 0) {
        *bufsiz = BUFSIZ;
        if ((*buf = aoc_malloc(*bufsiz)) == NULL)
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
            char   *nbuf;
            size_t  nbufsiz = *bufsiz * 2;
            ssize_t d = ptr - *buf;
            if ((nbuf = aoc_realloc(*buf, nbufsiz)) == NULL)
                return -1;
            *buf = nbuf;
            *bufsiz = nbufsiz;
            eptr = nbuf + nbufsiz;
            ptr = nbuf + d;
        }
    }
}

#endif
