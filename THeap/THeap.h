#pragma once

#include "TVector.h"

#include <stdexcept>
#include <iostream>

template<class Key>
class THeap;

template<class Key>
class THeap {
private:
    class Node {
    friend THeap<Key>;
    private:
        Node(Key _key, int _index);

        Key value;
        int index;
    };
public:
    THeap();

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
    private:
        Pointer(Node* node);

        Node* ptr;
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
THeap<Key>::Pointer::Pointer(Node* node) {
    ptr = node;
}

template<class Key>
bool THeap<Key>::is_empty() const {
    return n_elements == 0;
}

template<class Key>
void THeap<Key>::swap(int ind_1, int ind_2) {
    assert(a[ind_1]->index == ind_1);
    assert(a[ind_2]->index == ind_2);

    std::swap(a[ind_1], a[ind_2]);
    std::swap(a[ind_1]->index, a[ind_2]->index);
}

template<class Key>
void THeap<Key>::sift_up(int x) {
    while (x > 0 && a[x]->value < a[(x - 1) / dimension]->value) {
        swap(x, (x - 1) / dimension);
        x = (x - 1) / dimension;
    }
}

template<class Key>
void THeap<Key>::sift_down(int x) {
    while (1) {
        int minIndex = x;
        for (int i = 0; i < dimension && dimension * x + i + 1 < n_elements; ++i) {
            int curIndex = x * dimension + i + 1;
            if (a[curIndex]->value < a[minIndex]->value)
                minIndex = curIndex;
        }
        if (minIndex == x)
            break;
        else{
            swap(x, minIndex);
            x = minIndex;
        }
    }
}

template<class Key>
typename THeap<Key>::Pointer THeap<Key>::insert(Key x) {
    Node* new_node = new Node(x, a.size());

    a.push_back(new_node);
    sift_up(n_elements);
    n_elements++;

    return Pointer(new_node);
}

template<class Key>
Key THeap<Key>::extract_min() {
    if (is_empty()) {
        throw std::out_of_range("heap is empty");
    }

    Key value = a[0]->value;
    swap(0, n_elements - 1);
    n_elements--;

    a.pop_back();

    sift_down(0);

    return value;
}

template<class Key>
Key THeap<Key>::get_min() const {
    return a[0]->value;
}

template<class Key>
int THeap<Key>::get_size() const {
    return n_elements;
}

template<class Key>
void THeap<Key>::erase(Pointer& ptr) {
    if (ptr.ptr == nullptr) {
        throw std::out_of_range("no such element");
    }

    int id = ptr.ptr->index;
    swap(id, n_elements - 1);
    n_elements--;

    a.pop_back();

    sift_down(id);

    delete ptr.ptr;
    ptr.ptr = nullptr;
}

template<class Key>
void THeap<Key>::change(Pointer ptr, Key key) {
    int id = ptr.ptr->index;

    a[id]->value = key;

    sift_up(id);
    sift_down(id);
}

template<class Key>
template<class Iterator>
THeap<Key>::THeap(Iterator begin, Iterator end) {
    Iterator it = begin;

    while (it != end) {
        Node* new_node = new Node(n_elements);
        a.push_back(new_node);
        n_elements++;

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
    */

    dimension = max((size_t)2, insertCount / extractCount);
}
