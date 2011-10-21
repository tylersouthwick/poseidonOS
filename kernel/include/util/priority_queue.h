#ifndef MULTITTASKING_PRIORITY_QUEUE_H
#define MULTITTASKING_PRIORITY_QUEUE_H

#define PQ_NODE_COUNT 25

typedef struct pq_node {
	unsigned int data;
	unsigned int priority;
	struct pq_node *prev, *next;
} pq_node;

typedef struct priority_queue {
	int count;
	char name[255];
	pq_node nodes[PQ_NODE_COUNT];
	pq_node *first, *last;
} priority_queue;

void priority_queue_create(priority_queue *queue, const char *name);
void priority_queue_destroy(priority_queue * queue);
void priority_queue_insert(priority_queue *queue, unsigned int data, unsigned int priority);
int priority_queue_head(priority_queue *queue);
void priority_queue_remove(priority_queue *queue, unsigned int data);
void priority_queue_print(priority_queue *queue);

#endif
