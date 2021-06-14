#include "tree.h"

template <typename K, typename V>
tree<K, V>::node::node(K key, V value, size_t size, bool color)
    : _key(key)
    , _value(value)
    , _left(nullptr)
    , _right(nullptr)
    , _size(size)
    , _color(color)
{
}

template <typename K, typename V>
void tree<K, V>::copy(node* from, node* to)
{
    if (from == nullptr) {
        return;
    }

    to = new node(from->_key, from->_value, from->_size, from->_color);

    copy(from->_left, to->_left);
    copy(from->_right, to->_right);
}

template <typename K, typename V>
void tree<K, V>::clear(node* n)
{
    if (n == nullptr) {
        return;
    }

    clear(n->_left);
    clear(n->_right);

    delete n;
}

template <typename K, typename V>
bool tree<K, V>::is_red(node* n) const
{
    if (n == nullptr) {
        return BLACK;
    } else {
        return n->_color == RED;
    }
}

template <typename K, typename V>
size_t tree<K, V>::size(node* n) const
{
    if (n == nullptr) {
        return 0;
    } else {
        return n->_size;
    }
}

template <typename K, typename V>
bool tree<K, V>::contains(node* n, K key) const
{
    while (n != nullptr) {
        if (key < n->_key) {
            n = n->_left;
        } else if (key > n->_key) {
            n = n->_right;
        } else {
            return true;
        }
    }

    return false;
}

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::put(node* n, K key, V value)
{
    if (n == nullptr) {
        return new node(key, value, 1, RED);
    }

    if (key < n->_key) {
        n->_left = put(n->_left, key, value);
    } else if (key > n->_key) {
        n->_right = put(n->_right, key, value);
    } else {
        n->_value = value;
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

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::remove(node* n, K key)
{
    if (key < n->_key) {
        if (!is_red(n->_left) && !is_red(n->_left->_left)) {
            n = move_red_left(n);
        }
        n->_left = remove(n->_left, key);
    } else {
        if (is_red(n->_left)) {
            n = rotate_right(n);
        }

        if (key == n->_key && n->_right == nullptr) {
            return nullptr;
        }

        if (!is_red(n->_right) && !is_red(n->_right->_left)) {
            n = move_red_right(n);
        }

        if (key == n->_key) {
            node* temp = min(n->_right);
            n->_key = temp->_key;
            n->_value = temp->_value;
            n->_right = remove_min(n->_right);
        } else {
            n->_right = remove(n->_right, key);
        }
    }

    return balance(n);
}

template <typename K, typename V>
V& tree<K, V>::get(node* n, K key)
{
    while (n != nullptr) {
        if (key < n->_key) {
            n = n->_left;
        } else if (key > n->_key) {
            n = n->_right;
        } else {
            return n->_value;
        }
    }
}

template <typename K, typename V>
void tree<K, V>::flip_colors(node* n)
{
    n->_color = !n->_color;
    n->_left->_color = !n->_left->_color;
    n->_right->_color = !n->_right->_color;
}

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::rotate_left(node* n)
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

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::rotate_right(node* n)
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

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::move_red_left(node* n)
{
    flip_colors(n);
    if (is_red(n->_right->_left)) {
        n->_right = rotate_right(n->_right);
        n = rotate_left(n);
        flip_colors(n);
    }

    return n;
}

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::move_red_right(node* n)
{
    flip_colors(n);
    if (is_red(n->_left->_left)) {
        n = rotate_right(n);
        flip_colors(n);
    }

    return n;
}

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::min(node* n)
{
    if (n->_left == nullptr) {
        return n;
    } else {
        return min(n->_left);
    }
}

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::max(node* n)
{
    if (n->_right == nullptr) {
        return n;
    } else {
        return max(n->_right);
    }
}

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::remove_min(node* n)
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

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::remove_max(node* n)
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

template <typename K, typename V>
typename tree<K, V>::node* tree<K, V>::balance(node* n)
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

template <typename K, typename V>
tree<K, V>::tree()
    : _root(nullptr)
{
}

template <typename K, typename V>
tree<K, V>::tree(tree& other)
    : _root(nullptr)
{
    copy(other._root, _root);
}

template <typename K, typename V>
tree<K, V>::~tree()
{
    clear(_root);
}

template <typename K, typename V>
size_t tree<K, V>::size() const
{
    return size(_root);
}

template <typename K, typename V>
bool tree<K, V>::is_empty() const
{
    return _root == nullptr;
}

template <typename K, typename V>
bool tree<K, V>::contains(K key) const
{
    return contains(_root, key);
}

template <typename K, typename V>
void tree<K, V>::put(K key, V value)
{
    _root = put(_root, key, value);
    _root->_color = BLACK;
}

template <typename K, typename V>
void tree<K, V>::remove(K key)
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

template <typename K, typename V>
V& tree<K, V>::operator[](K key)
{
    if (!contains(key)) {
        throw std::invalid_argument("key is not exist");
    }

    return get(_root, key);
}

template class tree<size_t, short>;
template class tree<size_t, unsigned short>;
template class tree<size_t, int>;
template class tree<size_t, unsigned int>;
template class tree<size_t, long>;
template class tree<size_t, unsigned long>;
template class tree<size_t, long long>;
template class tree<size_t, unsigned long long>;

template class tree<size_t, char>;
template class tree<size_t, unsigned char>;

template class tree<size_t, float>;
template class tree<size_t, double>;
template class tree<size_t, long double>;

template class tree<size_t, bool>;

