#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct IteratorVTable IteratorVTable;
typedef struct Iterator Iterator;

void Iterator_next(Iterator *self);
void *Iterator_get(Iterator *self);
void Iterator_destroy(Iterator *self);
int Iterator_is_equal(const Iterator *self,const Iterator *other);
#endif
