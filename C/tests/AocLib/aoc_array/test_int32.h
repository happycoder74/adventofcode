#ifndef __TEST_INT32_H__
#define __TEST_INT32_H__

#include <stdbool.h>

int test_int32_array_new(void);
int test_int32_array_append(void);
int test_int32_array_index(void);
int test_int32_array_remove_index(void);
int test_int32_array_append_to_null(void);
int test_int32_array_append_to_wrong_type(void);

// Not yet implemented, shall not pass tests
int test_int32_array_insert(void);
int test_int32_array_insert_at_beginning(void);
int test_int32_array_insert_at_end(void);
int test_int32_array_insert_outside(void);

#endif // !__TEST_INT32_H__
