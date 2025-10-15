#ifndef CONTAINER_H
#define CONTAINER_H

#include "iterator.h"
#include "object.h"

typedef struct ContainerVTable ContainerVTable;
typedef struct Container Container;

size_t Container_size(const Container *self);
int Container_is_empty(const Container *self);
void Container_clear(Container *self);

Iterator *Container_begin(const Container *self);
Iterator *Container_end(const Container *self);
#endif

