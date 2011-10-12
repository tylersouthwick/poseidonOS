#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

static void test_run(int (test)(test_result_t *result), test_result_t *result);
static int test_summary(test_result_t *results, int count);

#define TEST_COUNT 25
int main(int argc, char **argv) {
	test_result_t results[TEST_COUNT];

	memset(&results, 0, sizeof(results));

	int count = 0;
	test_run(priority_queue_tests, &results[count++]);

	return test_summary(results, count);
}

static int test_summary(test_result_t *results, int count) {
	int failed = 0;
	int success = 0;
	for (int i=0; i < count; i++) {
		test_result_t *result = &results[i];
		failed += result->failed;
		success += result->success;

		if (result->failed) {
			printf("%s ... FAILED\n", result->name);
		} else {
			printf("%s ... SUCCESS\n", result->name);
		}
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
