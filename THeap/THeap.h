#pragma once

#include "TVector.h"

#include <stdexcept>
#include <iostream>
#include <cmath>

template<class Key>
class THeap;

template<class Key>
class THeap {
private:
    class Node;
    class Link;

    class Node {
    friend THeap<Key>;
    private:
        Node(Key _key, int _index);
        ~Node();

        Key value;
        int index;

        Link* user_pointer_copy;
    };

    class Link {
    friend THeap<Key>;
    private:
        Link(Node* node);

        int count_of_users;

        Node* link_node;
    };
public:
    THeap();
    ~THeap();

    template<class Iterator>
    THeap(Iterator begin, Iterator end);

    void swap(int ind_1, int ind_2);
    bool is_empty() const;
    class Pointer;
    Pointer insert(Key x);
    Key extract_min();
    Key get_min() const;
    int get_size() const;
    void erase(Pointer& ptr);
    void change(Pointer ptr, Key key);

    void optimize(size_t insertCount, size_t extractCount);

    class Pointer {
    friend THeap<Key>;
    public:
        ~Pointer();
        Pointer(const Pointer& p); // copying constructor
    private:
        Pointer(Link* link);

        Link* ptr;
    };
private:
    int dimension;
    int n_elements;

    TVector<Node*> a;

    void sift_up(int index);

    void sift_down(int index);
};

template<class Key>
THeap<Key>::THeap() {
    dimension = 2;
    n_elements = 0;
}

template<class Key>
THeap<Key>::Node::Node(Key _key, int _index) {
    value = _key;
    index = _index;
}

template<class Key>
THeap<Key>::Node::~Node() {
    user_pointer_copy->link_node = nullptr;
    user_pointer_copy->count_of_users--;
    if (user_pointer_copy == 0) {
        delete user_pointer_copy;
    }
}

template<class Key>
THeap<Key>::Link::Link(Node* node) {
    link_node = node;
    count_of_users = 2;
}

template<class Key>
THeap<Key>::Pointer::Pointer(Link* link) {
    ptr = link;
}

template<class Key>
THeap<Key>::Pointer::Pointer(const Pointer& p) {
    ptr = p.ptr;
    ptr->count_of_users++;
}

template<class Key>
THeap<Key>::Pointer::~Pointer() {
    ptr->count_of_users--;
    if (ptr->count_of_users == 0) {
        delete ptr;
    }
}

template<class Key>
THeap<Key>::~THeap() {
    for (int i = 0; i < n_elements; ++i) {
        delete a[i];
    }
}

template<class Key>
bool THeap<Key>::is_empty() const {
    return n_elements == 0;
}

template<class Key>
void THeap<Key>::swap(int ind_1, int ind_2) {
    //assert(a[ind_1]->index == ind_1);
    //assert(a[ind_2]->index == ind_2);

    std::swap(a[ind_1], a[ind_2]);
    std::swap(a[ind_1]->index, a[ind_2]->index);
}

template<class Key>
void THeap<Key>::sift_up(int x) {
    if (x >= n_elements) {
        return;
    }
    while (x > 0 && a[x]->value < a[(x - 1) / dimension]->value) {
        swap(x, (x - 1) / dimension);
        x = (x - 1) / dimension;
    }
}

template<class Key>
void THeap<Key>::sift_down(int x) {
    while (true) {
        int minIndex = x;
        for (int i = 0; i < dimension && dimension * x + i + 1 < n_elements; ++i) {
            int curIndex = x * dimension + i + 1;
            if (a[curIndex]->value < a[minIndex]->value)
                minIndex = curIndex;
        }
        if (minIndex == x) {
            break;
        } else {
            swap(x, minIndex);
            x = minIndex;
        }
    }
}

template<class Key>
typename THeap<Key>::Pointer THeap<Key>::insert(Key x) {
    Node* new_node = new Node(x, n_elements);

    Link* new_link = new Link(new_node);
    new_node->user_pointer_copy = new_link;

    a.push_back(new_node);
    n_elements++;
    sift_up(n_elements - 1);

    return Pointer(new_link);
}

template<class Key>
Key THeap<Key>::extract_min() {
    if (is_empty()) {
        throw std::out_of_range("no elements");
    }

    Key value = a[0]->value;

    swap(0, n_elements - 1);
    n_elements--;

    delete a[n_elements];
    a.pop_back();

    sift_down(0);

    return value;
}

template<class Key>
Key THeap<Key>::get_min() const {
    if (is_empty()) {
        throw std::out_of_range("no elements");
    }
    return a[0]->value;
}

template<class Key>
int THeap<Key>::get_size() const {
    return n_elements;
}

template<class Key>
void THeap<Key>::erase(Pointer& pointer) {
    if (pointer.ptr->link_node == nullptr) {
        throw std::out_of_range("no elements");
    }

    int id = pointer.ptr->link_node->index;

    swap(id, n_elements - 1);
    n_elements--;

    delete a[n_elements];
    a.pop_back();

    sift_up(id);
    sift_down(id);
}

template<class Key>
void THeap<Key>::change(Pointer pointer, Key key) {
    if (pointer.ptr->link_node == nullptr) {
        throw std::out_of_range("no such element");
    }

    int id = pointer.ptr->link_node->index;

    a[id]->value = key;

    sift_up(id);
    sift_down(id);
}

template<class Key>
template<class Iterator>
THeap<Key>::THeap(Iterator begin, Iterator end) {
    dimension = 2;
    n_elements = 0;

    Iterator it = begin;

    while (it != end) {
        Node* new_node = new Node(*it, n_elements);
        a.push_back(new_node);
        n_elements++;

        Link* new_link = new Link(new_node);
        new_node->user_pointer_copy = new_link;

        it++;
    }

    for (int i = n_elements - 1; i >= 0; --i)
        sift_down(i);
}

template<class Key>
void THeap<Key>::optimize(size_t insertCount, size_t extractCount) {
    /*
    a = insertCount
    b = extractCount
    a * log(n, k) - insert
    b * k * log(n, k) - extract
    f(k) = (a + b*k) / ln(k)
    f'(k) = (b * ln(k) - (a + b * k) / k) / ln^2(k)
    0: b * ln(k) - (a + b * k) / k = 0
    k * (ln(k) - 1) = a / b
    */

    const double range = (double)insertCount / (double)extractCount;
    int left = 2, right = 1e9;
    while (left + 1 < right) {
        int middle = (left + right) / 2;
        if (middle * (log(middle) - 1) < range)
            left = middle;
        else
            right = middle;
    }

    dimension = left;
}
