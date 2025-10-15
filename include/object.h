#ifndef OBJECT_H
#define OBJECT_H

#include <stddef.h>
#include <stdarg.h>

typedef struct ObjectVTable ObjectVTable;
typedef struct Object Object;

void Object_delete(Object *self);
#endif
