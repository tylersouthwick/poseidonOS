#include <test.h>
#include <stdio.h>
#include <string.h>
#include <util/priority_queue.h>

#define QUEUE_TEST(testName, body) TESTCASE(testName, {priority_queue queue; priority_queue_create(&queue, FUNCTION_NAME(testName)); body})

QUEUE_TEST(empty_queue, {
	test_assert_true(queue.size == 0);
});

QUEUE_TEST(add_one_item, {
	priority_queue_insert(&queue, 10, 5);
	test_assert_true(queue.first != 0);
	test_assert_true(queue.first->data == 10);
	test_assert_true(queue.size == 1);
});

QUEUE_TEST(add_two_items, {
	priority_queue_insert(&queue, 10, 5);
	priority_queue_insert(&queue, 7, 10);
	test_assert_true(queue.size == 2);

	int head1 = priority_queue_head(&queue);
	test_assert_true(head1 == 10);
	priority_queue_remove(&queue, 10);
	test_assert_true(queue.size == 1);

	int head2 = priority_queue_head(&queue);
	test_assert_true(head2 == 7);
	priority_queue_remove(&queue, 7);
	test_assert_true(queue.size == 0);
});

#define TEST_COUNT 25
int main(int argc, char **argv) {
	test_result_t results[TEST_COUNT];

	memset(&results, 0, sizeof(results));

	int count = 0;
	test_run(empty_queue, &results[count++]);
	test_run(add_one_item, &results[count++]);
	test_run(add_two_items, &results[count++]);

	return test_summary(results, count);
}
