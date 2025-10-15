#include <stdlib.h>
#include <string.h>
#include "header/dstruct_delc.h"
#include "header/core_internal.h"
#include "../include/linked_list.h"


typedef struct Node {
    void *data;
    struct Node *next;
	struct Node *prev;
}Node;

typedef struct {
	const IteratorVTable *vtable;
	Node *current_node;
} LinkedListIterator;


typedef struct LinkedList{
    const ContainerVTable *vtable;
    Node *head;
	Node *tail;
    size_t count;
	size_t data_size;
} LinkedList_t;

// Object Function
static void *ll_ctor(void *_self, va_list *app) 
{
    LinkedList_t *self = _self;
    self->head = NULL;
	self->tail = NULL;
    self->count = 0;
    return self;
}

static void ll_dtor(void *_self)
{
	if (!_self) return;
	LinkedList_t *self = _self;
	if (self->vtable && self->vtable->clear) {
		self->vtable->clear(_self);
	}	
}

// LinkedList iterator function
static int ll_iter_is_equal(const void *_self, const void *_other)
{
	const LinkedListIterator *self = _self;
	const LinkedListIterator *other = _other;
	return self->current_node == other->current_node;
}

static void ll_iter_next(void *_self) 
{
	LinkedListIterator *self = _self;
	if (self && self->current_node) {
		self->current_node = self->current_node->next;
	}
}

static void *ll_iter_get(const void *_self)
{
	const LinkedListIterator *self = _self;
	if (self && self->current_node) {
		return self->current_node->data;
	}
	return NULL;
}

static void ll_iter_destroy(void *_self)
{
	free(_self);
}

// Define IteratorVTable of LinkedList
static const IteratorVTable g_LinkedListIteratorVTable = {
	.next = ll_iter_next,
	.get = ll_iter_get,
	.is_equal = ll_iter_is_equal,
	.destroy = ll_iter_destroy
}; 

// Container Function
static size_t ll_size(const void *_self) 
{
    const LinkedList_t *self = _self; 
    return self->count;
}

static size_t ll_empty(const void *_self) 
{
	const LinkedList_t *self = _self;
	return self->count == 0;
}

static void ll_clear(void *_self) 
{
	if (!_self) return;
    LinkedList_t *self = _self;
    Node *current = self->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
		free(current->data);
        free(current);
        current = next;
    }
    self->head = NULL;
    self->count = 0;
}

static Iterator *ll_begin(const void *_self) 
{
	const LinkedList_t *self = _self;
	LinkedListIterator *iter = malloc(sizeof(LinkedListIterator));
	iter->vtable = &g_LinkedListIteratorVTable;
	iter->current_node = self->head;
	return (Iterator *)iter;
}

static Iterator *ll_end(const void *_self) 
{
	//const LinkedList_t *self = _self;
	LinkedListIterator *iter = malloc(sizeof(LinkedListIterator));
	iter->vtable = &g_LinkedListIteratorVTable;
	iter->current_node = NULL;
	return (Iterator *)iter;
}

// Define ContainerVTable of LinkedList
static const ContainerVTable g_LinkedListVTable = {
    {
        .size = sizeof(LinkedList_t),
        .ctor = ll_ctor,
		.dtor = ll_dtor
    },
    .size = ll_size,
	.is_empty = ll_empty,
	.clear = ll_clear,
	.begin = ll_begin,
	.end = ll_end
};

static const void *LinkedList = &g_LinkedListVTable;

// LL Function
void LinkedList_add_back(LinkedList_t *self, const void *data) 
{
	if (!self || !data) return;

	void *internal_data = malloc(self->data_size);
	if (!internal_data) return;
	
	memcpy(internal_data, data, self->data_size);
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = internal_data;
    new_node->next = NULL;
	new_node->prev = NULL;
    if(!self->head) {
        self->head = self->tail = new_node;
    } else {
		new_node->prev = self->tail;
        self->tail->next = new_node;
		self->tail = new_node;
    }
    self->count++;
}

void LinkedList_add_front(LinkedList_t *self, const void *data)
{	
	if (!self || !data) return;

	void *internal_data = malloc(self->data_size);
	if (!internal_data) return;
	
	memcpy(internal_data, data, self->data_size);
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return;
    new_node->data = internal_data;
    new_node->next = NULL;
	new_node->prev = NULL;
	if (!self->head) {
		self->head = self->tail = new_node;
	} else {
		self->head->prev = new_node;
		new_node->next = self->head;
		self->head = new_node;
	}
	self->count++;
}

void LinkedList_pop_back(LinkedList_t *self)
{
	if (!self || !self->head) return;
	Node *temp = self->tail;
	self->tail = self->tail->prev;
	if (self->tail)
		self->tail->next = NULL;
	else
		self->head = NULL;
	free(temp->data);
	free(temp);
	self->count--;
}

void LinkedList_pop_front(LinkedList_t *self)
{
	if (!self || !self->head) return;
	Node *temp = self->head;
	self->head = self->head->next;
	if (self->head)
		self->head->prev = NULL;
	else 
		self->tail = NULL;
	free(temp->data);
	free(temp);
	self->count--;
}

LinkedList_t *LinkedList_create(size_t data_size) 
{
	LinkedList_t *self = (LinkedList_t *)new(LinkedList);
	if (self)
		self->data_size = data_size;
	return self;
}

void LinkedList_front(LinkedList_t *_self,void *out_data) 
{
	LinkedList_t *self = _self;
	memcpy(out_data, self->head->data, self->data_size);
}

void LinkedList_back(LinkedList_t *_self,void *out_data)
{
	LinkedList_t *self = _self;
	Node *current = self->tail;
	memcpy(out_data, current->data, self->data_size);
}


Container *LinkedList_get_as_container(const LinkedList_t *self) 
{
	return (Container *)self;
}

void LinkedList_destroy(LinkedList_t *self)
{
	Object_delete((Object *)self);
}

