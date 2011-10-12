#include "test.h"
#include <stdio.h>
#include <string.h>

static int priority_queue_test(test_result_t *result) {
	strcpy(result->name, "priority queue");
	return 0;
}

#define TEST_COUNT 25
int main(int argc, char **argv) {
	test_result_t results[TEST_COUNT];

	memset(&results, 0, sizeof(results));

	int count = 0;
	test_run(priority_queue_test, &results[count++]);

	return test_summary(results, count);
}
