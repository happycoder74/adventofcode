#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>

int download_input(int year, int day) {
    FILE *fp = NULL;

    char        input_url[200];
    char        path[200];
    const char *filename = ".cookie";
    char        cookie_contents[200];

    sprintf(input_url, "https://adventofcode.com/%d/day/%d/input", year, day);

    char *data_home = NULL;
    if (!(data_home = getenv("AOC_DATA_LOCATION"))) {
        fprintf(stderr, "Could not find data location. Please set environment variable AOC_DATA_LOCATION\n");
        return EXIT_FAILURE;
    }
    sprintf(path, "%s/%s", data_home, filename);

    if (!(fp = fopen(path, "r"))) {
        fprintf(stderr, "Could not open cookie-file\n");
        return EXIT_FAILURE;
    }

    fgets(cookie_contents, sizeof(cookie_contents) / sizeof(char), fp);
    fclose(fp);

    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        FILE    *output_file = NULL;

        char cookie[200];
        sprintf(cookie, "session=%s", cookie_contents);

        char output_filename[200];
        sprintf(output_filename, "%s/%d/%02d/input.txt", data_home, year, day);
        output_file = fopen(output_filename, "w");

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
        curl_easy_setopt(curl, CURLOPT_URL, input_url);
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);

        res = curl_easy_perform(curl);

        fclose(output_file);

        if (res != CURLE_OK) {
            fprintf(stderr, "Error in Curl response, %d\n", res);
            return EXIT_FAILURE;
        }
        curl_easy_cleanup(curl);
    }
    return EXIT_SUCCESS;
}
