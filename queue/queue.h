#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

template<typename T>
class queue {
    size_t _capacity, _start, _size;
    T* _circle;

public:
    queue(size_t);
    queue(queue&);
    virtual ~queue();

    size_t capacity() const;
    size_t size() const;
    bool is_empty() const;

    void enqueue(T);
    T dequeue();

    T& operator[](size_t);
};

#endif
