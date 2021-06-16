#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <cmath>
#include <stdexcept>

template <typename T>
class array {
protected:
    size_t _capacity;
    T* _array;

    template <typename it>
    class array_iterator : public std::iterator<std::input_iterator_tag, it> {
        it* _pointer;

    public:
        array_iterator(it* pointer = nullptr)
            : _pointer(pointer)
        {
        }

        array_iterator(const array_iterator& other)
            : _pointer(other._pointer)
        {
        }

        ~array_iterator()
        {
        }

        bool operator==(const array_iterator& other) const
        {
            return _pointer == other._pointer;
        }

        bool operator!=(const array_iterator& other) const
        {
            return _pointer != other._pointer;
        }

        it& operator*()
        {
            return *_pointer;
        }

        const it& operator*() const
        {
            return *_pointer;
        }

        array_iterator& operator++()
        {
            _pointer++;

            return *this;
        }

        array_iterator operator++(int)
        {
            array_iterator copy(*this);

            _pointer++;

            return copy;
        }
    };

public:
    typedef array_iterator<T> iterator;
    typedef array_iterator<const T> const_iterator;

    array(size_t capacity = 0)
    {
        _capacity = capacity;
        _array = new T[capacity];
    }

    array(array& other)
    {
        _capacity = other._capacity;
        _array = new T[_capacity];

        std::copy(other._array, other._array + _capacity, _array);
    }

    virtual ~array()
    {
        delete[] _array;
    }

    void resize(size_t capacity)
    {
        T* array = new T[capacity];

        std::copy(_array, _array + std::min(_capacity, capacity), array);

        delete[] _array;

        _array = new T[capacity];

        std::copy(array, array + capacity, _array);

        delete[] array;

        _capacity = capacity;
    }

    size_t capacity() const
    {
        return _capacity;
    }

    void insert(size_t index, T value)
    {
        if (index >= _capacity) {
            throw std::out_of_range("index out of range");
        }

        T* array = new T[_capacity];

        std::copy(_array, _array + index, array);

        array[index] = value;

        std::copy(_array + index, _array + _capacity - 1, array + index + 1);

        delete[] _array;

        _array = new T[_capacity];

        std::copy(array, array + _capacity, _array);

        delete[] array;
    }

    T remove(size_t index)
    {
        if (index >= _capacity) {
            throw std::out_of_range("index out of range");
        }

        T value = _array[index];

        T* array = new T[_capacity];

        std::copy(_array, _array + index, array);
        std::copy(_array + index + 1, _array + _capacity, array + index);

        delete[] _array;

        _array = new T[_capacity];

        std::copy(array, array + _capacity, _array);

        delete[] array;

        return value;
    }

    T& operator[](size_t index)
    {
        if (index >= _capacity) {
            throw std::out_of_range("index out of range");
        }

        return _array[index];
    }

    iterator begin()
    {
        return iterator(_array);
    }

    iterator end()
    {
        return iterator(_array + _capacity);
    }

    const_iterator begin() const
    {
        return const_iterator(_array);
    }

    const_iterator end() const
    {
        return const_iterator(_array + _capacity);
    }
};

#endif
