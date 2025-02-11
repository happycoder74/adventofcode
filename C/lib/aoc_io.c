#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_list.h"
#include "aoc_string.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int download_input(int year, int day) {
    FILE *fp = NULL;

    const char *filename = ".cookie";
    char        cookie_contents[200];

    char *input_url = strdup_printf("https://adventofcode.com/%d/day/%d/input", year, day);

    char *data_home = NULL;
    data_home = getenv("AOC_DATA_LOCATION");
    if (!data_home) {
        fprintf(
            stderr,
            "Could not find data location. Please set environment variable AOC_DATA_LOCATION\n");
        return EXIT_FAILURE;
    }
    char *path = strdup_printf("%s/%s", data_home, filename);

    fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "Could not open cookie-file\n");
        free(path);
        return EXIT_FAILURE;
    }

    char *s = fgets(cookie_contents, sizeof(cookie_contents) / sizeof(char), fp);
    if (!s) {
        fprintf(stderr, "Failed to read cookie contents\n");
        free(path);
        return EXIT_FAILURE;
    }
    fclose(fp);

    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        FILE    *output_file = NULL;
        char     errbuf[CURL_ERROR_SIZE];
        char    *cookie = strdup_printf("session=%s", cookie_contents);

        char *output_filename = strdup_printf("%s/%d/%02d/input.txt", data_home, year, day);
        output_file = fopen(output_filename, "w");

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
        curl_easy_setopt(curl, CURLOPT_URL, input_url);
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
        curl_easy_setopt(curl, CURLOPT_USERAGENT,
                         "\"github.com/happycoder74/adventofcode/C/lib/aoc_io.c\"");

        res = curl_easy_perform(curl);

        free(cookie);
        free(input_url);
        free(output_filename);
        fclose(output_file);

        if (res != CURLE_OK) {
            fprintf(stderr, "Error in Curl response, (%d) - '%s'\n", res, errbuf);
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
    char     *path;
    char     *file = NULL;

    char *data_location = NULL;
    data_location = getenv("AOC_DATA_LOCATION");
    if ((data_location)) {
        path = strdup_printf("%s/%d/%02d/", data_location, year, day);
    } else {
        path = strdup_printf("../../data/%d/%02d/", year, day);
    }

    if ((!strcmp(filename, "test_input.txt")) || (!strcmp(filename, "input.txt"))) {
        file = strconcat(path, filename);
    } else {
        file = filename;
    }

    fp = fopen(file, "r");
    if (!(fp)) {
        printf("Can not open file!\n");
        return NULL;
    }

    char *to_trim = NULL;
    while ((getline(&line, &line_length, fp)) != -1) {
        to_trim = line;
        aoc_slist_prepend(data, strdup(str_trim(to_trim)));
    }
    free(to_trim);
    free(file);
    free(path);

    return aoc_slist_reverse(data);
}

AocArrayPtr get_input_new(char *filename, int year, int day) {
    FILE       *fp;
    AocArrayPtr data;
    char       *line;
    char       *path;
    char       *file = NULL;
    char       *data_location;
    size_t      line_length = 0;

    data_location = getenv("AOC_DATA_LOCATION");
    if ((data_location)) {
        path = strdup_printf("%s/%d/%02d/", data_location, year, day);
    } else {
        path = strdup_printf("../../data/%d/%02d/", year, day);
    }

    if ((!strcmp(filename, "test_input.txt")) || (!strcmp(filename, "input.txt"))) {
        file = strconcat(path, filename);
    } else {
        file = filename;
    }

    fp = fopen(file, "r");
    if (!(fp)) {
        printf("Can not open file!\n");
        return NULL;
    }

    data = aoc_str_array_new();
    char *to_trim = NULL;
    while ((getline(&line, &line_length, fp)) != -1) {
        to_trim = line;
        aoc_str_array_append(data, str_trim(to_trim));
    }
    free(to_trim);
    if ((line != NULL) && (line != to_trim)) {
        free(line);
    }

    if (file) {
        free(file);
    }

    return data;
}

AocArrayPtr get_input(char *filename, int year, int day) {
    FILE       *fp;
    AocArrayPtr data;
    char       *line = NULL;
    size_t      line_length = 0;
    char       *path;
    char       *file = NULL;
    char        wd[255];
    char       *data_location = NULL;

    data_location = getenv("AOC_DATA_LOCATION");
    if ((data_location)) {
        path = strdup_printf("%s/%d/%02d/", data_location, year, day);
    } else {
        path = strdup_printf("../../data/%d/%02d/", year, day);
    }

    if ((!strcmp(filename, "test_input.txt")) || (!strcmp(filename, "input.txt"))) {
        file = strconcat(path, filename);
    } else {
        file = filename;
    }

    fp = fopen(file, "r");
    if (!(fp)) {
        fprintf(stderr, "Can not open file! (%s)\nCurrent working directory = %s\n", file,
                getcwd(wd, 255));
        fprintf(stderr, "Trying to download...\n");
        int dl_status = download_input(year, day);
        if (!dl_status) {
            return NULL;
        } else {
            fp = fopen(file, "r");
            if (!(fp)) {
                fprintf(stderr, "Download failed... Exiting!\n");
                return NULL;
            }
        }
    }

    data = aoc_str_array_new();

    char *to_trim = NULL;
    while ((getline(&line, &line_length, fp)) != -1) {
        to_trim = line;
        aoc_str_array_append(data, str_trim(to_trim));
    }
    free(to_trim);
    if ((line != NULL) && (line != to_trim)) {
        free(line);
    }

    fclose(fp);
    if (file != filename) {
        free(file);
    }

    free(path);

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
        *buf = realloc(*buf, *bufsiz);
        if ((*buf) == NULL) {
            return -1;
        }
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
        *ptr++ = (char)c;
        if (c == delimiter) {
            *ptr = '\0';
            return ptr - *buf;
        }
        if (ptr + 2 >= eptr) {
            char   *nbuf;
            size_t  nbufsiz = *bufsiz * 2;
            ssize_t d = ptr - *buf;
            nbuf = realloc(*buf, nbufsiz);
            if ((nbuf) == NULL) {
                return -1;
            }
            *buf = nbuf;
            *bufsiz = nbufsiz;
            eptr = nbuf + nbufsiz;
            ptr = nbuf + d;
        }
    }
}
#endif
