#include "stack.h"

template<typename T>
stack<T>::stack(size_t capacity)
    : array<T>::array(capacity)
{
    _size = 0;
}

template<typename T>
stack<T>::stack(stack& other)
    : array<T>::array(other)
{
    _size = other._size;
}

template<typename T>
size_t stack<T>::size() const
{
    return _size;
}

template<typename T>
bool stack<T>::is_empty() const
{
    return _size == 0;
}

template<typename T>
void stack<T>::push(T value)
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

template<typename T>
T stack<T>::pop()
{
    T value = array<T>::remove(size() - 1);

    if (--_size <= array<T>::_capacity / 2) {
        array<T>::resize(array<T>::_capacity / 2);
    }

    return value;
}

template<typename T>
void stack<T>::push_front(T value)
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

template<typename T>
T stack<T>::pop_front()
{
    T value = array<T>::remove(0);

    if (--_size <= array<T>::_capacity / 2) {
        array<T>::resize(array<T>::_capacity / 2);
    }

    return value;
}

template<typename T>
T& stack<T>::operator[](size_t index)
{
    if (index >= _size) {
        throw std::out_of_range("index out of range");
    }

    return array<T>::operator[](index);
}

template class stack<short>;
template class stack<unsigned short>;
template class stack<int>;
template class stack<unsigned int>;
template class stack<long>;
template class stack<unsigned long>;
template class stack<long long>;
template class stack<unsigned long long>;

template class stack<char>;
template class stack<unsigned char>;

template class stack<float>;
template class stack<double>;
template class stack<long double>;

template class stack<bool>;
