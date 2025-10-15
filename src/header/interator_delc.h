#ifndef ITERATOR_DELC_H
#define ITERATOR_DELC_H

struct IteratorVTable {
    void (*next)(void *self);
    void *(*get)(const void *self);
    int (*is_equal)(const void *self, const void *other);
    void (*destroy)(void *self);
};

struct Iterator {
    const struct IteratorVTable *vtable;
};
#endif
