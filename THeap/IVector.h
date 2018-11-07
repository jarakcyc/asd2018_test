#pragma once

template<class T>
class TVector {
public:
    TVector();
    ~TVector();

    bool is_empty() const;

    void push_back(T element);

    void pop_back();

    T& operator [] (int index) const;
private:
    int capasity;
    int size;
    T* buffer;

    void Increase();

    void Decrease();
};
