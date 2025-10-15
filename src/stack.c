#include "../include/stack.h"
#include "../include/linked_list.h"
#include <stdlib.h>

struct Stack {
	LinkedList_t *ll;
};

Stack *Stack_create(size_t data_size)
{
	Stack *stack = malloc(sizeof(Stack));
	if (!stack) return NULL;
	stack->ll = LinkedList_create(data_size);
	if (!stack->ll) {
		free(stack);
		return NULL;
	}
	return stack;
}

void Stack_destroy(Stack *stack) 
{
	if (!stack) return;
	Object_delete((Object *)stack->ll);
	free(stack);
}

void Stack_push(Stack *stack, const void *data)
{
	if (!stack) return;
	LinkedList_add_front(stack->ll, data);
}

void Stack_pop(Stack *stack)
{
	if (!stack) return;
	LinkedList_pop_front(stack->ll);
}

void *Stack_peek(const Stack *stack)
{
	if (!stack) return NULL;
	void *data;
	LinkedList_front(stack->ll, &data);
	return data;
}

size_t Stack_size(const Stack *stack)
{
	if (!stack) return 0;
	return LinkedList_size(stack->ll);
}

int Stack_is_empty(const Stack *stack)
{
	if (!stack) return 1;
	return LinkedList_is_empty(stack->ll);
}
