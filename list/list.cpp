#include "list.h"

template<typename T>
list<T>::node::node(T value, node* next)
    : _value(value)
    , _next(next)
{
}

template<typename T>
list<T>::list()
    : _size(0)
    , _root(nullptr)
{
}

template<typename T>
list<T>::list(list& other)
{
    _size = other._size;
    _root = nullptr;

    for (size_t i = 0; i < other._size; i++) {
        insert(i, other[i]);
    }
}

template<typename T>
list<T>::~list()
{
    for (size_t i = 0; i < _size; i++) {
        remove(0);
    }
}

template<typename T>
size_t list<T>::size() const
{
    return _size;
}

template<typename T>
bool list<T>::is_empty() const
{
    return _root == nullptr;
}

template<typename T>
void list<T>::insert(size_t pos, T value)
{
    if (pos > _size) {
        throw std::out_of_range("index out of range");
    }

    if (pos == 0) {
        if (_root == nullptr) {
            _root = new node(value);
        } else {
            _root = new node(value, _root);
        }

        _size++;

        return;
    }

    node* prev = _root;
    for (size_t i = 0; i < pos - 1; i++) {
        prev = prev->_next;
    }

    prev->_next = new node(value, prev->_next);

    _size++;
}

template<typename T>
T list<T>::remove(size_t pos)
{
    if (pos + 1 > _size) {
        throw std::out_of_range("index out of range");
    }

    if (pos == 0) {
        T value = _root->_value;
        node* next = _root->_next;

        delete _root;

        _root = next;

        _size--;

        return value;
    }

    node* prev = _root;
    for (size_t i = 0; i < pos - 1; i++) {
        prev = prev->_next;
    }

    T value = prev->_next->_value;
    node* next = prev->_next->_next;

    delete prev->_next;

    prev->_next = next;

    _size--;

    return value;
}

template<typename T>
T& list<T>::operator[](size_t pos)
{
    if (pos + 1 > _size) {
        throw std::out_of_range("index out of range");
    }

    node* node = _root;
    for (size_t i = 0; i < pos; i++) {
        node = node->_next;
    }

    return node->_value;
}

template class list<short>;
template class list<unsigned short>;
template class list<int>;
template class list<unsigned int>;
template class list<long>;
template class list<unsigned long>;
template class list<long long>;
template class list<unsigned long long>;

template class list<char>;
template class list<unsigned char>;

template class list<float>;
template class list<double>;
template class list<long double>;

template class list<bool>;
