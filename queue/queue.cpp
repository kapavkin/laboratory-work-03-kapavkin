#include "queue.h"

template<typename T>
queue<T>::queue(size_t capacity)
{
    _capacity = capacity;
    _circle = new T[capacity];
    _start = 0;
    _size = 0;
}

template<typename T>
queue<T>::queue(queue& other)
{
    _capacity = other._capacity;

    _circle = new T[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _circle[i] = other._circle[i];
    }

    _start = other._start;
    _size = other._size;
}

template<typename T>
queue<T>::~queue()
{
    delete[] _circle;
}

template<typename T>
size_t queue<T>::capacity() const
{
    return _capacity;
}

template<typename T>
size_t queue<T>::size() const
{
    return _size;
}

template<typename T>
bool queue<T>::is_empty() const
{
    return _size == 0;
}

template<typename T>
void queue<T>::enqueue(T value)
{
    if (_size == _capacity) {
        throw std::out_of_range("index out of range");
    }

    _circle[(_start + _size++) % _capacity] = value;
}

template<typename T>
T queue<T>::dequeue()
{
    if (_size == 0) {
        throw std::out_of_range("index out of range");
    }

    T value = _circle[_start];

    _start = (_start + 1) % _capacity;
    _size--;

    return value;
}

template<typename T>
T& queue<T>::operator[](size_t pos)
{
    if (pos + 1 > _size) {
        throw std::out_of_range("index out of range");
    }

    return _circle[(_start + pos) % _capacity];
}

template class queue<short>;
template class queue<unsigned short>;
template class queue<int>;
template class queue<unsigned int>;
template class queue<long>;
template class queue<unsigned long>;
template class queue<long long>;
template class queue<unsigned long long>;

template class queue<char>;
template class queue<unsigned char>;

template class queue<float>;
template class queue<double>;
template class queue<long double>;

template class queue<bool>;
