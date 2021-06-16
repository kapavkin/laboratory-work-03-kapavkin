#ifndef TREE_H
#define TREE_H

#include <iterator>
#include <stdexcept>
#include <utility>

template <typename K, typename V>
class tree {
    static const bool RED = true;
    static const bool BLACK = false;

    struct node {
        std::pair<K, V> _cortege;
        node* _left;
        node* _right;
        size_t _size;
        bool _color;

        node(std::pair<K, V> cortege, size_t size, bool color)
            : _cortege(cortege)
            , _left(nullptr)
            , _right(nullptr)
            , _size(size)
            , _color(color)
        {
        }
    };

    node* _root;

    static void copy(node* from, node* to)
    {
        if (from == nullptr) {
            return;
        }

        to = new node(from->_cortege, from->_size, from->_color);

        copy(from->_left, to->_left);
        copy(from->_right, to->_right);
    }

    static void clear(node* n)
    {
        if (n == nullptr) {
            return;
        }

        clear(n->_left);
        clear(n->_right);

        delete n;
    }

    static bool is_red(node* n)
    {
        if (n == nullptr) {
            return BLACK;
        } else {
            return n->_color == RED;
        }
    }

    static size_t size(node* n)
    {
        if (n == nullptr) {
            return 0;
        } else {
            return n->_size;
        }
    }

    static bool contains(node* n, K key)
    {
        while (n != nullptr) {
            if (key < n->_cortege.first) {
                n = n->_left;
            } else if (key > n->_cortege.first) {
                n = n->_right;
            } else {
                return true;
            }
        }

        return false;
    }

    static node* put(node* n, K key, V value)
    {
        if (n == nullptr) {
            return new node(std::make_pair(key, value), 1, RED);
        }

        if (key < n->_cortege.first) {
            n->_left = put(n->_left, key, value);
        } else if (key > n->_cortege.first) {
            n->_right = put(n->_right, key, value);
        } else {
            n->_cortege.second = value;
        }

        if (is_red(n->_right) && !is_red(n->_left)) {
            n = rotate_left(n);
        }

        if (is_red(n->_left) && is_red(n->_left->_left)) {
            n = rotate_right(n);
        }

        if (is_red(n->_left) && is_red(n->_right)) {
            flip_colors(n);
        }

        n->_size = size(n->_left) + size(n->_right) + 1;

        return n;
    }

    static node* remove(node* n, K key)
    {
        if (key < n->_cortege.first) {
            if (!is_red(n->_left) && !is_red(n->_left->_left)) {
                n = move_red_left(n);
            }
            n->_left = remove(n->_left, key);
        } else {
            if (is_red(n->_left)) {
                n = rotate_right(n);
            }

            if (key == n->_cortege.first && n->_right == nullptr) {
                return nullptr;
            }

            if (!is_red(n->_right) && !is_red(n->_right->_left)) {
                n = move_red_right(n);
            }

            if (key == n->_cortege.first) {
                node* temp = min(n->_right);
                n->_cortege.first = temp->_cortege.first;
                n->_cortege.second = temp->_cortege.second;
                n->_right = remove_min(n->_right);
            } else {
                n->_right = remove(n->_right, key);
            }
        }

        return balance(n);
    }

    static V& get(node* n, K key)
    {
        while (n != nullptr) {
            if (key < n->_cortege.first) {
                n = n->_left;
            } else if (key > n->_cortege.first) {
                n = n->_right;
            } else {
                return n->_cortege.second;
            }
        }
    }

    static void flip_colors(node* n)
    {
        n->_color = !n->_color;
        n->_left->_color = !n->_left->_color;
        n->_right->_color = !n->_right->_color;
    }

    static node* rotate_left(node* n)
    {
        node* temp = n->_right;
        n->_right = temp->_left;
        temp->_left = n;
        temp->_color = temp->_left->_color;
        temp->_left->_color = RED;
        temp->_size = n->_size;
        n->_size = size(n->_left) + size(n->_right) + 1;

        return temp;
    }

    static node* rotate_right(node* n)
    {
        node* temp = n->_left;
        n->_left = temp->_right;
        temp->_right = n;
        temp->_color = temp->_right->_color;
        temp->_right->_color = RED;
        temp->_size = n->_size;
        n->_size = size(n->_left) + size(n->_right) + 1;

        return temp;
    }

