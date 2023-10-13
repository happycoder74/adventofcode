#ifndef __AOC_TEST_H__
#define __AOC_TEST_H__

#include <stddef.h>

typedef int(*TestFunc)(void);

typedef struct {
    char test_name[100];
    TestFunc func;
    void *function_parameters;
} TestCase;

typedef struct {
    TestCase **cases;
    size_t number_of_cases;
    size_t capacity;
    size_t passed;
} TestCaseStructure;


TestCaseStructure *init_test_structure(int initial_capacity);
void tear_down(TestCaseStructure *ts);
int add_case(TestCaseStructure *ts, char *test_name, TestFunc func, void *parameters);
void run_test_cases(TestCaseStructure *ts);

void test_report(TestCaseStructure *ts);

#endif // !__AOC_TEST_H__


