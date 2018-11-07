#pragma once

#include "TVector.h"

#include <stdexcept>
#include <iostream>

template<class Key>
class THeap;

template<class Key>
class Pointer;

template<class Key>
class Pointer {
    friend THeap<Key>;
public:
    Pointer(int _index);
private:
    int index;
};

template<class Key>
class THeap {
public:
    THeap();

    void swap(int ind_1, int ind_2);

    bool is_empty() const;

    Pointer<Key> insert(Key x);

    Key extract_min();

    Key get_min() const;

    int get_size() const;

    void erase(Pointer<Key> ptr);

    void change(Pointer<Key> ptr, Key key);

    template<class Iterator>
    void heapify(Iterator begin, Iterator end);

    void optimize(size_t insertCount, size_t extractCount);
private:
    int dimension;
    int n_elements;

    TVector<Key> a;
    TVector<Pointer<Key>* > pts;

    void sift_up(int index);

    void sift_down(int index);
};

template<class Key>
Pointer<Key>::Pointer(int _index) :
    index(_index)
{}

template<class Key>
THeap<Key>::THeap() {
    dimension = 2;
    n_elements = 0;
}

template<class Key>
bool THeap<Key>::is_empty() const {
    return n_elements == 0;
}

template<class Key>
void THeap<Key>::swap(int ind_1, int ind_2) {
    assert(pts[ind_1]->index == ind_1);
    assert(pts[ind_2]->index == ind_2);

    std::swap(a[ind_1], a[ind_2]);
    std::swap(pts[ind_1], pts[ind_2]);
    std::swap(pts[ind_1]->index, pts[ind_2]->index);
}

template<class Key>
void THeap<Key>::sift_up(int x) {
    while (x > 0 && a[x] < a[(x - 1) / dimension]) {
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
            if (a[curIndex] < a[minIndex])
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
Pointer<Key> THeap<Key>::insert(Key x) {
    Pointer<Key>* new_pointer = new Pointer<Key>(n_elements);

    a.push_back(x);
    pts.push_back(new_pointer);
    sift_up(n_elements);
    n_elements++;
}

template<class Key>
Key THeap<Key>::extract_min() {
    if (is_empty()) {
        throw std::invalid_argument("heap is empty");
    }

    Key value = a[0];
    swap(0, n_elements - 1);
    n_elements--;

    a.pop_back();
    pts.pop_back();

    sift_down(0);

    return value;
}

template<class Key>
Key THeap<Key>::get_min() const {
    return a[0];
}

template<class Key>
int THeap<Key>::get_size() const {
    return n_elements;
}

template<class Key>
void THeap<Key>::erase(Pointer<Key> ptr) {
    int id = ptr->index;
    swap(id, n_elements - 1);
    n_elements--;

    a.pop_back();
    pts.pop_back();

    sift_down(id);
}

template<class Key>
void THeap<Key>::change(Pointer<Key> ptr, Key key) {
    int id = ptr->index;

    a[id] = key;

    sift_up(id);
    sift_down(id);
}

template<class Key>
template<class Iterator>
void THeap<Key>::heapify(Iterator begin, Iterator end) {
    Iterator it = begin;

    while (it != end) {
        Pointer<Key>* new_pointer = new Pointer<Key>(n_elements);
        a.push_back(*it);
        pts.push_back(new_pointer);
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
}
