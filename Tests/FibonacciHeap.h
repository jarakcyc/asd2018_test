#pragma once

#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

template<class Key>
class FibonacciHeap {
private:
    class Link;
public:
    class Pointer;

    FibonacciHeap();
    bool is_empty() const;
    Pointer insert(Key key);
    Key get_min() const;
    Key extract_min();
    void merge(FibonacciHeap &otherHeap);
    Key decrease(Pointer pointer, Key key);
    Key erase(Pointer& pointer);

    /// For Testing
    vector<int> get_roots();
    ///

    class Pointer {
    public:
        Pointer();
        ~Pointer();
        Pointer(const Pointer& p);
    friend FibonacciHeap<Key>;
    private:
        Pointer(Link* _ptr);

        Link* ptr;
    };
private:
    class Node;

    class Link {
    friend FibonacciHeap<Key>;
    private:
        Link(Node* node);

        int count_of_users;

        Node* link_node;
    };

    class Node {
        friend FibonacciHeap<Key>;
    private:
        Node();
        Node(Key _key);
        ~Node();

        Node* parent;
        Node* right_brother;
        Node* left_brother;
        Node* first_son;

        Key value;

        int degree;

        bool mark;

        Link* user_pointer_copy;

        void join(Node*& node);
    };

    Node* root;
    Node* last_root;
    Node* min_node;

    void setmin(Node*& node, Node* new_node);
    void set_right_brother(Node*& node, Node* brother);
    void set_left_brother(Node*& node, Node* brother);
    void join(Node*& left, Node*& right);

    void consolidate();

    void cut(Node* node);
    void cascading_cut(Node* node);

    void clear(Node* node);

    const int MAX_SIZE = 30;
};

template<class Key>
vector<int> FibonacciHeap<Key>::get_roots() {
    vector<int> res;
    Node* ver = root;
    while (ver != nullptr) {
        res.push_back(ver->degree);
        ver = ver->right_brother;
    }
    return res;
}

template<class Key>
FibonacciHeap<Key>::FibonacciHeap() {
    root = nullptr;
    last_root = nullptr;
    min_node = nullptr;
}

template<class Key>
FibonacciHeap<Key>::Node::Node(Key _key) {
    value = _key;
    degree = 0;

    mark = false;

    parent = nullptr;
    right_brother = nullptr;
    left_brother = nullptr;
    first_son = nullptr;
}

template<class Key>
FibonacciHeap<Key>::Node::Node() {
    value = 0;
    degree = 0;
    mark = false;

    parent = nullptr;
    right_brother = nullptr;
    left_brother = nullptr;
    first_son = nullptr;
}

template<class Key>
FibonacciHeap<Key>::Node::~Node() {
    user_pointer_copy->link_node = nullptr;
    user_pointer_copy->count_of_users--;
    if (user_pointer_copy->count_of_users == 0) {
        delete user_pointer_copy;
    }
}

template<class Key>
FibonacciHeap<Key>::Link::Link(Node* node) {
    link_node = node;
    count_of_users = 2;
}

template<class Key>
FibonacciHeap<Key>::Pointer::Pointer() {
    ptr = nullptr;
}

template<class Key>
FibonacciHeap<Key>::Pointer::~Pointer() {
    ptr->count_of_users--;
    if (ptr->count_of_users == 0) {
        delete ptr;
    }
}

template<class Key>
FibonacciHeap<Key>::Pointer::Pointer(Link* _ptr) {
    ptr = _ptr;
}

template<class Key>
FibonacciHeap<Key>::Pointer::Pointer(const Pointer& p) {
    ptr = p.ptr;
    ptr->count_of_users++;
}

template<class Key>
void FibonacciHeap<Key>::set_right_brother(Node*& node, Node* brother) {
    if (node == nullptr) {
        return;
    }
    node->right_brother = brother;
}

template<class Key>
void FibonacciHeap<Key>::set_left_brother(Node*& node, Node* brother) {
    if (node == nullptr) {
        return;
    }
    node->left_brother = brother;
}

template<class Key>
void FibonacciHeap<Key>::join(Node*& left, Node*& right) {
    if (left->value > right->value) {
        swap(left, right);
    }

    if (left->first_son == nullptr) {
        left->first_son = right;

        right->parent = left;
    } else {
        set_right_brother(right, left->first_son);
        set_left_brother(left->first_son, right);

        left->first_son = right;

        right->parent = left;
    }

    right = nullptr;

    left->degree++;
}

template<class Key>
void FibonacciHeap<Key>::setmin(Node*& node, Node* new_node) {
    if (node == nullptr) {
        node = new_node;
    }
    if (node->value > new_node->value) {
        node = new_node;
    }
}

template<class Key>
bool FibonacciHeap<Key>::is_empty() const {
    return (root == nullptr);
}

template<class Key>
void FibonacciHeap<Key>::clear(Node* node) {
    if (node == nullptr) {
        return;
    }
    clear(node->first_son);
    clear(node->right_brother);
    delete node;
}

