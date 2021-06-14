#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <cmath>
#include <stdexcept>

template<typename T>
class array {
protected:
    size_t _capacity;
    T* _array;

public:
    array(size_t = 0);
    array(array&);
    virtual ~array();

    void resize(size_t);

    size_t capacity() const;

    void insert(size_t, T);
    T remove(size_t);

    T& operator[](size_t);
};

#endif
