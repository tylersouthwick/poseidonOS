#ifndef UTIL_TEST
#define UTIL_TEST

struct test_result {
	char name[255];
	unsigned int success;
	unsigned int failed;
} typedef test_result_t;

int priority_queue_tests(test_result_t *test_result);

#endif
