#include "header/dstruct_delc.h"
#include "../include/dstruct.h"
#include "header/core_internal.h"
#include <stdlib.h>

// Function of Object
void *new(const void *_vtable, ...) 
{
    const ObjectVTable *vtable = _vtable;
    Object *object = calloc(1, vtable->size);
    if (!object) {
        return NULL;
	}
	object->vtable = vtable;
    if (vtable->ctor) {
        va_list ap;
        va_start(ap, _vtable);
        vtable->ctor(object, &ap);
        va_end(ap);
    }
    return object;
}

void Object_delete(Object *self)
{
    if (!self) return;
    const ObjectVTable *vtable = ((Object*)self)->vtable;
    if (vtable->dtor) {
        vtable->dtor(self);
    }
    free(self);
}

// Function of Container
size_t Container_size(const Container *self)
{
    if (!self) return 0;
    const struct ContainerVTable *vtable = self->vtable;
    if (vtable->size) {
        return vtable->size(self);
    }
    return 0;
}

void Container_clear(Container *self) 
{
	if (!self) return;
	const struct ContainerVTable *vtable = self->vtable;
	if (vtable->clear) vtable->clear(self);
}

int Container_is_empty(const Container *self)
{
	if (!self) return -1;
	const struct ContainerVTable *vtable = self->vtable;
	if (vtable->is_empty) return vtable->is_empty(self);
	return -1;
}

struct Iterator *Container_begin(const struct Container *self)
{
	if (self && self->vtable && self->vtable->begin) 
		return self->vtable->begin(self);
	return NULL;
}

struct Iterator *Container_end(const struct Container *self) 
{
	if (self && self->vtable && self->vtable->end)
			return self->vtable->end(self);
	return NULL;
}
// Function of Iterator 
void Iterator_next(struct Iterator *self)
{
	if (self && self->vtable && self->vtable->next)
		self->vtable->next(self);
}

void *Iterator_get(struct Iterator *self)
{
	if (self && self->vtable && self->vtable->get)
		return self->vtable->get(self);
	return NULL;
}

int Iterator_is_equal(const Iterator *self, const Iterator *other) 
{
	if (self && self->vtable && self->vtable->is_equal) {
		return self->vtable->is_equal(self, other);
	}
	return 0;
}

void Iterator_destroy(Iterator *self) 
{
	if (self && self->vtable && self->vtable->destroy) {
		return self->vtable->destroy(self);
	}
}
