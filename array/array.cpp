#include "array.h"

template<typename T>
array<T>::array(size_t capacity)
{
    _capacity = capacity;
    _array = new T[capacity];
}

template<typename T>
array<T>::array(array& other)
{
    _capacity = other._capacity;

    _array = new T[_capacity];
    for (size_t i = 0; i < other._capacity; i++) {
        _array[i] = other._array[i];
    }
}

template<typename T>
array<T>::~array()
{
    delete[] _array;
}

template<typename T>
void array<T>::resize(size_t capacity)
{
    T* array = new T[capacity];

    std::copy(_array, _array + std::min(_capacity, capacity), array);

    delete[] _array;

    _array = new T[capacity];

    std::copy(array, array + capacity, _array);

    delete[] array;

    _capacity = capacity;
}

template<typename T>
size_t array<T>::capacity() const
{
    return _capacity;
}

template<typename T>
void array<T>::insert(size_t index, T value)
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

template<typename T>
T array<T>::remove(size_t index)
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

template<typename T>
T& array<T>::operator[](size_t index)
{
    if (index >= _capacity) {
        throw std::out_of_range("index out of range");
    }

    return _array[index];
}

template class array<short>;
template class array<unsigned short>;
template class array<int>;
template class array<unsigned int>;
template class array<long>;
template class array<unsigned long>;
template class array<long long>;
template class array<unsigned long long>;

template class array<char>;
template class array<unsigned char>;

template class array<float>;
template class array<double>;
template class array<long double>;

template class array<bool>;
