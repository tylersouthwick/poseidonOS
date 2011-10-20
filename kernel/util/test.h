#ifndef UTIL_TEST
#define UTIL_TEST

#include <kdebug.h>

struct test_result {
	char name[255];
	unsigned int success;
	unsigned int failed;
} typedef test_result_t;

int test_summary(test_result_t *results, int count);
void test_run(int (test)(test_result_t *result), test_result_t *result);

static int test_assert_true(int expression) {
	if (expression) {
		return 0;
	} else {
		ERROR(("expression should be true"));
		return 1;
	}
}

#define STR_VALUE(arg) #arg
#define FUNCTION_NAME(name) STR_VALUE(name)

#define TESTCASE(testName, body) static int testName (test_result_t *result) { int rc = 0; strcpy(result->name, FUNCTION_NAME(testName)); body; return rc;}
#endif
