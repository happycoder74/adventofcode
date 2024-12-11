#include <pcre2posix.h>
#include <stdio.h>
#include <string.h>

unsigned int solver(unsigned short part, char lines[10][4000], unsigned int nlines) {
    regex_t    re;
    size_t     nmatches = 4;
    regmatch_t matches[4];

    char pattern[] = "(mul\\((\\d{1,3}),(\\d{1,3})\\)|don\\'t\\(\\)|do\\(\\))";

    pcre2_regcomp(&re, pattern, 0);

    unsigned  result = 0;
    short int enabled = 1;
    for (unsigned int line_counter = 0; line_counter < nlines; line_counter++) {
        char  *str = lines[line_counter];
        size_t offset = 0;
        while (pcre2_regexec(&re, str + offset, nmatches, matches, 0) == 0) {
            unsigned int counter;
            for (counter = 0; (counter < nmatches) && (matches[counter].rm_so != -1); counter++) {
                size_t start = matches[counter].rm_so;
                size_t end = matches[counter].rm_eo;
                char   substring[100] = {0};
                strncpy(substring, str + offset + start, end - start);
                if ((strncmp(substring, "mul", 3) == 0) && enabled) {
                    unsigned int v1 = 0, v2 = 0;
                    sscanf(substring, "mul(%d,%d)", &v1, &v2);
                    result += v1 * v2;
                    counter += 3;
                } else if (strncmp(substring, "do(", 3) == 0) {
                    enabled = 1;
                    counter += 1;
                } else if (strncmp(substring, "don", 3) == 0) {
                    if (part == 2) {
                        enabled = 0;
                    }
                    counter += 1;
                }
            }
            offset += matches[counter - 1].rm_eo;
        }
    }
    return result;
}

int main(void) {

    FILE *fp = NULL;
    char  lines[10][4000];

    char filename[255];
    sprintf(filename, "%s/2024/03/input.txt", getenv("AOC_DATA_LOCATION"));

    fp = fopen(filename, "r");
    unsigned int line_counter = 0;
    while (fgets(lines[line_counter], 4000, fp) != NULL) {
        line_counter++;
    }
    fclose(fp);

    printf("Solution for part 1: %u\n", solver(1, lines, line_counter));
    printf("Solution for part 2: %u\n", solver(2, lines, line_counter));
}