    static node* move_red_left(node* n)
    {
        flip_colors(n);
        if (is_red(n->_right->_left)) {
            n->_right = rotate_right(n->_right);
            n = rotate_left(n);
            flip_colors(n);
        }

        return n;
    }

    static node* move_red_right(node* n)
    {
        flip_colors(n);
        if (is_red(n->_left->_left)) {
            n = rotate_right(n);
            flip_colors(n);
        }

        return n;
    }

    static node* min(node* n)
    {
        if (n->_left == nullptr) {
            return n;
        } else {
            return min(n->_left);
        }
    }

    static node* max(node* n)
    {
        if (n->_right == nullptr) {
            return n;
        } else {
            return max(n->_right);
        }
    }

    static node* remove_min(node* n)
    {
        if (n->_left == nullptr) {
            return nullptr;
        }

        if (!is_red(n->_left) && !is_red(n->_left->_left)) {
            n = move_red_left(n);
        }

        n->_left = remove_min(n->_left);

        return balance(n);
    }

    static node* remove_max(node* n)
    {
        if (is_red(n->_left)) {
            n = rotate_right(n);
        }

        if (n->_right == nullptr) {
            return nullptr;
        }

        if (!is_red(n->_right) && !is_red(n->_right->_left)) {
            n = move_red_right(n);
        }

        n->_right = remove_max(n->_right);

        return balance(n);
    }

    static node* balance(node* n)
    {
        if (is_red(n->_right) && !is_red(n->_left)) {
            n = rotate_left(n);
        }

        if (is_red(n->_left) && is_red(n->_left->_left)) {
            n = rotate_right(n);
        }

        if (is_red(n->_left) && is_red(n->_right)) {
            flip_colors(n);
        }

        n->_size = size(n->_left) + size(n->_right) + 1;

        return n;
    }

    template <typename it>
    class tree_iterator : public std::iterator<std::input_iterator_tag, it> {
        size_t _size, _index;
        node** _container;

        size_t fill_container(node* pointer, size_t index)
        {
            if (pointer == nullptr) {
                return index;
            }

            index = fill_container(pointer->_left, index);

            _container[index] = pointer;

            return fill_container(pointer->_right, index + 1);
        }

    public:
        tree_iterator(node* pointer = nullptr)
            : _size(tree<K, V>::size(pointer))
            , _index(0)
            , _container(new node*[tree<K, V>::size(pointer) + 1])
        {
            fill_container(pointer, 0);
            _container[_size] = nullptr;
        }

        tree_iterator(const tree_iterator& other)
            : _size(other._size)
            , _index(other._index)
            , _container(new node*[other._size + 1])
        {
            std::copy(other._container, other._container + _size + 1, _container);
        }

        ~tree_iterator()
        {
            delete[] _container;
        }

        bool operator==(const tree_iterator& other) const
        {
            return _container[_index] == other._container[other._index];
        }

        bool operator!=(const tree_iterator& other) const
        {
            return _container[_index] != other._container[other._index];
        }

        it& operator*()
        {
            return _container[_index]->_cortege;
        }

        const it& operator*() const
        {
            return _container[_index]->_cortege;
        }

        tree_iterator& operator++()
        {
            _index++;

            return *this;
        }

        tree_iterator operator++(int)
        {
            tree_iterator copy(*this);

            _index++;

            return copy;
        }
    };

public:
    typedef tree_iterator<std::pair<K, V>> iterator;
    typedef tree_iterator<const std::pair<K, V>> const_iterator;

    tree()
        : _root(nullptr)
    {
    }

    tree(tree& other)
        : _root(nullptr)
    {
        copy(other._root, _root);
    }

    virtual ~tree()
    {
        clear(_root);
    }

    size_t size() const
    {
        return size(_root);
    }

    bool is_empty() const
    {
        return _root == nullptr;
    }

    bool contains(K key) const
    {
        return contains(_root, key);
    }

    void put(K key, V value)
    {
        _root = put(_root, key, value);
        _root->_color = BLACK;
    }

    void remove(K key)
    {
        if (!contains(key)) {
            return;
        }

        if (!is_red(_root->_left) && !is_red(_root->_right)) {
            _root->_color = RED;
        }

        _root = remove(_root, key);

        if (!is_empty()) {
            _root->_color = BLACK;
        }
    }

    V& operator[](K key)
    {
        if (!contains(key)) {
            throw std::invalid_argument("key is not exist");
        }

        return get(_root, key);
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