template<class Key>
void FibonacciHeap<Key>::merge(FibonacciHeap &otherHeap) {
    if (otherHeap.root == nullptr)
        return;

    if (root == nullptr) {
        root = otherHeap.root;
        last_root = otherHeap.last_root;
        min_node = otherHeap.min_node;
    } else {
        set_right_brother(last_root, otherHeap.root);
        set_left_brother(otherHeap.root, last_root);

        last_root = otherHeap.last_root;

        if (min_node == nullptr ||
            otherHeap.root != nullptr && otherHeap.min_node->value < min_node->value) {
            min_node = otherHeap.min_node;
        }
    }

    otherHeap.root = nullptr;
    otherHeap.last_root = nullptr;
    otherHeap.min_node = nullptr;
}

template<class Key>
typename FibonacciHeap<Key>::Pointer FibonacciHeap<Key>::insert(Key key) {
    FibonacciHeap<Key> new_heap;

    new_heap.root = new Node(key);
    new_heap.min_node = new_heap.root;
    new_heap.last_root = new_heap.root;

    Link* new_link = new Link(new_heap.root);
    new_heap.root->user_pointer_copy = new_link;

    merge(new_heap);

    return Pointer(new_link);
}

template<class Key>
Key FibonacciHeap<Key>::get_min() const {
    if (is_empty()) {
        throw out_of_range("no elements");
    }
    return min_node->value;
}

template<class Key>
Key FibonacciHeap<Key>::extract_min() {
    if (is_empty()) {
        throw out_of_range("no elements");
    }
    Key res = get_min();

    FibonacciHeap<Key> children;

    children.root = min_node->first_son;

    while (children.root != nullptr) {
        children.root->parent = nullptr;

        setmin(children.min_node, children.root);
        children.last_root = children.root;

        children.root = children.root->right_brother;
    }

    Node* vertex = root;
    if (min_node != vertex) {
        while (vertex->right_brother != min_node) {
            vertex = vertex->right_brother;
        }
        set_right_brother(vertex, min_node->right_brother);
        set_left_brother(min_node->right_brother, vertex);

        if (min_node == last_root) {
            last_root = vertex;
        }
    }
    else {
        root = vertex->right_brother;

        if (min_node == last_root) {
            last_root = vertex->right_brother;
        }
    }

    children.root = min_node->first_son;

    delete min_node;
    min_node = nullptr;

    merge(children);

    consolidate();

    return res;
}

template<class Key>
void FibonacciHeap<Key>::consolidate() {
    Node** array = new Node*[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; ++i)
        array[i] = nullptr;

    Node* vertex = root;

    while (vertex != nullptr) {
        Node* next = vertex->right_brother;

        set_right_brother(vertex, nullptr);
        set_left_brother(vertex, nullptr);

        while (array[vertex->degree] != nullptr) {
            join(vertex, array[vertex->degree]);
        }

        array[vertex->degree] = vertex;

        vertex = next;
    }

    root = nullptr;
    min_node = nullptr;
    last_root = nullptr;

    for (int i = 0; i < MAX_SIZE; ++i) {
        if (array[i] != nullptr) {
            setmin(min_node, array[i]);

            if (root == nullptr) {
                root = array[i];
                last_root = array[i];
            } else {
                set_right_brother(last_root, array[i]);
                set_left_brother(array[i], last_root);
                last_root = array[i];
            }
        }
    }

    delete[] array;
}

template<class Key>
void FibonacciHeap<Key>::cut(Node* node) {
    if (node == nullptr || node->parent == nullptr) {
        return;
    }
    node->mark = false;

    Node* par = node->parent;
    node->parent = nullptr;

    if (par->first_son == node) {
        par->first_son = node->right_brother;
    }

    set_right_brother(node->left_brother, node->right_brother);
    set_left_brother(node->right_brother, node->left_brother);
    node->right_brother = nullptr;
    node->left_brother = nullptr;

    set_right_brother(last_root, node);
    set_left_brother(node, last_root);
    last_root = node;

    if (min_node->value > node->value) {
        min_node = node;
    }
}

template<class Key>
void FibonacciHeap<Key>::cascading_cut(Node* node) {
    while (node != nullptr && node->mark) {
        Node* par = node->parent;
        cut(node);
        node = par;
    }
    if (node != nullptr) {
        node->mark = true;
    }
}

template<class Key>
Key FibonacciHeap<Key>::decrease(Pointer pointer, Key key) {
    if (pointer.ptr->link_node == nullptr) {
        throw std::out_of_range("no such element");
    }

    Node* node = pointer.ptr->link_node;
    Key res = node->value;

    if (node->value < key) {
        throw std::invalid_argument("key must be less then value in node");
    }

    node->value = key;

    Node* par = node->parent;

    if (par == nullptr) {
        if (min_node->value > node->value) {
            min_node = node;
        }
        return res;
    }

    cut(node);

    if (par->mark == true) {
        cascading_cut(par);
    } else {
        par->mark = true;
    }

    return res;
}

template<class Key>
Key FibonacciHeap<Key>::erase(Pointer& pointer) {
    if (pointer.ptr->link_node == nullptr) {
        throw std::out_of_range("no such element");
    }

    Key res = decrease(pointer, min_node->value);
    min_node = pointer.ptr->link_node;
    extract_min();

    return res;
}
