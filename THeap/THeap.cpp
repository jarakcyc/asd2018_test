#pragma once

#include "IHeap.h"

#include <stdexcept>

template<class Key>
THeap<Key>::THeap(){
    n_elements = 0;
}

template<class Key>
bool THeap<Key>::is_empty() const {
    return n_elements == 0;
}

template<class Key>
void THeap<Key>::sift_up(int x) {
    while (x > 0 && a[x] < a[(x - 1) / 2]) {
        std::swap(a[x], a[(x - 1) / 2]);
        x = (x - 1) / 2;
    }
}

template<class Key>
void THeap<Key>::sift_down(int x) {
    while (1){
        int minIndex = x;
        for (int i = 0; i < 2 && 2 * x + i + 1 < n_elements; ++i) {
            int curIndex = x * 2 + i + 1;
            if (a[curIndex] < a[minIndex])
                minIndex = curIndex;
        }
        if (minIndex == x)
            break;
        else{
            std::swap(a[x], a[minIndex]);
            x = minIndex;
        }
    }
}

template<class Key>
void THeap<Key>::insert(Key x) {
    a.push_back(x);
    sift_up(n_elements);
    n_elements++;
}

template<class Key>
Key THeap<Key>::extract_min() {
    if (is_empty()) {
        throw std::invalid_argument("heap is empty");
    }

    Key value = a[0];
    std::swap(a[0], a[n_elements - 1]);
    n_elements--;
    a.pop_back();
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
