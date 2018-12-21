#pragma once

#include <stdexcept>

template<class T>
class TVector {
public:
    TVector();
    ~TVector();

    bool is_empty() const;

    void push_back(T element);

    void pop_back();

    int size() const;

    T back();

    T& operator [] (int index) const;
private:
    int capasity;
    int real_size;
    T* buffer;

    void Increase();

    void Decrease();
};

template<class T>
TVector<T>::TVector() :
    capasity(0),
    real_size(0)
{}

template<class T>
TVector<T>::~TVector() {
    delete[] buffer;
}

template<class T>
bool TVector<T>::is_empty() const {
    return (real_size == 0);
}

template<class T>
int TVector<T>::size() const {
    return real_size;
}

template<class T>
void TVector<T>::push_back(T element) {
    if (real_size == capasity) {
        Increase();
    }

    buffer[real_size] = element;
    real_size++;
}

template<class T>
void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::out_of_range("no elements");
    }

    real_size--;

    if (real_size * 4 < capasity) {
        Decrease();
    }
}

template<class T>
T TVector<T>::back() {
    if (real_size == 0) {
        throw std::out_of_range("no elements");
    }
    return buffer[real_size - 1];
}

template<class T>
T& TVector<T>::operator [] (int index) const {
    return buffer[index];
}

template<class T>
void TVector<T>::Increase() {
    if (capasity == 0) {
        capasity = 1;
        buffer = new T[1];
        return;
    }

    capasity *= 2;
    T* new_buffer = new T[capasity];

    for (int i = 0; i < real_size; ++i) {
        new_buffer[i] = buffer[i];
    }

    delete[] buffer;

    buffer = new_buffer;
}

template<class T>
void TVector<T>::Decrease() {
    capasity /= 2;
    T* new_buffer = new T[capasity];

    for (int i = 0; i < real_size; ++i) {
        new_buffer[i] = buffer[i];
    }

    delete[] buffer;

    buffer = new_buffer;
}

