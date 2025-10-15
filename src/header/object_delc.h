#ifndef OBJECT_DELC_H
#define OBJECT_DELC_H

#include <stddef.h>
#include <stdarg.h>

struct ObjectVTable {
    size_t size;
    void *(*ctor)(void *self, va_list *app);
    void (*dtor)(void *self);
};

struct Object {
    const struct ObjectVTable *vtable;
};
#endif
