#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "container.h"


typedef struct LinkedList LinkedList_t;

LinkedList_t *LinkedList_create(size_t data_size);
void LinkedList_destroy(LinkedList_t *self);

void LinkedList_front(LinkedList_t *self, void *out_data);
void LinkedList_back(LinkedList_t *self, void *out_data);
void LinkedList_add_back(LinkedList_t *self, const void *data);
void LinkedList_add_front(LinkedList_t *self, const void *data);
void LinkedList_pop_front(LinkedList_t *self);
void LinkedList_pop_back(LinkedList_t *self);

Container *LinkedList_get_as_container(const LinkedList_t *self);


#define LinkedList_front_as(_self, type)\
	({\
		LinkedList_t *self = _self;\
		type temp_value;\
		LinkedList_front(self, &temp_value);\
		temp_value;\
	 })
#define LinkedList_back_as(_self, type)\
	({\
	    LinkedList_t *self = _self\
		type = temp_value;\
	    LinkedList_back(self, &temp_value);\
		temp_value;\
	})
#define LinkedList_push_back(_self, type, ...)\
	({\
	   LinkedList_t *self = _self;\
	   LinkedList_add_back(self, &(type){__VA_ARGS__});\
	 })
#define LinkedList_push_front(_self, type, ...)\
	({\
	   LinkedList_t *self = _self;\
	   LinkedList_add_front(self, &(type){__VA_ARGS__});\
	})
#define LinkedList_begin(_self) Container_begin(LinkedList_get_as_container(_self))
#define LinkedList_end(_self) Container_end(LinkedList_get_as_container(_self))
#define LinkedList_size(_self) Container_size(LinkedList_get_as_container(_self))
#define LinkedList_is_empty(_self) Container_is_empty(LinkedList_get_as_container(_self))
#define LinkedList_clear(_self) Container_clear(LinkedList_get_as_container(_self))
#endif
