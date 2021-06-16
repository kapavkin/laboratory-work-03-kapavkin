#ifndef STACK_H
#define STACK_H

#include "array.h"

template <typename T>
class stack : private array<T> {
    size_t _size;

public:
    typedef typename array<T>::template array_iterator<T> iterator;
    typedef typename array<T>::template array_iterator<const T> const_iterator;

    stack(size_t capacity = 0)
        : array<T>::array(capacity)
    {
        _size = 0;
    }

    stack(stack& other)
        : array<T>::array(other)
    {
        _size = other._size;
    }

    size_t size() const
    {
        return _size;
    }

    bool is_empty() const
    {
        return _size == 0;
    }

    void push(T value)
    {
        if (_size == array<T>::_capacity) {
            if (array<T>::_capacity > 0) {
                array<T>::resize(2 * array<T>::_capacity);
            } else {
                array<T>::resize(1);
            }
        }

        array<T>::insert(size(), value);

        _size++;
    }

    T pop()
    {
        T value = array<T>::remove(size() - 1);

        if (--_size <= array<T>::_capacity / 2) {
            array<T>::resize(array<T>::_capacity / 2);
        }

        return value;
    }

    void push_front(T value)
    {
        if (_size == array<T>::_capacity) {
            if (array<T>::_capacity > 0) {
                array<T>::resize(2 * array<T>::_capacity);
            } else {
                array<T>::resize(1);
            }
        }

        array<T>::insert(0, value);

        _size++;
    }

    T pop_front()
    {
        T value = array<T>::remove(0);

        if (--_size <= array<T>::_capacity / 2) {
            array<T>::resize(array<T>::_capacity / 2);
        }

        return value;
    }

    T& operator[](size_t index)
    {
        if (index >= _size) {
            throw std::out_of_range("index out of range");
        }

        return array<T>::operator[](index);
    }

    iterator begin()
    {
        return array<T>::begin();
    }

    iterator end()
    {
        return iterator(array<T>::_array + _size);
    }

    const_iterator begin() const
    {
        return array<T>::begin();
    }

    const_iterator end() const
    {
        return const_iterator(array<T>::_array + _size);
    }
};

#endif
