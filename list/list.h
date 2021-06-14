#ifndef LIST_H
#define LIST_H

#include <stdexcept>

template<typename T>
class list {
    struct node {
        T _value;
        node* _next;

        node(T, node* = nullptr);
    };

    size_t _size;
    node* _root;

public:
    list();
    list(list&);
    virtual ~list();

    size_t size() const;
    bool is_empty() const;

    void insert(size_t, T);
    T remove(size_t);

    T& operator[](size_t);
};

#endif
