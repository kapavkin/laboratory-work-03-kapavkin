#ifndef LIST_H
#define LIST_H

#include <iterator>
#include <stdexcept>

template <typename T>
class list {
    struct node {
        T _value;
        node* _next;

        node(T value, node* next = nullptr)
            : _value(value)
            , _next(next)
        {
        }
    };

    size_t _size;
    node* _root;

    template <typename it>
    class list_iterator : public std::iterator<std::input_iterator_tag, it> {
        node* _pointer;

    public:
        list_iterator(node* pointer = nullptr)
            : _pointer(pointer)
        {
        }

        list_iterator(const list_iterator& other)
            : _pointer(other._pointer)
        {
        }

        ~list_iterator()
        {
        }

        bool operator==(const list_iterator& other) const
        {
            return _pointer == other._pointer;
        }

        bool operator!=(const list_iterator& other) const
        {
            return _pointer != other._pointer;
        }

        it& operator*()
        {
            return _pointer->_value;
        }

        const it& operator*() const
        {
            return _pointer->_value;
        }

        list_iterator& operator++()
        {
            _pointer = _pointer->_next;

            return *this;
        }

        list_iterator operator++(int)
        {
            list_iterator copy(*this);

            _pointer = _pointer->_next;

            return copy;
        }
    };

public:
    typedef list_iterator<T> iterator;
    typedef list_iterator<const T> const_iterator;

    list()
        : _size(0)
        , _root(nullptr)
    {
    }

    list(list& other)
    {
        _size = other._size;
        _root = nullptr;

        for (size_t i = 0; i < other._size; i++) {
            insert(i, other[i]);
        }
    }

    virtual ~list()
    {
        for (size_t i = 0; i < _size; i++) {
            remove(0);
        }
    }

    size_t size() const
    {
        return _size;
    }

    bool is_empty() const
    {
        return _root == nullptr;
    }

    void insert(size_t index, T value)
    {
        if (index > _size) {
            throw std::out_of_range("index out of range");
        }

        if (index == 0) {
            if (_root == nullptr) {
                _root = new node(value);
            } else {
                _root = new node(value, _root);
            }

            _size++;

            return;
        }

        node* prev = _root;
        for (size_t i = 0; i < index - 1; i++) {
            prev = prev->_next;
        }

        prev->_next = new node(value, prev->_next);

        _size++;
    }

    T remove(size_t index)
    {
        if (index + 1 > _size) {
            throw std::out_of_range("index out of range");
        }

        if (index == 0) {
            T value = _root->_value;
            node* next = _root->_next;

            delete _root;

            _root = next;

            _size--;

            return value;
        }

        node* prev = _root;
        for (size_t i = 0; i < index - 1; i++) {
            prev = prev->_next;
        }

        T value = prev->_next->_value;
        node* next = prev->_next->_next;

        delete prev->_next;

        prev->_next = next;

        _size--;

        return value;
    }

    T& operator[](size_t index)
    {
        if (index + 1 > _size) {
            throw std::out_of_range("index out of range");
        }

        node* node = _root;
        for (size_t i = 0; i < index; i++) {
            node = node->_next;
        }

        return node->_value;
    }

    iterator begin()
    {
        return iterator(_root);
    }

    iterator end()
    {
        return iterator();
    }

    const_iterator begin() const
    {
        return const_iterator(_root);
    }

    const_iterator end() const
    {
        return const_iterator();
    }
};

#endif
