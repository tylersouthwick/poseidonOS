#include "test.h"
#include <stdio.h>
#include <string.h>
#include <util/priority_queue.h>

TESTCASE(empty_queue, {
	priority_queue queue;

	priority_queue_create(&queue, "test1");
	rc += test_assert_true(queue.size != 0);
});

#define TEST_COUNT 25
int main(int argc, char **argv) {
	test_result_t results[TEST_COUNT];

	memset(&results, 0, sizeof(results));

	int count = 0;
	test_run(empty_queue, &results[count++]);

	return test_summary(results, count);
}
