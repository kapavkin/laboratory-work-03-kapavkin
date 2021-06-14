#ifndef TREE_H
#define TREE_H

#include <stdexcept>

template <typename K, typename V>
class tree {
    static const bool RED = true;
    static const bool BLACK = false;

    struct node {
        K _key;
        V _value;
        node* _left;
        node* _right;
        size_t _size;
        bool _color;

        node(K, V, size_t, bool);
    };

    node* _root;

    void copy(node*, node*);
    void clear(node*);

    bool is_red(node*) const;

    size_t size(node*) const;
    bool contains(node*, K) const;

    node* put(node*, K, V);
    node* remove(node*, K);

    V& get(node*, K);

    void flip_colors(node*);
    node* rotate_left(node*);
    node* rotate_right(node*);
    node* move_red_left(node*);
    node* move_red_right(node*);
    node* min(node*);
    node* max(node*);
    node* remove_min(node*);
    node* remove_max(node*);
    node* balance(node*);

public:
    tree();
    tree(tree&);
    virtual ~tree();

    size_t size() const;
    bool is_empty() const;
    bool contains(K) const;

    void put(K, V);
    void remove(K);

    V& operator[](K);
};

#endif
