#ifndef QUEUE_H
#define QUEUE_H

#include <algorithm>
#include <iterator>
#include <stdexcept>

template <typename T>
class queue {
    size_t _capacity, _start, _size;
    T* _circle;

    template <typename it>
    class queue_iterator : public std::iterator<std::input_iterator_tag, it> {
        queue _queue;
        it* _pointer;

    public:
        queue_iterator(const queue& queue, it* pointer = nullptr)
            : _queue(queue)
            , _pointer(pointer)
        {
        }

        queue_iterator(const queue_iterator& other)
            : _queue(other._queue)
            , _pointer(other._pointer)
        {
        }

        ~queue_iterator()
        {
        }

        bool operator==(const queue_iterator& other) const
        {
            return _pointer == other._pointer;
        }

        bool operator!=(const queue_iterator& other) const
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

        queue_iterator& operator++()
        {
            if (_pointer + 1 == _queue._circle + _queue._capacity) {
                _pointer = _queue._circle;
            } else {
                _pointer++;
            }

            return *this;
        }

        queue_iterator operator++(int)
        {
            queue_iterator copy(*this);

            if (_pointer + 1 == _queue._circle + _queue._capacity) {
                _pointer = _queue._circle;
            } else {
                _pointer++;
            }

            return copy;
        }
    };

public:
    typedef queue_iterator<T> iterator;
    typedef queue_iterator<const T> const_iterator;

    queue(size_t capacity)
        : _capacity(capacity + 1)
        , _circle(new T[capacity + 1])
        , _start(0)
        , _size(0)
    {
    }

    queue(const queue& other)
        : _capacity(other._capacity)
        , _circle(new T[_capacity])
        , _start(other._start)
        , _size(other._size)
    {
        std::copy(other._circle, other._circle + _capacity, _circle);
    }

    virtual ~queue()
    {
        delete[] _circle;
    }

    size_t capacity() const
    {
        return _capacity;
    }

    size_t size() const
    {
        return _size;
    }

    bool is_empty() const
    {
        return _size == 0;
    }

    void enqueue(T value)
    {
        if (_size == _capacity) {
            throw std::out_of_range("index out of range");
        }

        _circle[(_start + _size++) % _capacity] = value;
    }

    T dequeue()
    {
        if (_size == 0) {
            throw std::out_of_range("index out of range");
        }

        T value = _circle[_start];

        _start = (_start + 1) % _capacity;
        _size--;

        return value;
    }

    T& operator[](size_t index)
    {
        if (index >= _size) {
            throw std::out_of_range("index out of range");
        }

        return _circle[(_start + index) % _capacity];
    }

    iterator begin()
    {
        return iterator(*this, _circle + _start);
    }

    iterator end()
    {
        return iterator(*this, _circle + (_start + _size) % _capacity);
    }

    const_iterator begin() const
    {
        return const_iterator(*this, _circle + _start);
    }

    const_iterator end() const
    {
        return const_iterator(*this, _circle + (_start + _size) % _capacity);
    }
};

#endif
