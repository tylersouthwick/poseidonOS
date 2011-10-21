#ifndef UTIL_TEST
#define UTIL_TEST

#include <kdebug.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct test_result {
	unsigned int success;
	unsigned int failed;
} typedef test_result_t;

static int test_summary(test_result_t *results, int count);
static void test_run(int (test)(test_result_t *result), test_result_t *result);

#define STR_VALUE(arg) #arg
#define FUNCTION_NAME(name) STR_VALUE(name)

#define TESTCASE(testName, body) static int testName (test_result_t *result) { int rc = 0; printf("%s ... ", FUNCTION_NAME(testName)); body; if (!rc) printf("SUCCESS\n"); return rc;}

#define test_assert_true(expression) if (rc == 0) {if (!(expression)) {ERROR_MSG(("test should be true: %s", FUNCTION_NAME(expression))); rc++;}}

static int test_summary(test_result_t *results, int count) {
	int failed = 0;
	int success = 0;
	for (int i=0; i < count; i++) {
		test_result_t *result = &results[i];
		failed += result->failed;
		success += result->success;
	}

	printf("SUCCESS: %i\nFAILURE: %i\n", success, failed);

	return failed;
}

static void test_run(int (test)(test_result_t *result), test_result_t *result) {
	int rc = test(result);

	if (rc) {
		result->failed = 1;
		result->success = 0;
	} else {
		result->failed = 0;
		result->success = 1;
	}
}
#endif
