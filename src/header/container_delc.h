#ifndef CONTAINER_DELC_H
#define CONTAINER_DELC_H
#include "interator_delc.h"
#include "object_delc.h"

struct ContainerVTable {
    struct ObjectVTable base;
    size_t (*size)(const void *self);
	size_t (*is_empty)(const void *self);
    void (*clear)(void *self);
    struct Iterator *(*begin)(const void *self);
	struct Iterator *(*end)(const void *self);
};

struct Container {
    const struct ContainerVTable *vtable;
};
#endif
