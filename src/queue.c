#include "../include/queue.h"
#include "../include/linked_list.h"
#include <stdlib.h>

struct Queue {
	LinkedList_t *ll;
};

Queue *Queue_create(size_t data_size) 
{
	Queue *queue = malloc(sizeof(Queue));
	if (!queue) return NULL;
	queue->ll = LinkedList_create(data_size);
	if (!queue->ll) {
		free(queue);
		return NULL;
	}
	return queue;
}

void Queue_destroy(Queue *queue)
{
	if (!queue) return;
	Object_delete((Object *)queue->ll);
	free(queue);
}

void Queue_push(Queue *queue, const void *data)
{
	if (!queue) return;
	LinkedList_add_back(queue->ll, data);
}

void Queue_pop(Queue *queue)
{
	if (!queue) return;
	LinkedList_pop_front(queue->ll);
}

void *Queue_peek(const Queue *queue)
{
	if (!queue) return NULL;
	void *data;
	LinkedList_front(queue->ll, &data);
	return data;
}

size_t Queue_size(const Queue *queue)
{
	if (!queue) return 0;	
	return LinkedList_size(queue->ll);
}

int Queue_is_empty(const Queue *queue)
{
	if (!queue) return 1;
	return LinkedList_is_empty(queue->ll); 
}
