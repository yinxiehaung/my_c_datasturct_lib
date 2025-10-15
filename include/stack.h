#ifndef STACK_H
#define STACK_H
#include <stddef.h>


typedef struct Stack Stack;

Stack *Stack_create(size_t data_size);
void Stack_destroy(Stack *stack);

void Stack_push(Stack *stack, const void *data);
void Stack_pop(Stack *stack);
void *Stack_peek(const Stack *stack);
size_t Stack_size(const Stack *stack);
int Stack_is_empty(const Stack *stack);

#define Stack_push_v(_self, type, ...)\
	({\
	   Stack *self = _self;\
	   Stack_push(self, &(type){__VA_ARGS__});\
	 })
#define Stack_peek_as(_self, type)\
	({\
	  Stack *self = _self;\
	  type temp_value;\
	  Stack_push(self, &temp_value);\
	  temp_value;\
	})
#endif
