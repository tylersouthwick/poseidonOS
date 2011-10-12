#ifndef UTIL_TEST
#define UTIL_TEST

struct test_result {
	char name[255];
	unsigned int success;
	unsigned int failed;
} typedef test_result_t;

int test_summary(test_result_t *results, int count);
void test_run(int (test)(test_result_t *result), test_result_t *result);

#endif
