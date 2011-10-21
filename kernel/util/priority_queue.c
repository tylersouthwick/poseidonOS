#include <util/priority_queue.h>
#include <kdebug.h>
#include <string.h>

static pq_node *create_node(priority_queue *queue, unsigned int data, unsigned int priority) {
	pq_node *node = &(queue->nodes[queue->node_count++]);
	memset(node, 0, sizeof(pq_node));
	node->data = data;
	node->priority = priority;
	return node;
}

void priority_queue_create(priority_queue *queue, const char *name) {
	DEBUG_MSG(("Creating queue %s", name));
	memset(queue, 0, sizeof(priority_queue));
	strcpy(queue->name, name);
	queue->size = 0;
}

void priority_queue_destroy(priority_queue * queue) {
	pq_node *node;
	DEBUG_MSG(("Destorying queue %s", queue->name));
	node = queue->first;
	while (node) {
		pq_node *n = node->next;
		node = n;
	}
}

static int contains(priority_queue *queue, unsigned int data) {
	int i = 0;
	pq_node *n = queue->first;
	while (n && i < queue->size) {
		if (n->data == data) {
			return 1;
		}
		n = n->next;
	}
	return 0;
}

static void insert_node(priority_queue *queue, pq_node *after, pq_node *n) {

	n->next = after->next;
	n->prev = after;

	if (after->next)
		after->next->prev = n;
	else
		queue->last = n;
	after->next = n;
}

void priority_queue_insert(priority_queue *queue, unsigned int data, unsigned int priority) {
	pq_node *node;

	if (queue->size == 0) {
		DEBUG_MSG(("Inserting %i into queue[%s]", data, queue->name));
		queue->first = queue->last = create_node(queue, data, priority);
		queue->size = 1;
		return;
	}

	if (contains(queue, data)) {
		DEBUG_MSG(("Queue %s already contains [%i]", queue->name, data));
		return;
	}

	node = queue->first;
	DEBUG_MSG(("iterating to insert %i into %s with %i items", data, queue->name, queue->size));
	int i = 0;
	while (node && i < queue->size) {
		i++;
		if (node->data == data) {
			DEBUG_MSG(("%i already exists in queue [%s]", data, queue->name));
			return;
		}

		if (priority <= node->priority) continue;

		insert_node(queue, node, create_node(queue, data, priority));
		queue->size++;

		return;
	}

	DEBUG_MSG(("Inserting %i at end of queue[%s]", data, queue->name));
	{
		pq_node *last = queue->last;
		last->next = create_node(queue, data, priority);
		last->next->prev = last;
		queue->last = last->next;
	}
	queue->size++;
	return;
}

int priority_queue_head(priority_queue *queue) {
	if (queue->size== 0) {
		return -1;
	}

	DEBUG_MSG(("getting head from queue [%s]", queue-> name));

	queue->size--;
	pq_node *n = queue->first;
	//assert(n != NULL);
	unsigned int data = n->data;
	queue->first = n->next;
	if (queue->first)
		queue->first->prev = NULL;
	if (n == queue->last)
		queue->last = NULL;
	//kfree(n);

	return data;
}

static void remove_node(priority_queue *queue, pq_node *n) {
	DEBUG_MSG(("removing node..."));
	if (n->prev)
		n->prev->next = n->next;
	else
		queue->first = n->next;

	if (n->next)
		n->next->prev = n->prev;
	else
		queue->last = n->prev;
}

void priority_queue_remove(priority_queue *queue, unsigned int data) {
	pq_node *n;
	DEBUG_MSG(("Removing %i from queue [%s]", data, queue->name));
	n = queue->first;
	while (n) {
		if (n->data != data) {
			n = n->next;
			continue;
		}

		//remove node
		remove_node(queue, n);
		queue->size--;
		return;
	}
}
