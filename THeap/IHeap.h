#pragma once

#include "TVector.cpp"

template<class Key>
class THeap {
public:
    THeap();

    class Pointer {
    private:
        int index;
    };

    bool is_empty() const;

    void insert(Key x);

    Key extract_min();

    Key get_min() const;

    int get_size() const;
private:
    int n_elements;
    TVector<Key> a;

    void sift_up(int x);

    void sift_down(int x);
};
