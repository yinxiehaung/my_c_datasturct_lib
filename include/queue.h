#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>

typedef struct Queue Queue;

Queue *Queue_create(size_t data_size);
void Queue_destroy(Queue *queue);

void Queue_push(Queue *queue, const void *data);
void Queue_pop(Queue *queue);
void *Queue_peek(const Queue *queue);
size_t Queue_size(const Queue *queue);
int Queue_is_empty(const Queue *queue);

#define Queue_push_v(_self, type, ...)\
	({\
	  Queue *self = _self;\
	  Queue_push(self, &(type){__VA_ARGS__});\
	})
#define Queue_peek_as(_self, type)\
	({\
	  Queue *self = _self;\
	  type temp_value;\
	  Queue_peek(self, &temp_value);\
	  temp_value;\
	})
#endif
