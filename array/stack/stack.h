#ifndef STACK_H
#define STACK_H

#include "array.h"

template<typename T>
class stack : private array<T> {
    size_t _size;

public:
    stack(size_t = 0);
    stack(stack&);

    size_t size() const;
    bool is_empty() const;

    void push(T);
    T pop();

    void push_front(T);
    T pop_front();

    T& operator[](size_t);
};

#endif
