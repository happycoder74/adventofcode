#include "aoc_test.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define print_separator_line()    printf("==========================================================\n")

static void free_cases(TestCase **cases, size_t number_of_cases) {
    for (size_t i = 0; i < number_of_cases; i++) {
        TestCase *ptr = cases[i];
        if(ptr->function_parameters)
            free(ptr->function_parameters);
        free(ptr);
    }
}

TestCaseStructure *init_test_structure(int initial_capacity) {
    TestCaseStructure *ts = (TestCaseStructure *)malloc(sizeof(TestCaseStructure));
    ts->number_of_cases = 0;
    ts->capacity = initial_capacity;
    ts->cases = (TestCase **)calloc(ts->capacity, sizeof(TestCase *));
    ts->passed = 0;

    return ts;
}

void tear_down(TestCaseStructure *ts) {
    free_cases(ts->cases, ts->number_of_cases);
    ts->cases = NULL;
    ts->capacity = 0;
    ts->number_of_cases = 0;
}

static TestCase *new_case(char *test_name, TestFunc func, void *parameters) {
    TestCase *test_case = (TestCase *)malloc(sizeof(TestCase));
    sprintf(test_case->test_name, "%s", test_name);
    test_case->func = func;
    test_case->function_parameters = parameters;

    return test_case;
}

int add_case(TestCaseStructure *ts, char *test_name, TestFunc func, void *parameters) {
    TestCase *c = new_case(test_name, func, parameters);
    if (!c ) {
        return EXIT_FAILURE;
    }

    if (ts->number_of_cases == ts->capacity) {
        ts->capacity *= 2;
        ts->cases = (TestCase **)realloc(ts->cases, ts->capacity);
        if (!(ts->cases)) {
            fprintf(stderr, "Could not resize structure... Exiting with error\n");
            exit(EXIT_FAILURE);
        }
    }
    ts->cases[ts->number_of_cases++] = c;
    return EXIT_SUCCESS;
}

void run_test_cases(TestCaseStructure *ts) {
    print_separator_line();
    printf("* Running %d test cases\n", ts->number_of_cases);
    print_separator_line();

    for (size_t i = 0; i < ts->number_of_cases; i++) {
        TestCase *c = ts->cases[i];
        printf("Running %-40s", c->test_name);
        int result = c->func();
        if (!result) {
            ts->passed++;
            printf("%10s\n", "\033[0;32mPASSED\033[0m");
        } else {
            printf("%10s\n", "\033[0;31mFAILED\033[0m");
        }
    }
}

void test_report(TestCaseStructure *ts) {
    print_separator_line();
    if (ts->passed == ts->number_of_cases) {
        printf("\033[0;32mAll tests passed\033[0m\n");
    } else {
        printf("%d out of %d tests passed\n", ts->passed, ts->number_of_cases);
        printf("%d out of %d tests failed\n", (ts->number_of_cases - ts->passed), ts->number_of_cases);
    }
    print_separator_line();
    printf("Success rate %4.1f %%\n", ((float)(ts->passed)) / ((float) ts->number_of_cases) * 100);
    print_separator_line();

}




